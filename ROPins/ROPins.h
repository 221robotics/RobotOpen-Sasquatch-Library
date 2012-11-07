#include <avr/io.h>




/** struct for mapping digital pins */
struct pin_map_t {
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  volatile uint8_t* port;
  uint8_t bit;
};



static const pin_map_t digitalPinMap[] = {
  {&DDRG, &PING, &PORTG, 0},  // G0  DIO0
  {&DDRG, &PING, &PORTG, 1},  // G1  DIO1
  {&DDRC, &PINC, &PORTC, 0},  // C0  DIO2
  {&DDRC, &PINC, &PORTC, 1},  // C1  DIO3
  {&DDRC, &PINC, &PORTC, 2},  // C2  DIO4
  {&DDRC, &PINC, &PORTC, 3},  // C3  DIO5
  {&DDRC, &PINC, &PORTC, 4},  // C4  DIO6
  {&DDRC, &PINC, &PORTC, 5},  // C5  DIO7
  {&DDRC, &PINC, &PORTC, 6},  // C6  DIO8
  {&DDRC, &PINC, &PORTC, 7},  // C7  DIO9
  {&DDRA, &PINA, &PORTA, 7},  // A7  DIO10
  {&DDRA, &PINA, &PORTA, 6},  // A6  DIO11
  {&DDRA, &PINA, &PORTA, 5},  // A5  DIO12
  {&DDRA, &PINA, &PORTA, 4},  // A4  DIO13
  {&DDRA, &PINA, &PORTA, 3},  // A3  DIO14
  {&DDRA, &PINA, &PORTA, 2},  // A2  DIO15
  {&DDRA, &PINA, &PORTA, 1},  // A1  DIO16
  {&DDRA, &PINA, &PORTA, 0}   // A0  DIO17
};

static const pin_map_t solenoidPinMap[] = {
  {&DDRL, &PINL, &PORTL, 0},  // L0  S0
  {&DDRL, &PINL, &PORTL, 1},  // L1  S1
  {&DDRL, &PINL, &PORTL, 2},  // L2  S2
  {&DDRL, &PINL, &PORTL, 6},  // L6  S3
  {&DDRL, &PINL, &PORTL, 7},  // L7  S4
  {&DDRD, &PIND, &PORTD, 7},  // D7  S5
  {&DDRG, &PING, &PORTG, 2},  // G2  S6
  {&DDRJ, &PINJ, &PORTJ, 7}   // J7  S7
};




static inline __attribute__((always_inline))
  void roPinMode(uint8_t pin, uint8_t mode) {

    if (mode) {
      *digitalPinMap[pin].ddr |= 1 << digitalPinMap[pin].bit;
    } else {
      *digitalPinMap[pin].ddr &= ~(1 << digitalPinMap[pin].bit);
    }

}
static inline __attribute__((always_inline))
  uint8_t roPinRead(uint8_t pin) {

    return (*digitalPinMap[pin].pin >> digitalPinMap[pin].bit) & 1;

}
static inline __attribute__((always_inline))
  void roPinWrite(uint8_t pin, uint8_t value) {

    if (value) {
      *digitalPinMap[pin].port |= 1 << digitalPinMap[pin].bit;
    } else {
      *digitalPinMap[pin].port &= ~(1 << digitalPinMap[pin].bit);
    }

}

static inline __attribute__((always_inline))
  void roEnableSolenoid(uint8_t pin) {
    *solenoidPinMap[pin].ddr |= 1 << solenoidPinMap[pin].bit;
}

static inline __attribute__((always_inline))
  void roSolenoidWrite(uint8_t pin, uint8_t value) {

    if (value) {
      *solenoidPinMap[pin].port |= 1 << solenoidPinMap[pin].bit;
    } else {
      *solenoidPinMap[pin].port &= ~(1 << solenoidPinMap[pin].bit);
    }

}





#define		AI0			0
#define		AI1			1
#define		AI2			2
#define		AI3			3
#define		AI4			4
#define		AI5			5
#define		AI6			6
#define		AI7			7
#define		AI8			8
#define		AI9			9
#define		AI10		10
#define		AI11		11
#define		AI12		12
#define		AI13		13
#define		AI14		14
#define		AI15		15
#define		BMC			15
#define		PWM0		5
#define		PWM1		17
#define		PWM2		16
#define		PWM3		6
#define		PWM4		7
#define		PWM5		8
#define		PWM6		9
#define		PWM7		11
#define		PWM8		12
#define		PWM9		13
#define		PWM10		46
#define		PWM11		45
#define		PWM12		44
#define		INT0		E,4
#define		INT1		E,5
#define		INT2		E,6
#define		INT3		E,7
#define		INT4		D,2
#define		INT5		D,3