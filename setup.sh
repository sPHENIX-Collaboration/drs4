#! /bin/sh

rcdaq_client load librcdaqplugin_drs.so
# the trigger setting of 0x21 ( bits 1  0 0 0 0 1) means that 
# the DRS is using its channel 1 for its own trigger.
# the most significant bit means it also provides the system trigger 
rcdaq_client create_device device_drs -- 1 1001 0x21 -150 negative 885
rcdaq_client daq_list_readlist
rcdaq_client daq_set_maxevents 200
