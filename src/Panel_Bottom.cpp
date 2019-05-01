#include "Panel_Bottom.h"

void Panel_Bottom::begin(BasicLog *_log) {
    m_pos = PANEL_BOTTOM;
}

void Panel_Bottom::light(uint8_t c, uint8_t r) {
    
}

const char *Panel_Bottom::getPositionAsString() {
    return "BOTTOM";
}