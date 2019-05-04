#ifndef _PANEL_TOP_H
#define _PANEL_TOP_H

#include "LedControl_HW_SPI.h"

#include "Panel.h"

class Panel_Top : public Panel {
  private:
    LedControl_HW_SPI ledCtrl;
  public:
    Panel_Top();
    void begin(BasicLog *_log);
    void clear();
    void light(uint8_t r, uint8_t c);
    const char *getPositionAsString();
};

#endif // #ifndef _PANEL_TOP_H