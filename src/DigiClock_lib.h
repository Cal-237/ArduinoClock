//
// Created by caleb on 12/17/2024.
//

#ifndef DIGICLOCK_LIB_H
#define DIGICLOCK_LIB_H

#include <avr/io.h>

#define REG_SEGMENTS 0x00
#define REG_ASCII 0x10
#define REG_STRING 0x20
#define REG_BRIGHTNESS 0x30

#define DIGICLOCK_ADDR 0x30

void i2c_write(uint8_t data);

void i2c_start(void);

void i2c_stop(void);

void i2c_init(void);

void digiClock_writeSegment(uint8_t index, uint8_t map);

void digiClock_writeSegments(uint8_t maps[4], uint8_t colon);

void digiClock_writeBrightness(uint8_t brightness);

void digiClock_writeASCII(char ascii[9]);

void digiClock_writeTime(uint8_t num1, uint8_t num2);

#endif //DIGICLOCK_LIB_H
