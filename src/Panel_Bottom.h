#ifndef _PANEL_BOTTOM_H
#define _PANEL_BOTTOM_H

#include "Panel.h"

class Panel_Bottom : public Panel {
    public:
    void begin(BasicLog *_log);
    void light(uint8_t c, uint8_t r);
    const char *getPositionAsString();
};

#endif // #ifndef _PANEL_BOTTOM_H