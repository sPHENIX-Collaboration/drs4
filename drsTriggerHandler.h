#ifndef __DRSTRIGGERHANDLER_H__
#define __DRSTRIGGERHANDLER_H__

#include "TriggerHandler.h"

class DRSBoard;

class drsTriggerHandler : public TriggerHandler {

public:

  drsTriggerHandler(DRSBoard *board)
    {
      b = board;
    }

  ~drsTriggerHandler() {};

  //  virtual void identify(std::ostream& os = std::cout) const = 0;

  // this is the virtual worker routine
  int wait_for_trigger( const int moreinfo=0);

 protected:
  
  DRSBoard *b;


};

#endif
