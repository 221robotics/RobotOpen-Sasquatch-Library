#ifndef ROAnalog_h
#define ROAnalog_h

#include "RobotOpenSQ.h"


class ROAnalog
{
  public:
    ROAnalog(uint8_t);

    int read();
    
  private:
    uint8_t _channel;
};



#endif