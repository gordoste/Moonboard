#ifndef _PANEL_TOP_H
#define _PANEL_TOP_H

#include "LedControl_HW_SPI.h"

#include "Panel.h"

class Panel_Top : public Panel {
    private:
        LedControl_HW_SPI ledCtrl;
    public:
        void begin(BasicLog *_log);
        void clear();
        void light(uint8_t c, uint8_t r);
        const char *getPositionAsString();
};

#endif // #ifndef _PANEL_TOP_H