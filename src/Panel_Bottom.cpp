#include "Panel_Bottom.h"

void Panel_Bottom::begin(BasicLog *_log) {
  m_pos = PANEL_BOTTOM;
  m_log = _log;
  m_log->debug3("init %s start", getPositionAsString());
  
  //TODO setup the LedControl
  //TODO set shutdown false
  clear();
  //TODO set intensities

  m_log->debug2("init %s done", getPositionAsString());
}

void Panel_Bottom::light(uint8_t c, uint8_t r) {
  m_log->debug3("light(%i,%i)", c, r);
  // TODO
}

const char *Panel_Bottom::getPositionAsString() {
    return "BOTTOM";
}