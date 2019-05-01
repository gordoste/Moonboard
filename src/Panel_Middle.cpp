#include "Panel_Middle.h"

void Panel_Middle::begin(BasicLog *_log) {
  m_pos = PANEL_MIDDLE;
  m_log = _log;
  m_log->debug3("init %s start", getPositionAsString());
  
  //TODO setup the LedControl
  //TODO set shutdown false
  clear();
  //TODO set intensities

  m_log->debug2("init %s done", getPositionAsString());
}

void Panel_Middle::light(uint8_t c, uint8_t r) {
  m_log->debug3("light(%i,%i)", c, r);
  // TODO
}

const char *Panel_Middle::getPositionAsString() {
    return "MIDDLE";
}