#include "Panel_Top.h"

Panel_Top::Panel_Top() : Panel() {
    numRows = 6;
    numColumns = 11;
}

void Panel_Top::begin(BasicLog *_log) {
  m_pos = PANEL_TOP;
  m_log = _log;
  m_log->debug3("init %s start", getPositionAsString());

  ledCtrl.begin(MAX7219_CS_PIN, MAX7219_DEVICES, MAX7219_SPI_SPEED);
  ledCtrl.shutdown(0,false);
  ledCtrl.shutdown(1,false);
  ledCtrl.clearDisplay(0);
  ledCtrl.clearDisplay(1);
  ledCtrl.setIntensity(0, MOONBOARD_BLUERED_INTENSITY);
  ledCtrl.setIntensity(1, MOONBOARD_BLUERED_INTENSITY);

  lightEach();
  delay(1000);
  clear();

  m_log->debug2("init %s done", getPositionAsString());
}

void Panel_Top::clear() {
  ledCtrl.clearDisplay(0);
  ledCtrl.clearDisplay(1);
}

void Panel_Top::light(uint8_t r, uint8_t c) {
  m_log->debug2("light(%i,%i)", r, c);
  if (r > 5) { return; }
  if (c > 10) { return; }
  uint8_t addr; // address of MAX7219 to target
  if (c <= 5) {
    addr = 0;
  } else {
    addr = 1;
    c -= 6;
  }
  m_log->debug3("setLed(%i,%i,%i)", addr, r, c);
  ledCtrl.setLed(addr, r, c, true);
}

const char *Panel_Top::getPositionAsString() {
    return "TOP";
}