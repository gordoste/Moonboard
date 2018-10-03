#ifndef _MOONBOARD_H
#define _MOONBOARD_H

#include <SSD1306Console.h>
#include "LedControl_HW_SPI.h"
#include "BasicLog.h"

#include "Arduino.h"

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <Wifi.h>
#endif

#define MOONBOARD_MAXHOLDS 20 // Maximum holds per problem

#define MOONBOARD_CS1 15 // D8
#define MOONBOARD_CS2 3  // D9
#define MOONBOARD_CS3 1  // D10

#define MOONBOARD_BLUERED_INTENSITY 8
#define MOONBOARD_GREEN_INTENSITY 10 // Green LEDs are a bit weaker

#define MOONBOARD_SPI_SPEED 1000000UL

#define MOONBOARD_BOTTOM_PANEL ledCtrl[0]
#define MOONBOARD_MIDDLE_PANEL ledCtrl[1]
#define MOONBOARD_TOP_PANEL ledCtrl[2]

const PROGMEM byte led_map[] = {
    // Column A
    B00000001, B01110000, B00000001, B01100000, B00000001, B01010000, B00000001, B01000000, B00000001, B00100000, B00000001, B00010000, B00000000, B01100000, B00000000, B01000000, // A1 - A8
    B00000000, B00100000, B00000000, B00000000, B00000011, B01010000, B00000011, B01000000, B00000011, B00110000, B00000011, B00100000, B00000011, B00010000, B00000011, B00000000, // A9 - A16
    B00000101, B01110000, B00000101, B01100000, B00000101, B01010000, B00000101, B01000000, B00000101, B00110000, B00000101, B00100000, B00000101, B00010000, B00000101, B00000000, // A17 - A24
    // Column B
    B00000001, B01110101, B00000001, B01010101, B00000001, B00110101, B00000001, B00110000, B00000001, B00010101, B00000001, B00000000, B00000000, B01110000, B00000000, B01010000, // B1 - B8
    B00000000, B00110000, B00000000, B00010000, B00000011, B01010001, B00000011, B01000001, B00000011, B00110001, B00000011, B00100001, B00000011, B00010001, B00000011, B00000001, // B9 - B16
    B00000101, B01110001, B00000101, B01100001, B00000101, B01010001, B00000101, B01000001, B00000101, B00110001, B00000101, B00100001, B00000101, B00010001, B00000101, B00000001, // B17 - B24
    // Column C
    B00000001, B01110001, B00000001, B01100001, B00000001, B01010001, B00000001, B01000001, B00000001, B00100001, B00000001, B00010001, B00000000, B01100001, B00000000, B01000001, // C1 - C8
    B00000000, B00100001, B00000000, B00000001, B00000011, B01010010, B00000011, B01000010, B00000011, B00110010, B00000011, B00100010, B00000011, B00010010, B00000011, B00000010, // C9 - C16
    B00000101, B01110010, B00000101, B01100010, B00000101, B01010010, B00000101, B01000010, B00000101, B00110010, B00000101, B00100010, B00000101, B00010010, B00000101, B00000010, // C17 - C24
    // Column D
    B00000001, B01100101, B00000001, B01000101, B00000001, B00100101, B00000001, B00110001, B00000001, B00000101, B00000001, B00000001, B00000000, B01110001, B00000000, B01010001, // D1 - D8
    B00000000, B00110001, B00000000, B00010001, B00000011, B01010011, B00000011, B01000011, B00000011, B00110011, B00000011, B00100011, B00000011, B00010011, B00000011, B00000011, // D9 - D16
    B00000101, B01110011, B00000101, B01100011, B00000101, B01010011, B00000101, B01000011, B00000101, B00110011, B00000101, B00100011, B00000101, B00010011, B00000101, B00000011, // D17 - D24
    // Column E
    B00000001, B01110010, B00000001, B01100010, B00000001, B01010010, B00000001, B01000010, B00000001, B00100010, B00000001, B00010010, B00000000, B01100010, B00000000, B01000010, // E1 - E8
    B00000000, B00100010, B00000000, B00000010, B00000011, B01010100, B00000011, B01000100, B00000011, B00110100, B00000011, B00100100, B00000011, B00010100, B00000011, B00000100, // E9 - E16
    B00000101, B01110100, B00000101, B01100100, B00000101, B01010100, B00000101, B01000100, B00000101, B00110100, B00000101, B00100100, B00000101, B00010100, B00000101, B00000100, // E17 - E24
    // Column F
    B00000001, B01110110, B00000001, B01010110, B00000001, B00110110, B00000001, B00110010, B00000001, B00010110, B00000001, B00000010, B00000000, B01110010, B00000000, B01010010, // F1 - F8
    B00000000, B00110010, B00000000, B00010010, B00000011, B01010101, B00000011, B01000101, B00000011, B00110101, B00000011, B00100101, B00000011, B00010101, B00000011, B00000101, // F9 - F16
    B00000101, B01110101, B00000101, B01100101, B00000101, B01010101, B00000101, B01000101, B00000101, B00110101, B00000101, B00100101, B00000101, B00010101, B00000101, B00000101, // F17 - F24
    // Column G
    B00000001, B01110011, B00000001, B01100011, B00000001, B01010011, B00000001, B01000011, B00000001, B00100011, B00000001, B00010011, B00000000, B01100011, B00000000, B01000011, // G1 - G8
    B00000000, B00100011, B00000000, B00000011, B00000010, B01010000, B00000010, B01000000, B00000010, B00110000, B00000010, B00100000, B00000010, B00010000, B00000010, B00000000, // G9 - G16
    B00000100, B01110000, B00000100, B01100000, B00000100, B01010000, B00000100, B01000000, B00000100, B00110000, B00000100, B00100000, B00000100, B00010000, B00000100, B00000000, // G17 - G24
    // Column H
    B00000001, B01100110, B00000001, B01000110, B00000001, B00100110, B00000001, B00110011, B00000001, B00000110, B00000001, B00000011, B00000000, B01110011, B00000000, B01010011, // H1 - H8
    B00000000, B00110011, B00000000, B00010011, B00000010, B01010001, B00000010, B01000001, B00000010, B00110001, B00000010, B00100001, B00000010, B00010001, B00000010, B00000001, // H9 - H16
    B00000100, B01110001, B00000100, B01100001, B00000100, B01010001, B00000100, B01000001, B00000100, B00110001, B00000100, B00100001, B00000100, B00010001, B00000100, B00000001, // H17 - H24
    // Column I
    B00000001, B01110100, B00000001, B01100100, B00000001, B01010100, B00000001, B01000100, B00000001, B00100100, B00000001, B00010100, B00000000, B01100100, B00000000, B01000100, // I1 - I8
    B00000000, B00100100, B00000000, B00000100, B00000010, B01010010, B00000010, B01000010, B00000010, B00110010, B00000010, B00100010, B00000010, B00010010, B00000010, B00000010, // I9 - I16
    B00000100, B01110010, B00000100, B01100010, B00000100, B01010010, B00000100, B01000010, B00000100, B00110010, B00000100, B00100010, B00000100, B00010010, B00000100, B00000010, // I17 - I24
    // Column J
    B00000001, B10000000, B00000001, B01110111, B00000001, B01010111, B00000001, B00110100, B00000001, B00100111, B00000001, B00000100, B00000000, B01110100, B00000000, B01010100, // J1 - J8
    B00000000, B00110100, B00000000, B00010100, B00000010, B01010011, B00000010, B01000011, B00000010, B00110011, B00000010, B00100011, B00000010, B00010011, B00000010, B00000011, // J9 - J16
    B00000100, B01110011, B00000100, B01100011, B00000100, B01010011, B00000100, B01000011, B00000100, B00110011, B00000100, B00100011, B00000100, B00010011, B00000100, B00000011, // J17 - J24
    // Column K
    B00000001, B10000001, B00000001, B01100111, B00000001, B01000111, B00000001, B00110111, B00000001, B00010111, B00000001, B00000111, B00000000, B01100101, B00000000, B01000101, // K1 - K8
    B00000000, B00100101, B00000000, B00000101, B00000010, B01010100, B00000010, B01000100, B00000010, B00110100, B00000010, B00100100, B00000010, B00010100, B00000010, B00000100, // K9 - K16
    B00000100, B01110100, B00000100, B01100100, B00000100, B01010100, B00000100, B01000100, B00000100, B00110100, B00000100, B00100100, B00000100, B00010100, B00000100, B00000100, // K17 - K24
};

enum Command
{
  CMD_SET = 0,
  CMD_CLR = 1
};

class Moonboard_Controller
{
private:
  byte data[2];
  char *holds[MOONBOARD_MAXHOLDS];
  char *ptr;
  LedControl_HW_SPI ledCtrl[3] = {
    LedControl_HW_SPI(),
    LedControl_HW_SPI(),
    LedControl_HW_SPI()
  };
  int cmd;
  char *cmdId;
  char *cmdType;
  Client *m_client;
  BasicLog *m_log;

  int alphaToInt(char cc);

public:
  Moonboard_Controller(){};
  void begin(BasicLog *_log);
  void light(uint8_t c, uint8_t r);
  void clear();
  void processCmd(char *buf, int len);
  BasicLog *getLog();
  void setLog(BasicLog *);
  Client *getClient();
  void setClient(Client *client);
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_MOONBOARD)
extern Moonboard_Controller Moonboard;
#endif

#endif // #ifndef_MOONBOARD_H