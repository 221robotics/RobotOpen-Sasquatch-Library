/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            76
#define NUM_ANALOG_INPUTS           16
#define analogInputToDigitalPin(p)  ((p < 16) ? (p) + 54 : -1)
#define digitalPinHasPWM(p)         (((p) >= 5 && (p) <= 18))

static const uint8_t SS   = 53;
static const uint8_t MOSI = 51;
static const uint8_t MISO = 50;
static const uint8_t SCK  = 52;

static const uint8_t SDA = 20;
static const uint8_t SCL = 21;
static const uint8_t LED_BUILTIN = 74;

static const uint8_t A0 = 54;
static const uint8_t A1 = 55;
static const uint8_t A2 = 56;
static const uint8_t A3 = 57;
static const uint8_t A4 = 58;
static const uint8_t A5 = 59;
static const uint8_t A6 = 60;
static const uint8_t A7 = 61;
static const uint8_t A8 = 62;
static const uint8_t A9 = 63;
static const uint8_t A10 = 64;
static const uint8_t A11 = 65;
static const uint8_t A12 = 66;
static const uint8_t A13 = 67;
static const uint8_t A14 = 68;
static const uint8_t A15 = 69;


#ifdef ARDUINO_MAIN

const uint16_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &DDRA,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
	(uint16_t) &DDRE,
	(uint16_t) &DDRF,
	(uint16_t) &DDRG,
	(uint16_t) &DDRH,
	NOT_A_PORT,
	(uint16_t) &DDRJ,
	(uint16_t) &DDRK,
	(uint16_t) &DDRL,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
	(uint16_t) &PORTE,
	(uint16_t) &PORTF,
	(uint16_t) &PORTG,
	(uint16_t) &PORTH,
	NOT_A_PORT,
	(uint16_t) &PORTJ,
	(uint16_t) &PORTK,
	(uint16_t) &PORTL,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
	NOT_A_PIN,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
	(uint16_t) &PINE,
	(uint16_t) &PINF,
	(uint16_t) &PING,
	(uint16_t) &PINH,
	NOT_A_PIN,
	(uint16_t) &PINJ,
	(uint16_t) &PINK,
	(uint16_t) &PINL,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
	// PORTLIST		
	// -------------------------------------------		
	PE	, // PE 0 ** 0 ** USART0_RX				RO - USB
	PE	, // PE 1 ** 1 ** USART0_TX				RO - USB
	PJ	, // PJ 1 ** 14 ** USART3_TX			RO - USART
	PJ	, // PJ 0 ** 15 ** USART3_RX			RO - USART
	PG	, // PG 5 ** 4 ** PWM4					RO - SDCARD
	PE	, // PE 3 ** 5 ** PWM5					RO - PWM0
	PH	, // PH 0 ** 17 ** USART2_RX			RO - PWM1
	PH	, // PH 1 ** 16 ** USART2_TX			RO - PWM2
	PH	, // PH 3 ** 6 ** PWM6					RO - PWM3
	PH	, // PH 4 ** 7 ** PWM7					RO - PWM4
	PB	, // PB 4 ** 10 ** PWM10				RO - ETHERNET
	PH	, // PH 5 ** 8 ** PWM8					RO - PWM5
	PH	, // PH 6 ** 9 ** PWM9					RO - PWM6
	PB	, // PB 5 ** 11 ** PWM11				RO - PWM7
	PB	, // PB 6 ** 12 ** PWM12				RO - PWM8
	PB	, // PB 7 ** 13 ** PWM13				RO - PWM9
	PL	, // PL 3 ** 46 ** D46					RO - PWM10
	PL	, // PL 4 ** 45 ** D45					RO - PWM11
	PL	, // PL 5 ** 44 ** D44					RO - PWM12
	PE	, // PE 4 ** 2 ** PWM2					RO - INT0
	PD	, // PD 1 ** 20 ** I2C_SDA				RO - I2C
	PD	, // PD 0 ** 21 ** I2C_SCL				RO - I2C
	PE	, // PE 5 ** 3 ** PWM3					RO - INT1
	PE 	, // ADDED BY ROBOTOPEN					RO - INT2
	PG	, // PG 0 ** 41 ** D41					RO - DIO0
	PG	, // PG 1 ** 40 ** D40					RO - DIO1
	PC	, // PC 0 ** 37 ** D37					RO - DIO2
	PC	, // PC 1 ** 36 ** D36					RO - DIO3
	PC	, // PC 2 ** 35 ** D35					RO - DIO4
	PC	, // PC 3 ** 34 ** D34					RO - DIO5
	PC	, // PC 4 ** 33 ** D33					RO - DIO6
	PC	, // PC 5 ** 32 ** D32					RO - DIO7
	PC	, // PC 6 ** 31 ** D31					RO - DIO8
	PC	, // PC 7 ** 30 ** D30					RO - DIO9
	PA	, // PA 7 ** 29 ** D29					RO - DIO10
	PA	, // PA 6 ** 28 ** D28					RO - DIO11
	PA	, // PA 5 ** 27 ** D27					RO - DIO12
	PA	, // PA 4 ** 26 ** D26					RO - DIO13
	PA	, // PA 3 ** 25 ** D25					RO - DIO14
	PA	, // PA 2 ** 24 ** D24					RO - DIO15
	PA	, // PA 1 ** 23 ** D23					RO - DIO16
	PA	, // PA 0 ** 22 ** D22					RO - DIO17
	PL	, // PL 0 ** 49 ** D49					RO - S0
	PL	, // PL 1 ** 48 ** D48					RO - S1
	PL	, // PL 2 ** 47 ** D47					RO - S2
	PL	, // PL 6 ** 43 ** D43					RO - S3
	PL	, // PL 7 ** 42 ** D42					RO - S4
	PD	, // PD 7 ** 38 ** D38					RO - S5
	PG	, // PG 2 ** 39 ** D39					RO - S6
	PJ  , // ADDED BY ROBOTOPEN					RO - S7
	PB	, // PB 3 ** 50 ** SPI_MISO				RO - SPI
	PB	, // PB 2 ** 51 ** SPI_MOSI				RO - SPI
	PB	, // PB 1 ** 52 ** SPI_SCK				RO - SPI
	PB	, // PB 0 ** 53 ** SPI_SS				RO - SPI
	PF	, // PF 0 ** 54 ** A0					RO - AI0
	PF	, // PF 1 ** 55 ** A1					RO - AI1
	PF	, // PF 2 ** 56 ** A2					RO - AI2
	PF	, // PF 3 ** 57 ** A3					RO - AI3
	PF	, // PF 4 ** 58 ** A4					RO - AI4
	PF	, // PF 5 ** 59 ** A5					RO - AI5
	PF	, // PF 6 ** 60 ** A6					RO - AI6
	PF	, // PF 7 ** 61 ** A7					RO - AI7
	PK	, // PK 0 ** 62 ** A8					RO - AI8
	PK	, // PK 1 ** 63 ** A9					RO - AI9
	PK	, // PK 2 ** 64 ** A10					RO - AI10
	PK	, // PK 3 ** 65 ** A11					RO - AI11
	PK	, // PK 4 ** 66 ** A12					RO - AI12
	PK	, // PK 5 ** 67 ** A13					RO - AI13
	PK	, // PK 6 ** 68 ** A14					RO - AI14
	PK	, // PK 7 ** 69 ** A15					RO - AI15/BMC
	PE  , // ADDED BY ROBOTOPEN					RO - INT3
	PD	, // PD 2 ** 19 ** USART1_RX			RO - INT4
	PD	, // PD 3 ** 18 ** USART1_TX			RO - INT5
	PD	, // PD 4								RO - GREEN
	PD	, // PD 5								RO - BLUE
	PD	, // PD 6								RO - RED
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	// PIN IN PORT		
	// -------------------------------------------		
	_BV( 0 )	, // PE 0 ** 0 ** USART0_RX		RO - USB
	_BV( 1 )	, // PE 1 ** 1 ** USART0_TX		RO - USB
	_BV( 1 )	, // PJ 1 ** 14 ** USART3_TX	RO - USART
	_BV( 0 )	, // PJ 0 ** 15 ** USART3_RX	RO - USART
	_BV( 5 )	, // PG 5 ** 4 ** PWM4			RO - SDCARD
	_BV( 3 )	, // PE 3 ** 5 ** PWM5			RO - PWM0
	_BV( 0 )	, // PH 0 ** 17 ** USART2_RX	RO - PWM1
	_BV( 1 )	, // PH 1 ** 16 ** USART2_TX	RO - PWM2
	_BV( 3 )	, // PH 3 ** 6 ** PWM6			RO - PWM3
	_BV( 4 )	, // PH 4 ** 7 ** PWM7			RO - PWM4
	_BV( 4 )	, // PB 4 ** 10 ** PWM10		RO - ETHERNET
	_BV( 5 )	, // PH 5 ** 8 ** PWM8			RO - PWM5
	_BV( 6 )	, // PH 6 ** 9 ** PWM9			RO - PWM6
	_BV( 5 )	, // PB 5 ** 11 ** PWM11		RO - PWM7
	_BV( 6 )	, // PB 6 ** 12 ** PWM12		RO - PWM8
	_BV( 7 )	, // PB 7 ** 13 ** PWM13		RO - PWM9
	_BV( 3 )	, // PL 3 ** 46 ** D46			RO - PWM10
	_BV( 4 )	, // PL 4 ** 45 ** D45			RO - PWM11
	_BV( 5 )	, // PL 5 ** 44 ** D44			RO - PWM12
	_BV( 4 )	, // PE 4 ** 2 ** PWM2			RO - INT0
	_BV( 1 )	, // PD 1 ** 20 ** I2C_SDA		RO - I2C
	_BV( 0 )	, // PD 0 ** 21 ** I2C_SCL		RO - I2C
	_BV( 5 )	, // PE 5 ** 3 ** PWM3			RO - INT1
	_BV( 6 ) 	, // PE 6 ** 70 ** INT6			RO - INT2
	_BV( 0 )	, // PG 0 ** 41 ** D41			RO - DIO0
	_BV( 1 )	, // PG 1 ** 40 ** D40			RO - DIO1
	_BV( 0 )	, // PC 0 ** 37 ** D37			RO - DIO2
	_BV( 1 )	, // PC 1 ** 36 ** D36			RO - DIO3
	_BV( 2 )	, // PC 2 ** 35 ** D35			RO - DIO4
	_BV( 3 )	, // PC 3 ** 34 ** D34			RO - DIO5
	_BV( 4 )	, // PC 4 ** 33 ** D33			RO - DIO6
	_BV( 5 )	, // PC 5 ** 32 ** D32			RO - DIO7
	_BV( 6 )	, // PC 6 ** 31 ** D31			RO - DIO8
	_BV( 7 )	, // PC 7 ** 30 ** D30			RO - DIO9
	_BV( 7 )	, // PA 7 ** 29 ** D29			RO - DIO10
	_BV( 6 )	, // PA 6 ** 28 ** D28			RO - DIO11
	_BV( 5 )	, // PA 5 ** 27 ** D27			RO - DIO12
	_BV( 4 )	, // PA 4 ** 26 ** D26			RO - DIO13
	_BV( 3 )	, // PA 3 ** 25 ** D25			RO - DIO14
	_BV( 2 )	, // PA 2 ** 24 ** D24			RO - DIO15
	_BV( 1 )	, // PA 1 ** 23 ** D23			RO - DIO16
	_BV( 0 )	, // PA 0 ** 22 ** D22			RO - DIO17
	_BV( 0 )	, // PL 0 ** 49 ** D49			RO - S0
	_BV( 1 )	, // PL 1 ** 48 ** D48			RO - S1
	_BV( 2 )	, // PL 2 ** 47 ** D47			RO - S2
	_BV( 6 )	, // PL 6 ** 43 ** D43			RO - S3
	_BV( 7 )	, // PL 7 ** 42 ** D42			RO - S4
	_BV( 7 )	, // PD 7 ** 38 ** D38			RO - S5
	_BV( 2 )	, // PG 2 ** 39 ** D39			RO - S6
	_BV( 7 )    , // PJ 7 ** 72 ** S7			RO - S7
	_BV( 3 )	, // PB 3 ** 50 ** SPI_MISO		RO - SPI
	_BV( 2 )	, // PB 2 ** 51 ** SPI_MOSI		RO - SPI
	_BV( 1 )	, // PB 1 ** 52 ** SPI_SCK		RO - SPI
	_BV( 0 )	, // PB 0 ** 53 ** SPI_SS		RO - SPI
	_BV( 0 )	, // PF 0 ** 54 ** A0			RO - AI0
	_BV( 1 )	, // PF 1 ** 55 ** A1			RO - AI1
	_BV( 2 )	, // PF 2 ** 56 ** A2			RO - AI2
	_BV( 3 )	, // PF 3 ** 57 ** A3			RO - AI3
	_BV( 4 )	, // PF 4 ** 58 ** A4			RO - AI4
	_BV( 5 )	, // PF 5 ** 59 ** A5			RO - AI5
	_BV( 6 )	, // PF 6 ** 60 ** A6			RO - AI6
	_BV( 7 )	, // PF 7 ** 61 ** A7			RO - AI7
	_BV( 0 )	, // PK 0 ** 62 ** A8			RO - AI8
	_BV( 1 )	, // PK 1 ** 63 ** A9			RO - AI9
	_BV( 2 )	, // PK 2 ** 64 ** A10			RO - AI10
	_BV( 3 )	, // PK 3 ** 65 ** A11			RO - AI11
	_BV( 4 )	, // PK 4 ** 66 ** A12			RO - AI12
	_BV( 5 )	, // PK 5 ** 67 ** A13			RO - AI13
	_BV( 6 )	, // PK 6 ** 68 ** A14			RO - AI14
	_BV( 7 )	, // PK 7 ** 69 ** A15 			RO - AI15/BMC
	_BV( 7 )  	, // PE 7 ** 71 ** INT7			RO - INT3
	_BV( 2 )	, // PD 2 ** 19 ** USART1_RX	RO - INT4
	_BV( 3 )	, // PD 3 ** 18 ** USART1_TX	RO - INT5
	_BV( 4 )    , // PD 4						RO - GREEN
	_BV( 5 )    , // PD 5						RO - BLUE
	_BV( 6 )    , // PD 6						RO - RED
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	// TIMERS		
	// -------------------------------------------		
	NOT_ON_TIMER	, // PE 0 ** 0 ** USART0_RX	
	NOT_ON_TIMER	, // PE 1 ** 1 ** USART0_TX
	NOT_ON_TIMER	, // PJ 1 ** 14 ** USART3_TX	
	NOT_ON_TIMER	, // PJ 0 ** 15 ** USART3_RX
	TIMER0B	, // PG 5 ** 4 ** PWM4	
	TIMER3A	, // PE 3 ** 5 ** PWM5
	TIMER3B	, // PH 0 ** 17 ** USART2_RX
	TIMER3C	, // PH 1 ** 16 ** USART2_TX
	TIMER4A	, // PH 3 ** 6 ** PWM6	
	TIMER4B	, // PH 4 ** 7 ** PWM7
	TIMER2A	, // PB 4 ** 10 ** PWM10
	TIMER4C	, // PH 5 ** 8 ** PWM8	
	TIMER2B	, // PH 6 ** 9 ** PWM9
	TIMER1A	, // PB 5 ** 11 ** PWM11	
	TIMER1B	, // PB 6 ** 12 ** PWM12	
	TIMER0A	, // PB 7 ** 13 ** PWM13
	TIMER5A	, // PL 3 ** 46 ** D46	
	TIMER5B	, // PL 4 ** 45 ** D45	
	TIMER5C	, // PL 5 ** 44 ** D44	
	NOT_ON_TIMER	, // PE 4 ** 2 ** PWM2
	NOT_ON_TIMER	, // PD 1 ** 20 ** I2C_SDA	
	NOT_ON_TIMER	, // PD 0 ** 21 ** I2C_SCL	
	NOT_ON_TIMER	, // PE 5 ** 3 ** PWM3	
	NOT_ON_TIMER	, // PD 3 ** 18 ** USART1_TX	
	NOT_ON_TIMER	, // PD 2 ** 19 ** USART1_RX	
	NOT_ON_TIMER	, // PA 0 ** 22 ** D22	
	NOT_ON_TIMER	, // PA 1 ** 23 ** D23	
	NOT_ON_TIMER	, // PA 2 ** 24 ** D24	
	NOT_ON_TIMER	, // PA 3 ** 25 ** D25	
	NOT_ON_TIMER	, // PA 4 ** 26 ** D26	
	NOT_ON_TIMER	, // PA 5 ** 27 ** D27	
	NOT_ON_TIMER	, // PA 6 ** 28 ** D28	
	NOT_ON_TIMER	, // PA 7 ** 29 ** D29	
	NOT_ON_TIMER	, // PC 7 ** 30 ** D30	
	NOT_ON_TIMER	, // PC 6 ** 31 ** D31	
	NOT_ON_TIMER	, // PC 5 ** 32 ** D32	
	NOT_ON_TIMER	, // PC 4 ** 33 ** D33	
	NOT_ON_TIMER	, // PC 3 ** 34 ** D34	
	NOT_ON_TIMER	, // PC 2 ** 35 ** D35	
	NOT_ON_TIMER	, // PC 1 ** 36 ** D36	
	NOT_ON_TIMER	, // PC 0 ** 37 ** D37	
	NOT_ON_TIMER	, // PD 7 ** 38 ** D38	
	NOT_ON_TIMER	, // PG 2 ** 39 ** D39	
	NOT_ON_TIMER	, // PG 1 ** 40 ** D40	
	NOT_ON_TIMER	, // PG 0 ** 41 ** D41	
	NOT_ON_TIMER	, // PL 7 ** 42 ** D42	
	NOT_ON_TIMER	, // PL 6 ** 43 ** D43	
	NOT_ON_TIMER	, // PL 2 ** 47 ** D47	
	NOT_ON_TIMER	, // PL 1 ** 48 ** D48	
	NOT_ON_TIMER	, // PL 0 ** 49 ** D49	
	NOT_ON_TIMER	, // PB 3 ** 50 ** SPI_MISO	
	NOT_ON_TIMER	, // PB 2 ** 51 ** SPI_MOSI	
	NOT_ON_TIMER	, // PB 1 ** 52 ** SPI_SCK	
	NOT_ON_TIMER	, // PB 0 ** 53 ** SPI_SS	
	NOT_ON_TIMER	, // PF 0 ** 54 ** A0	
	NOT_ON_TIMER	, // PF 1 ** 55 ** A1	
	NOT_ON_TIMER	, // PF 2 ** 56 ** A2	
	NOT_ON_TIMER	, // PF 3 ** 57 ** A3	
	NOT_ON_TIMER	, // PF 4 ** 58 ** A4	
	NOT_ON_TIMER	, // PF 5 ** 59 ** A5	
	NOT_ON_TIMER	, // PF 6 ** 60 ** A6	
	NOT_ON_TIMER	, // PF 7 ** 61 ** A7	
	NOT_ON_TIMER	, // PK 0 ** 62 ** A8	
	NOT_ON_TIMER	, // PK 1 ** 63 ** A9	
	NOT_ON_TIMER	, // PK 2 ** 64 ** A10	
	NOT_ON_TIMER	, // PK 3 ** 65 ** A11	
	NOT_ON_TIMER	, // PK 4 ** 66 ** A12	
	NOT_ON_TIMER	, // PK 5 ** 67 ** A13	
	NOT_ON_TIMER	, // PK 6 ** 68 ** A14	
	NOT_ON_TIMER	, // PK 7 ** 69 ** A15	
	NOT_ON_TIMER	, // 	
	NOT_ON_TIMER	, // 	
	NOT_ON_TIMER	, // 	
	NOT_ON_TIMER	, // 	
	NOT_ON_TIMER	, // 	
	NOT_ON_TIMER	, // 	
};

#endif

#endif