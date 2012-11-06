// MACROS FOR EASY PIN HANDLING FOR ATMEL GCC-AVR
#define _SET(type,name,bit)            	type ## name  |= _BV(bit)    
#define _CLEAR(type,name,bit)        	type ## name  &= ~ _BV(bit)        
#define _GET(type,name,bit)            	((type ## name >> bit) &  1)

#define OUTPUT(pin)         _SET(DDR,pin)    
#define INPUT(pin)			_CLEAR(DDR,pin)    
#define HIGH(pin)          	_SET(PORT,pin)
#define LOW(pin)            _CLEAR(PORT,pin)       
#define READ(pin)           _GET(PIN,pin)


#define		DIO0 		G,0
#define		DIO1		G,1
#define		DIO2		C,0
#define		DIO3		C,1
#define		DIO4		C,2
#define		DIO5		C,3
#define		DIO6		C,4
#define		DIO7		C,5
#define		DIO8		C,6
#define		DIO9		C,7
#define		DIO10		A,7
#define		DIO11		A,6
#define		DIO12		A,5
#define		DIO13		A,4
#define		DIO14		A,3
#define		DIO15		A,2
#define		DIO16		A,1
#define		DIO17		A,0
#define		AI0			F,0
#define		AI1			F,1
#define		AI2			F,2
#define		AI3			F,3
#define		AI4			F,4
#define		AI5			F,5
#define		AI6			F,6
#define		AI7			F,7
#define		AI8			K,0
#define		AI9			K,1
#define		AI10		K,2
#define		AI11		K,3
#define		AI12		K,4
#define		AI13		K,5
#define		AI14		K,6
#define		AI15		K,7
#define		S0			L,0
#define		S1			L,1
#define		S2			L,2
#define		S3			L,6
#define		S4			L,7
#define		S5			D,7
#define		S6			G,2
#define		S7			J,7
#define		PWM0		E,3
#define		PWM1		H,0
#define		PWM2		H,1
#define		PWM3		H,3
#define		PWM4		H,4
#define		PWM5		H,5
#define		PWM6		H,6
#define		PWM7		B,5
#define		PWM8		B,6
#define		PWM9		B,7
#define		PWM10		L,3
#define		PWM11		L,4
#define		PWM12		L,5
#define		INT0		E,4
#define		INT1		E,5
#define		INT2		E,6
#define		INT3		E,7
#define		INT4		D,2
#define		INT5		D,3
#define		BMC			K,7