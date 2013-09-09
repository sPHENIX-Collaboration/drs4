#! /bin/sh

rcdaq_client load librcdaqplugin_drs.so
rcdaq_client create_device device_drs -- 1 1001 1 -150 negative 885
rcdaq_client daq_list_readlist
rcdaq_client daq_set_maxevents 200
