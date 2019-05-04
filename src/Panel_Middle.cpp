#include "Panel_Middle.h"

Panel_Middle::Panel_Middle() : Panel() {}

void Panel_Middle::begin(BasicLog *_log) {
  m_pos = PANEL_MIDDLE;
  m_log = _log;
  m_log->debug3("init %s start", getPositionAsString());

  ledCtrl = LedControl_HW_SPI();

  //TODO setup the LedControl
  //TODO set shutdown false
  clear();
  //TODO set intensities

  m_log->debug2("init %s done", getPositionAsString());
}

void Panel_Middle::clear() {
  // TODO
}

void Panel_Middle::light(uint8_t r, uint8_t c) {
  m_log->debug3("light(%i,%i)", r, c);
  // TODO
}

const char *Panel_Middle::getPositionAsString() {
    return "MIDDLE";
}