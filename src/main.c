#include <avr/io.h>
#include <util/delay.h>
#include "DigiClock_lib.h"

typedef struct time {
    uint8_t mins;
    uint8_t secs;
} Time;

int main() {

    i2c_init();
    _delay_ms(100); // protective delay ater initializing i2c

    digiClock_writeBrightness(3);
    _delay_ms(10);

    Time time = {0, 0};

    while (1) {
        digiClock_writeTime(time.mins, time.secs);

        _delay_ms(1000);

        time.secs++;
        if (time.secs >= 60) {
            time.mins++;
            time.secs = 0;
        }

    }

    return 0;
}