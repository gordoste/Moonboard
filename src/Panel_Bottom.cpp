#include "Panel_Bottom.h"

void Panel_Bottom::begin(BasicLog *_log) {
  m_pos = PANEL_BOTTOM;
  m_log = _log;
  m_log->debug3("init %s start", getPositionAsString());
  
  ledCtrl_L = LedControl_SW_SPI();
  ledCtrl_R = LedControl_SW_SPI();
  ledCtrl_L.begin(MAX7219_DTA_PIN, MAX7219_CLK_PIN, MAX7219_CS1_PIN, MAX7219_CS1_DEVICES);
  ledCtrl_R.begin(MAX7219_DTA_PIN, MAX7219_CLK_PIN, MAX7219_CS2_PIN, MAX7219_CS2_DEVICES);
  ledCtrl_L.shutdown(0,false);
  ledCtrl_L.shutdown(1,false);
  ledCtrl_R.shutdown(0,false);
  ledCtrl_R.shutdown(1,false);
  ledCtrl_L.clearDisplay(0);
  ledCtrl_R.clearDisplay(0);
  ledCtrl_L.clearDisplay(1);
  ledCtrl_R.clearDisplay(1);
  ledCtrl_L.setIntensity(0, MOONBOARD_GREEN_INTENSITY);
  ledCtrl_L.setIntensity(1, MOONBOARD_BLUERED_INTENSITY);
  ledCtrl_R.setIntensity(0, MOONBOARD_GREEN_INTENSITY);
  ledCtrl_R.setIntensity(1, MOONBOARD_BLUERED_INTENSITY);

  m_log->debug2("init %s done", getPositionAsString());
}

void Panel_Bottom::clear() {
  ledCtrl_L.clearDisplay(0);
  ledCtrl_R.clearDisplay(0);
  ledCtrl_L.clearDisplay(1);
  ledCtrl_R.clearDisplay(1);
}

void Panel_Bottom::light(uint8_t c, uint8_t r) {
  //m_log->debug3("light(%i,%i)", c, r);
  if (r > 11) { return; }
  if (c > 10) { return; }
  LedControl_SW_SPI lc; // which LedControl object to target
  uint8_t addr; // address of MAX7219 to target
  if (r <= 5) { // green
    addr = 0;
  } else { // blue
    addr = 1;
    r -= 6;
  }
  if (c <= 5) { // left
    lc = ledCtrl_L;
  }
  else { // right
    lc = ledCtrl_R;
    c -= 6;    
  }
  //m_log->debug3("setLed(%i,%i,%i)", addr, r, c);
  //m_log->debug3("status:%i",ledCtrl_L.getStatus(3));
  lc.setLed(addr, r, c, true);
}

const char *Panel_Bottom::getPositionAsString() {
    return "BOTTOM";
}