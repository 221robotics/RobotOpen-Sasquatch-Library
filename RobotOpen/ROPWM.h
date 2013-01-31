#ifndef ROPWM_h
#define ROPWM_h

#include <RobotOpen.h>


class ROPWM
{
  public:
    ROPWM(uint8_t);

    void write(byte);
    
  private:
    uint8_t _channel;
};



#endif