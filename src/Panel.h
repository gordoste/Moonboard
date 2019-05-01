#ifndef _PANEL_H
#define _PANEL_H

#include <SSD1306Console.h>
#include "LedControl_HW_SPI.h"
#include "BasicLog.h"

#include "Arduino.h"

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <Wifi.h>
#endif

#define MOONBOARD_MAXHOLDS 20 // Maximum holds lit per panel

#define MOONBOARD_BLUERED_INTENSITY 8
#define MOONBOARD_GREEN_INTENSITY 10 // Green LEDs are a bit weaker

#define MOONBOARD_SPI_SPEED 1000000UL

enum Position
{
  PANEL_BOTTOM = 0,
  PANEL_MIDDLE = 1,
  PANEL_TOP = 2
};

enum Command
{
  CMD_SET = 0,
  CMD_CLR = 1
};

class Panel
{
protected:
  byte data[2];
  char *holds[MOONBOARD_MAXHOLDS];
  char *ptr;
  LedControl_HW_SPI ledCtrl = LedControl_HW_SPI();
  int cmd;
  char *cmdId;
  char *cmdType;
  Client *m_client;
  BasicLog *m_log;
  Position m_pos;

  int alphaToInt(char cc);

public:
  Panel(){};
  void begin(BasicLog *_log);
  void light(uint8_t c, uint8_t r);
  void clear();
  void processCmd(char *buf, int len);
  BasicLog *getLog();
  void setLog(BasicLog *);
  Client *getClient();
  void setClient(Client *client);
  Position getPosition();
  const char *getPositionAsString();
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_MOONBOARD)
extern Panel Moonboard;
#endif

#endif // #ifndef _PANEL_H