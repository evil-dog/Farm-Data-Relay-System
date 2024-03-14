#include "fdrs_ssd1306wire.h"

uint16_t FDRS_SSD1306Wire::FDRS_drawStringMaxWidth(int16_t xMove, int16_t yMove, uint16_t maxLineWidth, const String &strUser) {
  uint16_t firstChar  = pgm_read_byte(fontData + FIRST_CHAR_POS);
  uint16_t lineHeight = pgm_read_byte(fontData + HEIGHT_POS);

  const char* text = strUser.c_str();

  uint16_t length = strlen(text);
  uint16_t lastDrawnPos = 0;
  uint16_t lineNumber = 0;
  uint16_t strWidth = 0;

  uint16_t preferredBreakpoint = 0;
  uint16_t widthAtBreakpoint = 0;
  uint16_t firstLineChars = 0;
  uint16_t drawStringResult = 1; // later tested for 0 == error, so initialize to 1

  for (uint16_t i = 0; i < length; i++) {
    char c = (this->fontTableLookupFunction)(text[i]);
    if (c == 0)
      continue;
    strWidth += pgm_read_byte(fontData + JUMPTABLE_START + (c - firstChar) * JUMPTABLE_BYTES + JUMPTABLE_WIDTH);

    // Always try to break on a space, dash or slash
    if (text[i] == ' ' || text[i]== '-' || text[i] == '/') {
      preferredBreakpoint = i + 1;
      widthAtBreakpoint = strWidth;
    }

    if (strWidth >= maxLineWidth) {
      if (preferredBreakpoint == 0) {
        preferredBreakpoint = i;
        widthAtBreakpoint = strWidth;
      }
      drawStringResult = drawStringInternal(xMove, yMove + (lineNumber++) * (lineHeight-5) , &text[lastDrawnPos], preferredBreakpoint - lastDrawnPos, widthAtBreakpoint, true);
      if (firstLineChars == 0)
        firstLineChars = preferredBreakpoint;
      lastDrawnPos = preferredBreakpoint;
      // It is possible that we did not draw all letters to i so we need
      // to account for the width of the chars from `i - preferredBreakpoint`
      // by calculating the width we did not draw yet.
      strWidth = strWidth - widthAtBreakpoint;
      preferredBreakpoint = 0;
      if (drawStringResult == 0) // we are past the display already?
        break;
    }
  }

  // Draw last part if needed
  if (drawStringResult != 0 && lastDrawnPos < length) {
    drawStringResult = drawStringInternal(xMove, yMove + (lineNumber++) * (lineHeight -5) , &text[lastDrawnPos], length - lastDrawnPos, getStringWidth(&text[lastDrawnPos], length - lastDrawnPos, true), true);
  }

 return lineNumber;

}
