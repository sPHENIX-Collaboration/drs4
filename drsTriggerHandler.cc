
#include "drsTriggerHandler.h"
#include <iostream>

#include "DRS.h"

using namespace std;


int drsTriggerHandler::wait_for_trigger( const int moreinfo)
{

  //  while (b->IsBusy());
  //return 0;
  return  b->IsBusy();

}
