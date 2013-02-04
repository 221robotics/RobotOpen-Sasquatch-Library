#ifndef ROTimer_h
#define ROTimer_h



class ROTimer
{
  public:
    ROTimer();

    void queue(unsigned int);
    boolean ready();
    
  private:
    unsigned long _millisExpire;
    boolean _timerSet;
};



#endif