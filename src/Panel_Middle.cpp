#include "Panel_Middle.h"

void Panel_Middle::begin(BasicLog *_log) {
    m_pos = PANEL_MIDDLE;
}

void Panel_Middle::light(uint8_t c, uint8_t r) {
    
}

const char *Panel_Middle::getPositionAsString() {
    return "MIDDLE";
}