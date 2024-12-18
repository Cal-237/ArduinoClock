//
// Created by caleb on 12/17/2024.
//

#include <avr/io.h>
#include "DigiClock_lib.h"

void i2c_write(const uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while ((TWCR & (1 << TWINT)) == 0)
        ;
}

void i2c_start(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while ((TWCR & (1 << TWINT)) == 0)
        ;
}

void i2c_stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void i2c_init(void) {
    TWSR = 0x00;
    TWBR = 0x48;  // sets frequency to 100kHz assuming prescaler = 1 and 16MHz F_CPU
    TWCR = (1 << TWEN);
}

void digiClock_writeSegment(const uint8_t index, const uint8_t map) {
    i2c_start();
    i2c_write(DIGICLOCK_ADDR << 1);   // address is 7 bits plus a 0 (Write) for R/W
    i2c_write(REG_SEGMENTS + index);

    i2c_write(map);

    i2c_stop();
}

void digiClock_writeSegments(uint8_t maps[4], uint8_t colon) {
    i2c_start();
    i2c_write(DIGICLOCK_ADDR << 1);   // address is 7 bits plus a 0 (Write) for R/W
    i2c_write(REG_SEGMENTS);

    i2c_write(maps[0]);
    i2c_write(maps[1]);

    i2c_write(colon);

    i2c_write(maps[2]);
    i2c_write(maps[3]);

    i2c_stop();
}

void digiClock_writeBrightness(const uint8_t brightness) {
    i2c_start();
    i2c_write(DIGICLOCK_ADDR << 1);   // address is 7 bits plus a 0 (Write) for R/W
    i2c_write(REG_BRIGHTNESS);

    i2c_write(brightness);

    i2c_stop();
}

void digiClock_writeASCII(char ascii[9]) {
    i2c_start();
    i2c_write(DIGICLOCK_ADDR << 1);   // address is 7 bits plus a 0 (Write) for R/W
    i2c_write(REG_ASCII);

    for (uint8_t i = 0; i < 9; i++) {
        i2c_write(ascii[i]);
    }

    i2c_stop();
}

void digiClock_writeTime(uint8_t num1, uint8_t num2) {
    unsigned char ascii[9] = "0 0 :0 0";

    ascii[0] = num1 / 10 + '0';
    ascii[2] = num1 % 10 + '0';

    ascii[5] = num2 / 10 + '0';
    ascii[7] = num2 % 10 + '0';

    digiClock_writeASCII(ascii);
}
