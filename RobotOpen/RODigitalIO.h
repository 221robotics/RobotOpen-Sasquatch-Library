#ifndef RODigitalIO_h
#define RODigitalIO_h

#include <RobotOpen.h>


class RODigitalIO
{
  public:
    RODigitalIO(uint8_t, uint8_t);

    void on();
	void off();
	uint8_t read();
	void pullUp();
	void allowFloat();
	void setMode(uint8_t);
    
  private:
    uint8_t _channel;
};



#endif