#ifndef _PANEL_BOTTOM_H
#define _PANEL_BOTTOM_H

#define MAX7219_DTA_PIN 13  // Pin 13 = D7
#define MAX7219_CLK_PIN 14   // Pin 14 = D5
#define MAX7219_CS1_PIN 15   // Pin 15 = D8
#define MAX7219_CS1_DEVICES 2
#define MAX7219_CS2_PIN 12    // Pin 12 = D6
#define MAX7219_CS2_DEVICES 2

#include "LedControl_SW_SPI.h"

#include "Panel.h"

class Panel_Bottom : public Panel {
    private:
        LedControl_SW_SPI ledCtrl_L; // left side
        LedControl_SW_SPI ledCtrl_R; // right side
    public:
        void begin(BasicLog *_log);
        void clear();
        void light(uint8_t c, uint8_t r);
        const char *getPositionAsString();
};

#endif // #ifndef _PANEL_BOTTOM_H