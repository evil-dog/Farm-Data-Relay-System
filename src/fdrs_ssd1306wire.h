#ifndef __FDRS_SSD1306Wire_h__
#define __FDRS_SSD1306Wire_h__

#include <SSD1306Wire.h>

class FDRS_SSD1306Wire : public SSD1306Wire {
    public:
        /**
         * Create and initialize the Display using Wire library
         *
         * Beware for retro-compatibility default values are provided for all parameters see below.
         * Please note that if you don't wan't SD1306Wire to initialize and change frequency speed ot need to 
         * ensure -1 value are specified for all 3 parameters. This can be usefull to control TwoWire with multiple
         * device on the same bus.
         * 
         * @param _address I2C Display address
         * @param _sda I2C SDA pin number, default to -1 to skip Wire begin call
         * @param _scl I2C SCL pin number, default to -1 (only SDA = -1 is considered to skip Wire begin call)
         * @param g display geometry dafault to generic GEOMETRY_128_64, see OLEDDISPLAY_GEOMETRY definition for other options
         * @param _i2cBus on ESP32 with 2 I2C HW buses, I2C_ONE for 1st Bus, I2C_TWO fot 2nd bus, default I2C_ONE
         * @param _frequency for Frequency by default Let's use ~700khz if ESP8266 is in 160Mhz mode, this will be limited to ~400khz if the ESP8266 in 80Mhz mode
         */
        FDRS_SSD1306Wire(uint8_t _address, int _sda = -1, int _scl = -1, OLEDDISPLAY_GEOMETRY g = GEOMETRY_128_64, HW_I2C _i2cBus = I2C_ONE, int _frequency = 700000)
        : SSD1306Wire(_address, _sda, _scl, g, _i2cBus, _frequency) {}

        // Modified version with closer spacing. Also returns number of lines used.
        uint16_t FDRS_drawStringMaxWidth(int16_t x, int16_t y, uint16_t maxLineWidth, const String &text);
};

#endif // __FDRS_SSD1306Wire_h__