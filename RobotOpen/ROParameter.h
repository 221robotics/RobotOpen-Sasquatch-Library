#ifndef ROParameter_h
#define ROParameter_h


// types for parameters
#define BOOL 'b'
#define CHAR 'c'
#define INT 'i'
#define LONG 'l'
#define FLOAT 'f'


class ROParameter
{
  public:
    ROParameter(String, char, uint8_t);

    boolean getBool();
    char getChar();
    int getInt();
    long getLong();
    float getFloat();

    String label;
    uint8_t type;
    uint8_t location;
};



#endif