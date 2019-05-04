#ifndef _PANEL_MIDDLE_H
#define _PANEL_MIDDLE_H

#define MAX7219_CS_PIN 15 // Pin 15 = D8 = CS
#define MAX7219_DEVICES 2
#define MAX7219_SPI_SPEED 1000000UL

#include "LedControl_HW_SPI.h"

#include "Panel.h"

class Panel_Middle : public Panel {
  private:
    LedControl_HW_SPI ledCtrl = LedControl_HW_SPI();
  public:
    Panel_Middle();
    void begin(BasicLog *_log);
    void clear();
    void light(uint8_t r, uint8_t c);
    const char *getPositionAsString();
};

#endif // #ifndef _PANEL_MIDDLE_H