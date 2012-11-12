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
	PE	, // PE 0					RO - USB_RX
	PE	, // PE 1					RO - USB_TX
	PJ	, // PJ 1					RO - USART_TX
	PJ	, // PJ 0					RO - USART_RX
	PG	, // PG 5					RO - SDCARD_SS
	PE	, // PE 3					RO - PWM0
	PH	, // PH 0					RO - PWM1 ** REMAP **
	PH	, // PH 1					RO - PWM2 ** REMAP **
	PH	, // PH 3					RO - PWM3
	PH	, // PH 4					RO - PWM4
	PB	, // PB 4					RO - ETHERNET_SS
	PH	, // PH 5					RO - PWM5
	PH	, // PH 6					RO - PWM6
	PB	, // PB 5					RO - PWM7
	PB	, // PB 6					RO - PWM8
	PB	, // PB 7					RO - PWM9
	PL	, // PL 3					RO - PWM10
	PL	, // PL 4					RO - PWM11
	PL	, // PL 5					RO - PWM12
	PE	, // PE 4					RO - INT0
	PD	, // PD 1					RO - I2C_SDA
	PD	, // PD 0					RO - I2C_SCL
	PE	, // PE 5					RO - INT1
	PE 	, // PE 6					RO - INT2
	PG	, // PG 0					RO - DIO0
	PG	, // PG 1					RO - DIO1
	PC	, // PC 0					RO - DIO2
	PC	, // PC 1					RO - DIO3
	PC	, // PC 2					RO - DIO4
	PC	, // PC 3					RO - DIO5
	PC	, // PC 4					RO - DIO6
	PC	, // PC 5					RO - DIO7
	PC	, // PC 6					RO - DIO8
	PC	, // PC 7					RO - DIO9
	PA	, // PA 7					RO - DIO10
	PA	, // PA 6					RO - DIO11
	PA	, // PA 5					RO - DIO12
	PA	, // PA 4					RO - DIO13
	PA	, // PA 3					RO - DIO14
	PA	, // PA 2					RO - DIO15
	PA	, // PA 1					RO - DIO16
	PA	, // PA 0					RO - DIO17
	PL	, // PL 0					RO - S0
	PL	, // PL 1					RO - S1
	PL	, // PL 2					RO - S2
	PL	, // PL 6					RO - S3
	PL	, // PL 7					RO - S4
	PG	, // PG 2					RO - S5
	PD	, // PD 7					RO - S6
	PJ  , // PJ 7					RO - S7
	PB	, // PB 3					RO - SPI_MISO
	PB	, // PB 2					RO - SPI_MOSI
	PB	, // PB 1					RO - SPI_SCK
	PB	, // PB 0					RO - SPI_SS
	PF	, // PF 0 					RO - AI0
	PF	, // PF 1 					RO - AI1
	PF	, // PF 2 					RO - AI2
	PF	, // PF 3 					RO - AI3
	PF	, // PF 4 					RO - AI4
	PF	, // PF 5 					RO - AI5
	PF	, // PF 6 					RO - AI6
	PF	, // PF 7 					RO - AI7
	PK	, // PK 0 					RO - AI8
	PK	, // PK 1 					RO - AI9
	PK	, // PK 2 					RO - AI10
	PK	, // PK 3 					RO - AI11
	PK	, // PK 4 					RO - AI12
	PK	, // PK 5 					RO - AI13
	PK	, // PK 6 					RO - AI14
	PK	, // PK 7 					RO - BMC
	PE  , // PE 7					RO - INT3
	PD	, // PD 2					RO - INT4
	PD	, // PD 3					RO - INT5
	PD	, // PD 4					RO - GREEN
	PD	, // PD 5					RO - BLUE
	PD	, // PD 6					RO - RED
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	// PIN IN PORT		
	// -------------------------------------------		
	_BV( 0 )	, // PE 0			RO - USB_RX
	_BV( 1 )	, // PE 1 			RO - USB_TX
	_BV( 1 )	, // PJ 1 			RO - USART_TX
	_BV( 0 )	, // PJ 0 			RO - USART_RX
	_BV( 5 )	, // PG 5 			RO - SDCARD_SS
	_BV( 3 )	, // PE 3 			RO - PWM0
	_BV( 0 )	, // PH 0 			RO - PWM1 ** REMAP **
	_BV( 1 )	, // PH 1 			RO - PWM2 ** REMAP **
	_BV( 3 )	, // PH 3 			RO - PWM3
	_BV( 4 )	, // PH 4 			RO - PWM4
	_BV( 4 )	, // PB 4 			RO - ETHERNET_SS
	_BV( 5 )	, // PH 5 			RO - PWM5
	_BV( 6 )	, // PH 6 			RO - PWM6
	_BV( 5 )	, // PB 5 			RO - PWM7
	_BV( 6 )	, // PB 6 			RO - PWM8
	_BV( 7 )	, // PB 7 			RO - PWM9
	_BV( 3 )	, // PL 3 			RO - PWM10
	_BV( 4 )	, // PL 4 			RO - PWM11
	_BV( 5 )	, // PL 5 			RO - PWM12
	_BV( 4 )	, // PE 4 			RO - INT0
	_BV( 1 )	, // PD 1 			RO - I2C_SDA
	_BV( 0 )	, // PD 0 			RO - I2C_SCL
	_BV( 5 )	, // PE 5 			RO - INT1
	_BV( 6 ) 	, // PE 6 			RO - INT2
	_BV( 0 )	, // PG 0 			RO - DIO0
	_BV( 1 )	, // PG 1 			RO - DIO1
	_BV( 0 )	, // PC 0 			RO - DIO2
	_BV( 1 )	, // PC 1 			RO - DIO3
	_BV( 2 )	, // PC 2 			RO - DIO4
	_BV( 3 )	, // PC 3 			RO - DIO5
	_BV( 4 )	, // PC 4 			RO - DIO6
	_BV( 5 )	, // PC 5 			RO - DIO7
	_BV( 6 )	, // PC 6 			RO - DIO8
	_BV( 7 )	, // PC 7 			RO - DIO9
	_BV( 7 )	, // PA 7 			RO - DIO10
	_BV( 6 )	, // PA 6 			RO - DIO11
	_BV( 5 )	, // PA 5 			RO - DIO12
	_BV( 4 )	, // PA 4 			RO - DIO13
	_BV( 3 )	, // PA 3 			RO - DIO14
	_BV( 2 )	, // PA 2 			RO - DIO15
	_BV( 1 )	, // PA 1 			RO - DIO16
	_BV( 0 )	, // PA 0 			RO - DIO17
	_BV( 0 )	, // PL 0 			RO - S0
	_BV( 1 )	, // PL 1 			RO - S1
	_BV( 2 )	, // PL 2 			RO - S2
	_BV( 6 )	, // PL 6 			RO - S3
	_BV( 7 )	, // PL 7 			RO - S4
	_BV( 2 )	, // PG 2 			RO - S5
	_BV( 7 )	, // PD 7 			RO - S6
	_BV( 7 )    , // PJ 7 			RO - S7
	_BV( 3 )	, // PB 3 			RO - SPI_MISO
	_BV( 2 )	, // PB 2 			RO - SPI_MOSI
	_BV( 1 )	, // PB 1 			RO - SPI_SCK
	_BV( 0 )	, // PB 0 			RO - SPI_SS
	_BV( 0 )	, // PF 0 			RO - AI0
	_BV( 1 )	, // PF 1 			RO - AI1
	_BV( 2 )	, // PF 2 			RO - AI2
	_BV( 3 )	, // PF 3 			RO - AI3
	_BV( 4 )	, // PF 4 			RO - AI4
	_BV( 5 )	, // PF 5 			RO - AI5
	_BV( 6 )	, // PF 6 			RO - AI6
	_BV( 7 )	, // PF 7 			RO - AI7
	_BV( 0 )	, // PK 0 			RO - AI8
	_BV( 1 )	, // PK 1 			RO - AI9
	_BV( 2 )	, // PK 2 			RO - AI10
	_BV( 3 )	, // PK 3 			RO - AI11
	_BV( 4 )	, // PK 4 			RO - AI12
	_BV( 5 )	, // PK 5 			RO - AI13
	_BV( 6 )	, // PK 6 			RO - AI14
	_BV( 7 )	, // PK 7 			RO - BMC
	_BV( 7 )  	, // PE 7 			RO - INT3
	_BV( 2 )	, // PD 2 			RO - INT4
	_BV( 3 )	, // PD 3 			RO - INT5
	_BV( 4 )    , // PD 4			RO - GREEN
	_BV( 5 )    , // PD 5			RO - BLUE
	_BV( 6 )    , // PD 6			RO - RED
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	// TIMERS		
	// -------------------------------------------		
	NOT_ON_TIMER	, // PE 0					RO - USB_RX
	NOT_ON_TIMER	, // PE 1					RO - USB_TX
	NOT_ON_TIMER	, // PJ 1					RO - USART_TX
	NOT_ON_TIMER	, // PJ 0					RO - USART_RX
	TIMER0B			, // PG 5					RO - SDCARD_SS
	TIMER3A			, // PE 3					RO - PWM0
	NOT_ON_TIMER	, // PH 0					RO - PWM1 ** REMAP **
	NOT_ON_TIMER	, // PH 1					RO - PWM2 ** REMAP **
	TIMER4A			, // PH 3					RO - PWM3
	TIMER4B			, // PH 4					RO - PWM4
	TIMER2A			, // PB 4					RO - ETHERNET_SS
	TIMER4C			, // PH 5					RO - PWM5
	TIMER2B			, // PH 6					RO - PWM6
	TIMER1A			, // PB 5					RO - PWM7
	TIMER1B			, // PB 6					RO - PWM8
	TIMER0A			, // PB 7					RO - PWM9
	TIMER5A			, // PL 3					RO - PWM10
	TIMER5B			, // PL 4					RO - PWM11
	TIMER5C			, // PL 5					RO - PWM12
	TIMER3B			, // PE 4					RO - INT0
	NOT_ON_TIMER	, // PD 1					RO - I2C_SDA
	NOT_ON_TIMER	, // PD 0					RO - I2C_SCL
	TIMER3C			, // PE 5					RO - INT1
	NOT_ON_TIMER 	, // PE 6					RO - INT2
	NOT_ON_TIMER	, // PG 0					RO - DIO0
	NOT_ON_TIMER	, // PG 1					RO - DIO1
	NOT_ON_TIMER	, // PC 0					RO - DIO2
	NOT_ON_TIMER	, // PC 1					RO - DIO3
	NOT_ON_TIMER	, // PC 2					RO - DIO4
	NOT_ON_TIMER	, // PC 3					RO - DIO5
	NOT_ON_TIMER	, // PC 4					RO - DIO6
	NOT_ON_TIMER	, // PC 5					RO - DIO7
	NOT_ON_TIMER	, // PC 6					RO - DIO8
	NOT_ON_TIMER	, // PC 7					RO - DIO9
	NOT_ON_TIMER	, // PA 7					RO - DIO10
	NOT_ON_TIMER	, // PA 6					RO - DIO11
	NOT_ON_TIMER	, // PA 5					RO - DIO12
	NOT_ON_TIMER	, // PA 4					RO - DIO13
	NOT_ON_TIMER	, // PA 3					RO - DIO14
	NOT_ON_TIMER	, // PA 2					RO - DIO15
	NOT_ON_TIMER	, // PA 1					RO - DIO16
	NOT_ON_TIMER	, // PA 0					RO - DIO17
	NOT_ON_TIMER	, // PL 0					RO - S0
	NOT_ON_TIMER	, // PL 1					RO - S1
	NOT_ON_TIMER	, // PL 2					RO - S2
	NOT_ON_TIMER	, // PL 6					RO - S3
	NOT_ON_TIMER	, // PL 7					RO - S4
	NOT_ON_TIMER	, // PG 2					RO - S5
	NOT_ON_TIMER	, // PD 7					RO - S6
	NOT_ON_TIMER  	, // PJ 7					RO - S7
	NOT_ON_TIMER	, // PB 3					RO - SPI_MISO
	NOT_ON_TIMER	, // PB 2					RO - SPI_MOSI
	NOT_ON_TIMER	, // PB 1					RO - SPI_SCK
	NOT_ON_TIMER	, // PB 0					RO - SPI_SS
	NOT_ON_TIMER	, // PF 0 					RO - AI0
	NOT_ON_TIMER	, // PF 1 					RO - AI1
	NOT_ON_TIMER	, // PF 2 					RO - AI2
	NOT_ON_TIMER	, // PF 3 					RO - AI3
	NOT_ON_TIMER	, // PF 4 					RO - AI4
	NOT_ON_TIMER	, // PF 5 					RO - AI5
	NOT_ON_TIMER	, // PF 6 					RO - AI6
	NOT_ON_TIMER	, // PF 7 					RO - AI7
	NOT_ON_TIMER	, // PK 0 					RO - AI8
	NOT_ON_TIMER	, // PK 1 					RO - AI9
	NOT_ON_TIMER	, // PK 2 					RO - AI10
	NOT_ON_TIMER	, // PK 3 					RO - AI11
	NOT_ON_TIMER	, // PK 4 					RO - AI12
	NOT_ON_TIMER	, // PK 5 					RO - AI13
	NOT_ON_TIMER	, // PK 6 					RO - AI14
	NOT_ON_TIMER	, // PK 7 					RO - BMC
	NOT_ON_TIMER  	, // PE 7					RO - INT3
	NOT_ON_TIMER	, // PD 2					RO - INT4
	NOT_ON_TIMER	, // PD 3					RO - INT5
	NOT_ON_TIMER	, // PD 4					RO - GREEN
	NOT_ON_TIMER	, // PD 5					RO - BLUE
	NOT_ON_TIMER	, // PD 6					RO - RED 	
};

#endif

#endif