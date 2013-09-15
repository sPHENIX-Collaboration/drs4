
#include <iostream>
#include "DRS.h"

#include <daq_device_drs.h>
#include <string.h>

using namespace std;

daq_device_drs::daq_device_drs(const int eventtype
					   , const int subeventid
					   , const int trigger
					   , const float triggerthreshold
					   , const int slope
					   , const int delay
					   , const int speed
					   , const int start
					   , const int nch)
{

  m_eventType  = eventtype;
  m_subeventid = subeventid;

  _trigger_handler=0;
  _broken = 0;

  _drs = new DRS();
  if (  _drs->GetNumberOfBoards() == 0)
    {
      _broken = 1;
      delete _drs;
      _drs = 0;
      b = 0;
      return;
    }

  b = _drs->GetBoard(0);


  // the trigger allows to make an "or" of 5 triggers
  _trigger = trigger & 0x1f;

  // bit number 5 says if we also provide the system trigger
  if (trigger & 0x20)
    { 
      _trigger_handler = 1 ; 
    }

  //  cout << "** " <<  __FILE__ << " triggerhandler " << _trigger_handler << endl;

  _tthreshold = triggerthreshold / 1000. ;
  _slope = slope;
  _delay = delay;

  _start = start;
  _nch = nch;

  if (  _start  > 1023 )
    {
      cout << "** " <<  __FILE__ << " warning: invalid start channels" << endl;

      _start = 0;
    }

  if ( _nch == 0 ) _nch = 1024;


  if ( ( _start + _nch) > 1024 )
    {
      cout << "** " <<  __FILE__ << " warning: invalid number of channels" << endl;

      _nch = 1024 - _start;
    }

  //  cout << __LINE__ << "  " << __FILE__ << " speed  " <<  speed<< endl;
  if ( speed != 0 
       && speed != 1
       && speed != 2
       && speed != 5 )
    {
      _speed = 0;
      cout << "invalid speed, setting 0.7GS/s"  << endl;
    }
  else
    {
      _speed = speed;
    }

  if ( _trigger_handler )
    {
      //  cout << __LINE__ << "  " << __FILE__ << " registering triggerhandler " << endl;
      _th  = new drsTriggerHandler (b);
      registerTriggerHandler ( _th);
    }
  else
    {
      _th = 0;
    }
  b->Init();


}

daq_device_drs::~daq_device_drs()
{
  // if (b) delete b;
  
  if ( _drs ) delete _drs;
  b = 0;

  if (_th)
    {
      clearTriggerHandler();
      delete _th;
      _th = 0;
    }
}


int  daq_device_drs::init()
{

  if ( _broken ) 
    {
      //      cout << __LINE__ << "  " << __FILE__ << " broken ";
      //      identify();
      return 0; //  we had a catastrophic failure
    }

  b->Reinit();
  b->SetFrequency(getGS(), 1);

  b->SetTranspMode(1);
  b->SetInputRange(0);
  b->EnableTrigger(1,1);              // lemo off, analog trigger on
  b->SetTriggerSource(_trigger);
  b->SetTriggerLevel(_tthreshold, _slope);
  b->SetTriggerDelayNs(_delay);
 
  // and we trigger rearm with our event type so it takes effect
  rearm (m_eventType);

  return 0;

}

// the put_data function

int daq_device_drs::put_data(const int etype, int * adr, const int length )
{

  if ( _broken ) 
    {
      //      cout << __LINE__ << "  " << __FILE__ << " broken ";
      //      identify();
      return 0; //  we had a catastrophic failure
    }

  int len = 0;

  if (etype != m_eventType )  // not our id
    {
      return 0;
    }

  sevt =  (subevtdata_ptr) adr;
  // set the initial subevent length
  sevt->sub_length =  SEVTHEADERLENGTH;

  // update id's etc
  sevt->sub_id =  m_subeventid;
  sevt->sub_type=4;
  sevt->sub_decoding = 81;
  sevt->reserved[0] = 0;
  sevt->reserved[1] = 0;

  if ( length < max_length(etype) ) 
    {
      //      cout << __LINE__ << "  " << __FILE__ << " length " << length <<endl;
      return 0;
    }

  unsigned int data;
  
  sevt->data = _nch | ( 0xf << 16);  // say "1024 samples, all 4 channels on" for now

  b->TransferWaves(0, 8);

  float *d = (float *) &sevt->data;  // we let "d" point to the location past the first word
  d++;                               // which we set 2 lines above
  len++;

  //  float *x = d;

  b->GetTime(0, b->GetTriggerCell(0), d);  // the first 1024 samples are the time bins

  if ( _start)
    {
      memmove (d, &d[_start], _nch);
    }

  len += _nch;
  d += _nch;

  for ( int i = 0; i < 8; i+=2)            // and here come channel 0,2,4,6 (the actually connected channels)
    {
      b->GetWave(0, i, d);
      if ( _start)
	{
	  memmove (d, &d[_start], _nch);
	}

      len += _nch;
      d += _nch;
    }


//   for ( int j = 0; j < 1024; j++)
//     {
//       cout << j 
// 	   << "  " << x[j] 
// 	   << "  " << x[j + 1024] 
// 	   << "  " << x[j + 2*1024] 
// 	   << "  " << x[j + 3*1024] 
// 	   << "  " << x[j + 4*1024] 
// 	   << endl;
//     }



  sevt->sub_padding = len%2;
  len = len + (len%2);
  sevt->sub_length += len;
  //  cout << __LINE__ << "  " << __FILE__ << " returning "  << sevt->sub_length << endl;

  return  sevt->sub_length;
}


void daq_device_drs::identify(std::ostream& os) const
{
  if ( _broken) 
    {
      os << "DRS4 Eval Board  Event Type: " << m_eventType 
	 << " Subevent id: " << m_subeventid 
	 << " ** not functional ** " << endl;
    }
  else
    {
      os  << "DRS4 Eval Board  Event Type: " << m_eventType 
	  << " Subevent id: " << m_subeventid 
	  << " S/N "     << b->GetBoardSerialNumber() 
	//	  << " Firmware rev " << b->GetFirmwareVersion()
	  << " Trg " << _trigger
	  << " Thresh " << _tthreshold*1000 <<"mV";
      if (_slope) os << " neg " ;
      else os << " pos "; 
      os << " delay " << _delay 
      //      os << " delay " << _delay << " (" << getGS() << "/" << getActualGS() << "GS) "
	 << " speed " << _speed << " (" 
	//	 << getGS() << " ( " << getActualGS() << ") GS) "
	 << getGS() <<  "GS) "
	 << " start " << _start << " nch " << _nch;
      if (_trigger_handler) os << " *Trigger" ;
      os << endl;

    }
}

int daq_device_drs::max_length(const int etype) const
{
  if (etype != m_eventType) return 0;
  return  (5*1024 + SEVTHEADERLENGTH + 10);
}


// the rearm() function
int  daq_device_drs::rearm(const int etype)
{
  if ( _broken ) 
    {
      //      cout << __LINE__ << "  " << __FILE__ << " broken ";
      //      identify();
      return 0; //  we had a catastrophic failure
    }

  if (etype != m_eventType) return 0;

  b->StartDomino();

  return 0;
}

double daq_device_drs::getActualGS() const 
{
  if ( _broken ) 
    {
      //      cout << __LINE__ << "  " << __FILE__ << " broken ";
      //      identify();
      return 0; //  we had a catastrophic failure
    }
  double f;
  b->ReadFrequency(0, &f);
  return f;
}

double daq_device_drs::getGS() const
{
  if ( _broken ) 
    {
      //      cout << __LINE__ << "  " << __FILE__ << " broken ";
      //      identify();
      return 0; //  we had a catastrophic failure
    }

  switch ( _speed)
    {
    case 0:
      return 0.7;
      break;

    case 1:
      return 1.;
      break;

    case 2:
      return 2.;
      break;

    case 3:
      return 5;
      break;

    default:
      return 1;
      break;
    }


}

