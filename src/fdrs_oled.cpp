#include "fdrs_oled.h"

void FDRS_OLED::draw_OLED_header()
{
    display->setFont(ArialMT_Plain_10);
    display->clear();
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    if (_is_gateway) {
        display->drawString(0, 0, "MAC: " + String(_mac, HEX));
    } else {
        display->drawString(0, 0, "ID: " + String(_mac));
    }
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(63, 0, _header);
    display->setTextAlignment(TEXT_ALIGN_RIGHT);
    if (_is_gateway) {
        display->drawString(127, 0, "TBD");
    } else {
        display->drawString(127, 0, "GW: " + String(_gateway_mac, HEX));
    }
    display->display();
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->setFont(ArialMT_Plain_10);
    display->drawHorizontalLine(0, 15, 128);
    display->drawHorizontalLine(0, 16, 128);
}

void FDRS_OLED::drawDebugPage() {
    draw_OLED_header();
    uint8_t lineNumber = 0;
    for (uint8_t i = 0; i < 5; i++)
    {
        uint8_t ret = display->FDRS_drawStringMaxWidth(0, 17 + (lineNumber * 9), 127, debug_buffer[i]);
        lineNumber = ret + lineNumber;
        if (lineNumber > 5)
            break;
    }
    display->display();
}

void FDRS_OLED::debug_OLED(String debug_text)
{
    displayEvent = millis()/1000; // Display Event is tracked in units of seconds
    displayPage = 0;
    display->clear();

    for (uint8_t i = 4; i > 0; i--)
    {

        debug_buffer[i] = debug_buffer[i - 1];
    }
    debug_buffer[0] = String(millis() / 1000) + " " + debug_text;
    drawDebugPage();
}

void FDRS_OLED::drawBlankPage() {
    display->clear();
    display->display();
}

void FDRS_OLED::drawStatusPage() {
    // draw_OLED_header();
    // display->FDRS_drawStringMaxWidth(0, 17, 127, "Status Page 1 " + String(millis()/1000));
    // display->display();
}

void FDRS_OLED::drawPage2() {
    // draw_OLED_header();
    // display->FDRS_drawStringMaxWidth(0, 17, 127, "Page 2 " + String(millis()/1000));
    // display->display();
}

void FDRS_OLED::drawPage3() {
    // draw_OLED_header();
    // display->FDRS_drawStringMaxWidth(0, 17, 127, "Page 3 " + String(millis()/1000));
    // display->display();
}

// write display content to display buffer
// nextpage = true -> flip 1 page
// When debug info comes in then switch to debug page
// after 60 seconds switch to blank page to save screen
void FDRS_OLED::drawPageOLED(bool nextpage) {

    if((millis()/1000 - displayEvent) > this->_page_secs && nextpage) {
        displayPage = (displayPage >= DISPLAY_PAGES) ? 0 : (displayPage + 1);
        displayEvent = millis()/1000;
        display->clear();

        switch(displayPage) {

        // page 0: debug output
        // page 1: gateway/node status
        // page 2: to be defined
        // page 3: to be defined
        // page 4: blank (screen saver)

        case 0: // display debug output
            drawDebugPage();
            break;
        case 1: // gateway/node status
            // drawStatusPage();
            // break;
        case 2: // to be defined later
            // drawPage2();
            // break;
        case 3: // to be defined later
            // drawPage3();
            // break;
        case 4: // Blank page
            drawBlankPage();
            break;
        default: // Blank page
            drawBlankPage();
            break;
        }
    }
}

void FDRS_OLED::init_oled() {
  pinMode(_rst, OUTPUT);
  digitalWrite(_rst, LOW);
  delay(30);
  digitalWrite(_rst, HIGH);
  Wire.begin(_sda, _scl);
  display->init();
  //display->flipScreenVertically();
  draw_OLED_header();
}
