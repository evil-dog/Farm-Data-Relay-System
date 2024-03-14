
#ifndef __FDRS_OLED_h__
#define __FDRS_OLED_h__

#include <Arduino.h>
#include "fdrs_ssd1306wire.h"
#define DISPLAY_PAGES 4

class FDRS_OLED {
    protected:
        int _sda;
        int _scl;
        uint8_t _rst;
        int _page_secs;
        bool _is_gateway;
        uint8_t _mac;
        String _header;
        uint8_t _gateway_mac;
        FDRS_SSD1306Wire* display; // ADDRESS, SDA, SCL
        String debug_buffer[5] = {"", "", "", "", ""};
        unsigned long displayEvent = 0;
        uint8_t displayPage = 0;

        void draw_OLED_header();
        void drawDebugPage();
        void drawBlankPage();
        void drawStatusPage();
        void drawPage2();
        void drawPage3();


    public:
        FDRS_OLED(int sda, int scl, uint8_t rst, int page_secs, bool is_gateway, uint8_t mac, String header, uint8_t gateway_mac) {
            _sda = sda;
            _scl = scl;
            _rst = rst;
            _page_secs = page_secs;
            _is_gateway = is_gateway;
            _mac = mac;
            _header = header;
            _gateway_mac = gateway_mac;
            display = new FDRS_SSD1306Wire(0x3c, sda, scl);
        }
        ~FDRS_OLED() {
            delete display;
        }

        void debug_OLED(String debug_text);
        void drawPageOLED(bool nextpage);
        void init_oled();
};

#endif //__FDRS_OLED_h__