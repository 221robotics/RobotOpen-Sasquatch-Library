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

#define NUM_DIGITAL_PINS            69
#define NUM_ANALOG_INPUTS           12
#define analogInputToDigitalPin(p)  ((p < 12) ? (p) + 73 : -1)


static const uint8_t SS   = 53;
static const uint8_t MOSI = 51;
static const uint8_t MISO = 50;
static const uint8_t SCK  = 52;

static const uint8_t SDA = 7;
static const uint8_t SCL = 8;
static const uint8_t LED_BUILTIN = 4;

static const uint8_t A0 = 73;
static const uint8_t A1 = 74;
static const uint8_t A2 = 75;
static const uint8_t A3 = 76;
static const uint8_t A4 = 77;
static const uint8_t A5 = 78;
static const uint8_t A6 = 79;
static const uint8_t A7 = 80;
static const uint8_t A8 = 81;
static const uint8_t A9 = 82;
static const uint8_t A10 = 83;
static const uint8_t A11 = 84;


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
	PE	, // PE0					RO0 - USB_RX
	PE	, // PE1					RO1 - USB_TX
	PJ	, // PJ1					RO2 - USART_TX
	PJ	, // PJ0					RO3 - USART_RX
	PD	, // PD6					RO4 - RED
	PD	, // PD4					RO5 - GREEN
	PD	, // PD5					RO6 - BLUE
	PD  , // PD1 					RO7 - I2C SDA
	PD	, // PD0					RO8 - I2C SCL
	PG  , // PG5					RO9 - SDCARD
    PB  , // PB4					RO10 - ETHERNET
    PE  , // PE4					RO11 - INT0
    PE  , // PE5					RO12 - INT1
    PE  , // PE6					RO13 - INT2
	PE  , // PE7					RO14 - INT3
	PD  , // PD2					RO15 - INT4
    PD  , // PD3					RO16 - INT5
	PJ  , // PJ6					RO17 - INT_DIO_0
	PJ  , // PJ5					RO18 - INT_DIO_1
    PJ  , // PJ4					RO19 - INT_DIO_2
	PJ  , // PJ3					RO20 - INT_DIO_3
	PJ  , // PJ2					RO21 - INT_DIO_4
	PG  , // PG3					RO22 - INT_DIO_5
	PE  , // PE2					RO23 - PWM0
    PE  , // PE3					RO24 - PWM1
    PH  , // PH0					RO25 - PWM2
    PH  , // PH1					RO26 - PWM3
    PH  , // PH2					RO27 - PWM4
	PH  , // PH3					RO28 - PWM5
	PH  , // PH4					RO29 - PWM6
	PH  , // PH5					RO30 - PWM7
	PH  , // PH6					RO31 - PWM8
	PH  , // PH7					RO32 - PWM9
	PB  , // PB5					RO33 - PWM10
	PB  , // PB6					RO34 - PWM11
	PB  , // PB7					RO35 - PWM12
	PL  , // PL3					RO36 - PWM13
	PL  , // PL4					RO37 - PWM14
	PL  , // PL5					RO38 - PWM15
	PL  , // PL0					RO39 - S0
	PL  , // PL1					RO40 - S1
	PL  , // PL2					RO41 - S2
 	PL  , // PL6					RO42 - S3
	PL  , // PL7					RO43 - S4
	PL  , // PD7					RO44 - S5
	PG  , // PG2					RO45 - S6
	PJ  , // PJ7					RO46 - S7
	PG  , // PG0					RO47 - DIO0
	PH  , // PG1					RO48 - DIO1
	PC  , // PC0					RO49 - DIO2
	PB  , // PB3					RO50 - SPI MISO
	PB  , // PB2					RO51 - SPI MOSI
	PB  , // PB1					RO52 - SPI SCK
	PB  , // PB0					RO53 - SPI SS
	PC  , // PC1					RO54 - DIO3
	PC  , // PC2					RO55 - DIO4
	PC  , // PC3					RO56 - DIO5
	PC  , // PC4					RO57 - DIO6
	PC  , // PC5					RO58 - DIO7
	PC  , // PC6					RO59 - DIO8
	PC  , // PC7					RO60 - DIO9
	PA  , // PA7					RO61 - DIO10
	PA  , // PA6					RO62 - DIO11
	PA  , // PA5					RO63 - DIO12
	PA  , // PA4					RO64 - DIO13
	PA  , // PA3					RO65 - DIO14
	PA  , // PA2					RO66 - DIO15
	PA  , // PA1					RO67 - DIO16
	PA  , // PA0					RO68 - DIO17
	PK  , // PK7					RO69 - DIO18
	PK  , // PK6					RO70 - DIO19
	PK  , // PK5					RO71 - DIO20
	PG  , // PG4					RO72 - DIO21
	PF  , // PF0					RO73 - AI0
	PF  , // PF1					RO74 - AI1
	PF  , // PF2					RO75 - AI2
	PF  , // PF3					RO76 - AI3
	PF  , // PF4					RO77 - AI4
	PF  , // PF5					RO78 - AI5
	PF  , // PF6					RO79 - AI6
	PF  , // PF7					RO80 - AI7
	PK  , // PK0					RO81 - AI8
	PK  , // PK1					RO82 - AI9
	PK  , // PK2					RO83 - AI10
	PK  , // PK3					RO84 - AI11
	PK  , // PK4					RO85 - BMC
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	// PIN IN PORT		
	// -------------------------------------------
	_BV( 0 )	, // PE0					RO0 - USB_RX
	_BV( 1 )	, // PE1					RO1 - USB_TX
	_BV( 1 )	, // PJ1					RO2 - USART_TX
	_BV( 0 )	, // PJ0					RO3 - USART_RX
	_BV( 6 )	, // PD6					RO4 - RED
	_BV( 4 )	, // PD4					RO5 - GREEN
	_BV( 5 )	, // PD5					RO6 - BLUE
	_BV( 1 )	, // PD1 					RO7 - I2C SDA
	_BV( 0 )	, // PD0					RO8 - I2C SCL
	_BV( 5 )	, // PG5					RO9 - SDCARD
    _BV( 4 )	, // PB4					RO10 - ETHERNET
    _BV( 4 )	, // PE4					RO11 - INT0
    _BV( 5 )	, // PE5					RO12 - INT1
    _BV( 6 )	, // PE6					RO13 - INT2
	_BV( 7 )	, // PE7					RO14 - INT3
	_BV( 2 )	, // PD2					RO15 - INT4
    _BV( 3 )	, // PD3					RO16 - INT5
	_BV( 6 )	, // PJ6					RO17 - INT_DIO_0
	_BV( 5 )	, // PJ5					RO18 - INT_DIO_1
    _BV( 4 )	, // PJ4					RO19 - INT_DIO_2
	_BV( 3 )	, // PJ3					RO20 - INT_DIO_3
	_BV( 2 )	, // PJ2					RO21 - INT_DIO_4
	_BV( 3 )	, // PG3					RO22 - INT_DIO_5
	_BV( 2 )	, // PE2					RO23 - PWM0
    _BV( 3 )	, // PE3					RO24 - PWM1
    _BV( 0 )	, // PH0					RO25 - PWM2
    _BV( 1 )	, // PH1					RO26 - PWM3
    _BV( 2 )	, // PH2					RO27 - PWM4
	_BV( 3 )	, // PH3					RO28 - PWM5
	_BV( 4 )	, // PH4					RO29 - PWM6
	_BV( 5 )	, // PH5					RO30 - PWM7
	_BV( 6 )	, // PH6					RO31 - PWM8
	_BV( 7 )	, // PH7					RO32 - PWM9
	_BV( 5 )	, // PB5					RO33 - PWM10
	_BV( 6 )	, // PB6					RO34 - PWM11
	_BV( 7 )	, // PB7					RO35 - PWM12
	_BV( 3 )	, // PL3					RO36 - PWM13
	_BV( 4 )	, // PL4					RO37 - PWM14
	_BV( 5 )	, // PL5					RO38 - PWM15
	_BV( 0 )	, // PL0					RO39 - S0
	_BV( 1 )	, // PL1					RO40 - S1
	_BV( 2 )	, // PL2					RO41 - S2
 	_BV( 6 )	, // PL6					RO42 - S3
	_BV( 7 )	, // PL7					RO43 - S4
	_BV( 7 )	, // PD7					RO44 - S5
	_BV( 2 )	, // PG2					RO45 - S6
	_BV( 7 )	, // PJ7					RO46 - S7
	_BV( 0 )	, // PG0					RO47 - DIO0
	_BV( 1 )	, // PG1					RO48 - DIO1
	_BV( 0 )	, // PC0					RO49 - DIO2
	_BV( 3 )	, // PB3					RO50 - SPI MISO
	_BV( 2 )	, // PB2					RO51 - SPI MOSI
	_BV( 1 )	, // PB1					RO52 - SPI SCK
	_BV( 0 )	, // PB0					RO53 - SPI SS
	_BV( 1 )	, // PC1					RO54 - DIO3
	_BV( 2 )	, // PC2					RO55 - DIO4
	_BV( 3 )	, // PC3					RO56 - DIO5
	_BV( 4 )	, // PC4					RO57 - DIO6
	_BV( 5 )	, // PC5					RO58 - DIO7
	_BV( 6 )	, // PC6					RO59 - DIO8
	_BV( 7 )	, // PC7					RO60 - DIO9
	_BV( 7 )	, // PA7					RO61 - DIO10
	_BV( 6 )	, // PA6					RO62 - DIO11
	_BV( 5 )	, // PA5					RO63 - DIO12
	_BV( 4 )	, // PA4					RO64 - DIO13
	_BV( 3 )	, // PA3					RO65 - DIO14
	_BV( 2 )	, // PA2					RO66 - DIO15
	_BV( 1 )	, // PA1					RO67 - DIO16
	_BV( 0 )	, // PA0					RO68 - DIO17
	_BV( 7 )	, // PK7					RO69 - DIO18
	_BV( 6 )	, // PK6					RO70 - DIO19
	_BV( 5 )	, // PK5					RO71 - DIO20
	_BV( 4 )	, // PG4					RO72 - DIO21
	_BV( 0 )	, // PF0					RO73 - AI0
	_BV( 1 )	, // PF1					RO74 - AI1
	_BV( 2 )	, // PF2					RO75 - AI2
	_BV( 3 )	, // PF3					RO76 - AI3
	_BV( 4 )	, // PF4					RO77 - AI4
	_BV( 5 )	, // PF5					RO78 - AI5
	_BV( 6 )	, // PF6					RO79 - AI6
	_BV( 7 )	, // PF7					RO80 - AI7
	_BV( 0 )	, // PK0					RO81 - AI8
	_BV( 1 )	, // PK1					RO82 - AI9
	_BV( 2 )	, // PK2					RO83 - AI10
	_BV( 3 )	, // PK3					RO84 - AI11
	_BV( 4 )	, // PK4					RO85 - BMC
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	// TIMERS		
	// -------------------------------------------
	NOT_ON_TIMER, // PE0					RO0 - USB_RX
	NOT_ON_TIMER, // PE1					RO1 - USB_TX
	NOT_ON_TIMER, // PJ1					RO2 - USART_TX
	NOT_ON_TIMER, // PJ0					RO3 - USART_RX
	NOT_ON_TIMER, // PD6					RO4 - RED
	NOT_ON_TIMER, // PD4					RO5 - GREEN
	NOT_ON_TIMER, // PD5					RO6 - BLUE
	NOT_ON_TIMER, // PD1 					RO7 - I2C SDA
	NOT_ON_TIMER, // PD0					RO8 - I2C SCL
	TIMER0B		, // PG5					RO9 - SDCARD
    TIMER2A		, // PB4					RO10 - ETHERNET
    TIMER3B		, // PE4					RO11 - INT0
    TIMER3C		, // PE5					RO12 - INT1
    NOT_ON_TIMER, // PE6					RO13 - INT2
	NOT_ON_TIMER, // PE7					RO14 - INT3
	NOT_ON_TIMER, // PD2					RO15 - INT4
    NOT_ON_TIMER, // PD3					RO16 - INT5
	NOT_ON_TIMER, // PJ6					RO17 - INT_DIO_0
	NOT_ON_TIMER, // PJ5					RO18 - INT_DIO_1
    NOT_ON_TIMER, // PJ4					RO19 - INT_DIO_2
	NOT_ON_TIMER, // PJ3					RO20 - INT_DIO_3
	NOT_ON_TIMER, // PJ2					RO21 - INT_DIO_4
	NOT_ON_TIMER, // PG3					RO22 - INT_DIO_5
	NOT_ON_TIMER, // PE2					RO23 - PWM0
    TIMER3A		, // PE3					RO24 - PWM1
    NOT_ON_TIMER, // PH0					RO25 - PWM2
    NOT_ON_TIMER, // PH1					RO26 - PWM3
    NOT_ON_TIMER, // PH2					RO27 - PWM4
	TIMER4A		, // PH3					RO28 - PWM5
	TIMER4B		, // PH4					RO29 - PWM6
	TIMER4C		, // PH5					RO30 - PWM7
	TIMER2B		, // PH6					RO31 - PWM8
	NOT_ON_TIMER, // PH7					RO32 - PWM9
	TIMER1A		, // PB5					RO33 - PWM10
	TIMER1B		, // PB6					RO34 - PWM11
	TIMER0A		, // PB7					RO35 - PWM12
	TIMER5A		, // PL3					RO36 - PWM13
	TIMER5B		, // PL4					RO37 - PWM14
	TIMER5C		, // PL5					RO38 - PWM15
	NOT_ON_TIMER, // PL0					RO39 - S0
	NOT_ON_TIMER, // PL1					RO40 - S1
	NOT_ON_TIMER, // PL2					RO41 - S2
 	NOT_ON_TIMER, // PL6					RO42 - S3
	NOT_ON_TIMER, // PL7					RO43 - S4
	NOT_ON_TIMER, // PD7					RO44 - S5
	NOT_ON_TIMER, // PG2					RO45 - S6
	NOT_ON_TIMER, // PJ7					RO46 - S7
	NOT_ON_TIMER, // PG0					RO47 - DIO0
	NOT_ON_TIMER, // PG1					RO48 - DIO1
	NOT_ON_TIMER, // PC0					RO49 - DIO2
	NOT_ON_TIMER, // PB3					RO50 - SPI MISO
	NOT_ON_TIMER, // PB2					RO51 - SPI MOSI
	NOT_ON_TIMER, // PB1					RO52 - SPI SCK
	NOT_ON_TIMER, // PB0					RO53 - SPI SS
	NOT_ON_TIMER, // PC1					RO54 - DIO3
	NOT_ON_TIMER, // PC2					RO55 - DIO4
	NOT_ON_TIMER, // PC3					RO56 - DIO5
	NOT_ON_TIMER, // PC4					RO57 - DIO6
	NOT_ON_TIMER, // PC5					RO58 - DIO7
	NOT_ON_TIMER, // PC6					RO59 - DIO8
	NOT_ON_TIMER, // PC7					RO60 - DIO9
	NOT_ON_TIMER, // PA7					RO61 - DIO10
	NOT_ON_TIMER, // PA6					RO62 - DIO11
	NOT_ON_TIMER, // PA5					RO63 - DIO12
	NOT_ON_TIMER, // PA4					RO64 - DIO13
	NOT_ON_TIMER, // PA3					RO65 - DIO14
	NOT_ON_TIMER, // PA2					RO66 - DIO15
	NOT_ON_TIMER, // PA1					RO67 - DIO16
	NOT_ON_TIMER, // PA0					RO68 - DIO17
	NOT_ON_TIMER, // PK7					RO69 - DIO18
	NOT_ON_TIMER, // PK6					RO70 - DIO19
	NOT_ON_TIMER, // PK5					RO71 - DIO20
	NOT_ON_TIMER, // PG4					RO72 - DIO21
	NOT_ON_TIMER, // PF0					RO73 - AI0
	NOT_ON_TIMER, // PF1					RO74 - AI1
	NOT_ON_TIMER, // PF2					RO75 - AI2
	NOT_ON_TIMER, // PF3					RO76 - AI3
	NOT_ON_TIMER, // PF4					RO77 - AI4
	NOT_ON_TIMER, // PF5					RO78 - AI5
	NOT_ON_TIMER, // PF6					RO79 - AI6
	NOT_ON_TIMER, // PF7					RO80 - AI7
	NOT_ON_TIMER, // PK0					RO81 - AI8
	NOT_ON_TIMER, // PK1					RO82 - AI9
	NOT_ON_TIMER, // PK2					RO83 - AI10
	NOT_ON_TIMER, // PK3					RO84 - AI11
	NOT_ON_TIMER, // PK4					RO85 - BMC
};

#endif

#endif