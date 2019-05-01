#include "Panel_Top.h"

void Panel_Top::begin(BasicLog *_log) {
    m_pos = PANEL_TOP;
}

void Panel_Top::light(uint8_t c, uint8_t r) {
}

const char *Panel_Top::getPositionAsString() {
    return "TOP";
}