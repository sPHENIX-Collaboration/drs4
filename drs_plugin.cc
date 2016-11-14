#include "drs_plugin.h"

#include "parseargument.h"

#include <daq_device_drs.h>
//#include <daq_device_tspmparams.h>

#include <strings.h>

int drs_plugin::create_device(deviceblock *db)
{

  //  std::cout << __LINE__ << "  " << __FILE__ << "  " << db->argv0 << "  " << db->npar << std::endl;

  int eventtype;
  int subid;

  if ( strcasecmp(db->argv0,"device_drs") == 0 ) 
    {
      // we need at least 3 params
      if ( db->npar <3 ) return 1; // indicate wrong params
      
      eventtype  = get_value ( db->argv1); // event type
      subid = get_value ( db->argv2); // subevent id

      if ( db->npar == 3)
	{

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 4)
	{
	  int trigger = get_value ( db->argv3);


	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  0,
						  trigger ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 5)
	{
	  int trigger = get_value ( db->argv3);
	  float th = strtof ( db->argv4, 0);

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  0,
						  trigger, th ));
	  return 0;  // say "we handled this request" 
	}
      else if ( db->npar == 6)
	{
	  int trigger = get_value ( db->argv3);
	  float th = strtof ( db->argv4, 0);
	  
	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv5[0] == 'P' || db->argv5[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv5[0] == 'N' || db->argv5[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = get_value ( db->argv5);
	    }

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  0,
						  trigger, th, slope ));
	  return 0;  // say "we handled this request" 
	}


      else if ( db->npar == 7)
	{
	  int trigger = get_value ( db->argv3);
	  float th = strtof ( db->argv4, 0);

	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv5[0] == 'P' || db->argv5[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv5[0] == 'N' || db->argv5[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = get_value ( db->argv5);
	    }


	  int delay = get_value ( db->argv6);


	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  0,
						  trigger, th, slope, delay ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 8)
	{
	  int trigger = get_value ( db->argv3);
	  float th = strtof ( db->argv4, 0);

	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv5[0] == 'P' || db->argv5[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv5[0] == 'N' || db->argv5[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = get_value ( db->argv5);
	    }

	  int delay = get_value ( db->argv6);
	  int speed = get_value ( db->argv7);

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  0,
						  trigger, th, slope, delay, speed ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 9)
	{
	  int trigger = get_value ( db->argv3);
	  float th = strtof ( db->argv4, 0);

	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv5[0] == 'P' || db->argv5[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv5[0] == 'N' || db->argv5[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = get_value ( db->argv5);
	    }

	  int delay = get_value ( db->argv6);
	  int speed = get_value ( db->argv7);
	  int startch = get_value ( db->argv8);

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  0,
						  trigger, th, slope,
						  delay, speed, startch ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 10)
	{
	  int trigger = get_value ( db->argv3);
	  float th = strtof ( db->argv4, 0);

	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv5[0] == 'P' || db->argv5[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv5[0] == 'N' || db->argv5[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = get_value ( db->argv5);
	    }

	  int delay = get_value ( db->argv6);
	  int speed = get_value ( db->argv7);
	  int startch = get_value ( db->argv8);
	  int nch = get_value ( db->argv9);

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  0,
						  trigger, th, slope,
						  delay, speed, startch, nch ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 11)
	{
	  int trigger = get_value ( db->argv3);
	  float th = strtof ( db->argv4, 0);

	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv5[0] == 'P' || db->argv5[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv5[0] == 'N' || db->argv5[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = get_value ( db->argv5);
	    }

	  int delay = get_value ( db->argv6);
	  int speed = get_value ( db->argv7);
	  int startch = get_value ( db->argv8);
	  int nch = get_value ( db->argv9);
	  int baseline = get_value ( db->argv10);

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  0,
						  trigger, th, slope,
						  delay, speed, startch, nch, baseline ));
	  return 0;  // say "we handled this request" 
	}



      
      else
	{
	  return 1; // say it is our device but the parameters are wrong 
	}
    } 


  // the new "by serialnumber" device


  else if ( strcasecmp(db->argv0,"device_drs_by_serialnumber") == 0 ) 
    {
      // we need at least 4 params
      if ( db->npar <4 ) return 1; // indicate wrong params
      
      eventtype  = get_value ( db->argv1); // event type
      subid = get_value ( db->argv2); // subevent id
      int serialnumber = get_value ( db->argv3); // serialnumber

      if ( db->npar == 4)
	{

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  serialnumber ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 5)
	{
	  int trigger = get_value ( db->argv4);


	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  serialnumber,
						  trigger ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 6)
	{
	  int trigger = get_value ( db->argv4);
	  float th = strtof ( db->argv5, 0);

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  serialnumber,
						  trigger, th ));
	  return 0;  // say "we handled this request" 
	}
      
      else if ( db->npar == 7)
	{
	  int trigger = get_value ( db->argv4);
	  float th = strtof ( db->argv5, 0);
	  
	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv6[0] == 'P' || db->argv6[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv6[0] == 'N' || db->argv6[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = get_value ( db->argv6);
	    }

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  serialnumber,
						  trigger, th, slope ));
	  return 0;  // say "we handled this request" 
	}


      else if ( db->npar == 8)
	{
	  int trigger = get_value ( db->argv4);
	  float th = strtof ( db->argv5, 0);

	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv6[0] == 'P' || db->argv6[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv6[0] == 'N' || db->argv6[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = get_value ( db->argv6);
	    }


	  int delay = get_value ( db->argv7);


	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  serialnumber,
						  trigger, th, slope, delay ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 9)
	{
	  int trigger = get_value ( db->argv4);
	  float th = strtof ( db->argv5, 0);

	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv6[0] == 'P' || db->argv6[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv6[0] == 'N' || db->argv6[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = get_value ( db->argv6);
	    }

	  int delay = get_value ( db->argv7);
	  int speed = get_value ( db->argv8);

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  serialnumber,
						  trigger, th, slope, delay, speed ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 10)
	{
	  int trigger = get_value ( db->argv4);
	  float th = strtof ( db->argv5, 0);

	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv6[0] == 'P' || db->argv6[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv6[0] == 'N' || db->argv6[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = get_value ( db->argv6);
	    }

	  int delay = get_value ( db->argv7);
	  int speed = get_value ( db->argv8);
	  int startch = get_value ( db->argv9);

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  serialnumber,
						  trigger, th, slope,
						  delay, speed, startch ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 11)
	{
	  int trigger = get_value ( db->argv4);
	  float th = strtof ( db->argv5, 0);

	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv6[0] == 'P' || db->argv6[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv6[0] == 'N' || db->argv6[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = get_value ( db->argv6);
	    }

	  int delay = get_value ( db->argv7);
	  int speed = get_value ( db->argv8);
	  int startch = get_value ( db->argv9);
	  int nch = get_value ( db->argv10);

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  serialnumber,
						  trigger, th, slope,
						  delay, speed, startch, nch ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 12)
	{
	  int trigger = get_value ( db->argv4);
	  float th = strtof ( db->argv5, 0);

	  // slope can be 0 (negative) or 1 (positive)
	  // or P / p or N / n 
	  int slope = 0;
	  if ( db->argv6[0] == 'P' || db->argv6[0] == 'p' )
	    {
	      slope = 0;
	    }
	  else if ( db->argv6[0] == 'N' || db->argv6[0] == 'n' )
	    {
	      slope = 1;
	    }
	  else
	    {
	      slope = get_value ( db->argv6);
	    }

	  int delay = get_value ( db->argv7);
	  int speed = get_value ( db->argv8);
	  int startch = get_value ( db->argv9);
	  int nch = get_value ( db->argv10);
	  int baseline = get_value ( db->argv11);

	  add_readoutdevice ( new daq_device_drs( eventtype,
						  subid,
						  serialnumber,
						  trigger, th, slope,
						  delay, speed, startch, nch, baseline ));
	  return 0;  // say "we handled this request" 
	}



      
      else
	{
	  return 1; // say it is our device but the parameters are wrong 
	}
    } 
  
  return -1; // say " this is not our device"
}

void drs_plugin::identify(std::ostream& os, const int flag) const
{

  if ( flag <=2 )
    {
      os << " - DRS Plugin" << std::endl;
    }
  else
    {
      os << " - DRS Plugin, provides - " << std::endl;
      os << " -     device_drs (evttype, subid, triggerchannel, triggerthreshold[mV], slope[n/p], delay[ns], speed, start_ch, nch, baseline[mV]) - DRS4 Eval Board " << std::endl;
      os << " -     device_drs_by_serialnumber " << std::endl;
      os << "                  (evttype, subid, serialnumber, triggerchannel, triggerthreshold[mV], slope[n/p], delay[ns], speed, start_ch, nch, baseline[mV]) - DRS4 Eval Board " << std::endl;
    }
      

}


drs_plugin _dp;
