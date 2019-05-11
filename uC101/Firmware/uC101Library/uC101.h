#ifndef __UC101_H__
#define __UC101_H__

#include <stdint.h>

// uC101 Pin Definitions
#define BUTTON_1 	PD2
#define BUTTON_2 	PD4

#define ENCODER_SW 	PB1
#define ENCODER_A 	PB0
#define ENCODER_B 	PD7

#define LED_RED 	PD3
#define LED_GREEN 	PD5
#define LED_BLUE 	PD6

#define CHARLIE_1 	PC3
#define CHARLIE_2 	PC2
#define CHARLIE_3 	PC1
#define CHARLIE_4 	PC0

#define UART_RX 	PD0
#define UART_TX 	PD1

#define SPI_MOSI 	PB3
#define SPI_MISO    PB4
#define SPI_SCK     PB5
#define SPI_nSS     PB2

#define I2C_SDA 	PC4
#define I2C_SCL     PC5

#define POT 		ADC6

// Port Definitions
#define BUTTON_1_PORT 	PORTD
#define BUTTON_2_PORT 	PORTD

#define ENCODER_SW_PORT PORTB
#define ENCODER_A_PORT 	PORTB
#define ENCODER_B_PORT 	PORTD

#define LED_RED_PORT 	PORTD
#define LED_GREEN_PORT 	PORTD
#define LED_BLUE_PORT 	PORTD

#define CHARLIE_1_PORT 	PORTC
#define CHARLIE_2_PORT 	PORTC
#define CHARLIE_3_PORT 	PORTC
#define CHARLIE_4_PORT 	PORTC

#define UART_RX_PORT 	PORTD
#define UART_TX_PORT 	PORTD

#define SPI_MOSI_PORT 	PORTB
#define SPI_MISO_PORT 	PORTB
#define SPI_SCK_PORT 	PORTB
#define SPI_nSS_PORT 	PORTB

#define I2C_SDA_PORT	PORTC
#define I2C_SCL_PORT	PORTC

//  Pin/Port Manipulation Macros
#define clearBit(port,pin) 	(port) &= ~(1<<(pin))
#define setBit(port,pin) 	(port) |= (1<<(pin))
#define toggleBit(port,pin) (port) ^= (1<<(pin))

#define ledOn(pin) 			(PORTD) &= ~(1<<(pin))
#define ledOff(pin) 		(PORTD) |= (1<<(pin))
#define ledToggle(pin) 		(PORTD) ^= (1<<(pin))

#define dirOut(port,pin) 	(*(&port-1)) |= (1<<(pin))
#define dirIn(port,pin) 	(*(&port-1)) &= ~(1<<(pin))

#define readPin(port,pin) 	(((*(&port-2)) & (1<<pin)) ? 1 : 0)

#endif