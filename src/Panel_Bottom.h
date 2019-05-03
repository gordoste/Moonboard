#ifndef _PANEL_BOTTOM_H
#define _PANEL_BOTTOM_H

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