#ifndef RODigitalIO_h
#define RODigitalIO_h

#include "RobotOpenSQ.h"


class RODigitalIO
{
  public:
    RODigitalIO(uint8_t, uint8_t);

    void on();
	void off();
	boolean read();
	void pullUp();
	void allowFloat();
	void setMode(uint8_t);
    
  private:
    uint8_t _channel;
};



#endif