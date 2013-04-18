#ifndef ROParameter_h
#define ROParameter_h


// types for parameters
#define BOOL 'b'
#define CHAR 'c'
#define INT 'i'
#define LONG 'l'
#define FLOAT 'f'


// generic definition
class ROParameter
{
  public:
    String label;
    uint8_t type;
    uint8_t location;
};


class ROBoolParameter
{
  public:
    ROBoolParameter(String, uint8_t);

    boolean get();

    String label;
    uint8_t type;
    uint8_t location;
};

class ROCharParameter
{
  public:
    ROCharParameter(String, uint8_t);

    char get();

    String label;
    uint8_t type;
    uint8_t location;
};

class ROIntParameter
{
  public:
    ROIntParameter(String, uint8_t);

    int get();

    String label;
    uint8_t type;
    uint8_t location;
};

class ROLongParameter
{
  public:
    ROLongParameter(String, uint8_t);

    long get();

    String label;
    uint8_t type;
    uint8_t location;
};


class ROFloatParameter
{
  public:
    ROFloatParameter(String, uint8_t);

    float get();

    String label;
    uint8_t type;
    uint8_t location;
};


#endif