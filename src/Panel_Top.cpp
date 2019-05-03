#include "Panel_Top.h"

void Panel_Top::begin(BasicLog *_log) {
  m_pos = PANEL_TOP;
  m_log = _log;
  m_log->debug3("init %s start", getPositionAsString());
  
  ledCtrl = LedControl_HW_SPI();

  //TODO setup the LedControl
  //TODO set shutdown false
  clear();
  //TODO set intensities

  m_log->debug2("init %s done", getPositionAsString());
}

void Panel_Top::clear() {
  // TODO
}

void Panel_Top::light(uint8_t c, uint8_t r) {
  m_log->debug3("light(%i,%i)", c, r);
  // TODO
}

const char *Panel_Top::getPositionAsString() {
  return "TOP";
}