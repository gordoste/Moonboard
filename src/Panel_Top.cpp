#include "Panel_Top.h"

Panel_Top::Panel_Top() : Panel() {}

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

void Panel_Top::light(uint8_t r, uint8_t c) {
  m_log->debug3("light(%i,%i)", r, c);
  // TODO
}

const char *Panel_Top::getPositionAsString() {
  return "TOP";
}