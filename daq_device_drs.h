#ifndef __DAQ_DEVICE_TSPMPROTO__
#define __DAQ_DEVICE_TSPMPROTO__


#include <daq_device.h>
#include <stdio.h>
#include <drsTriggerHandler.h>

class DRS;
class DRSBoard;

class daq_device_drs: public  daq_device {


public:

  daq_device_drs(const int eventtype
		 , const int subeventid
		 , const int serialnumber = 0
		 , const int trigger = 0x21
		 , const float triggerthreshold = -50
		 , const int slope = 0
		 , const int delay = 0
		 , const int speed = 0
		 , const int start = 0
		 , const int nch = 0
		 , const int baseline = 0);

  ~daq_device_drs();


  void identify(std::ostream& os = std::cout) const;

  int max_length(const int etype) const;

  // functions to do the work

  int put_data(const int etype, int * adr, const int length);

  int init();

  int rearm( const int etype);

 protected:
  double getGS() const;
  double getActualGS() const;

  subevtdata_ptr sevt;

  int _broken;

  int _serialnumber;

  int _trigger;
  int _trigger_handler;
  double _tthreshold;
  int _slope;
  int _delay;
  int _speed;
  int _start;  // this is the first channel to readout
  int _nch;    // this how many channels to read out
  int _baseline;

  static DRS *_drs;


  
  DRSBoard *b;

  drsTriggerHandler *_th;

};


#endif
