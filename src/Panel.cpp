#include "Panel.h"

/*void Moonboard_Controller::begin(BasicLog *_log)
{
  m_log = _log;
  m_log->debug3("init start");
  MOONBOARD_BOTTOM_PANEL.begin(MOONBOARD_CS1, 2, MOONBOARD_SPI_SPEED);
  MOONBOARD_MIDDLE_PANEL.begin(MOONBOARD_CS2, 2, MOONBOARD_SPI_SPEED);
  MOONBOARD_TOP_PANEL.begin(MOONBOARD_CS3, 2, MOONBOARD_SPI_SPEED);
  for (uint8_t d = 0; d < 3; d++)
  {
    for (uint8_t i = 0; i < ledCtrl[d].getDeviceCount(); i++)
    {
      ledCtrl[d].shutdown(i, false);
    }
  }
  clear();
  MOONBOARD_BOTTOM_PANEL.setIntensity(0, MOONBOARD_GREEN_INTENSITY);
  MOONBOARD_BOTTOM_PANEL.setIntensity(1, MOONBOARD_BLUERED_INTENSITY);
  MOONBOARD_MIDDLE_PANEL.setIntensity(0, MOONBOARD_BLUERED_INTENSITY);
  MOONBOARD_MIDDLE_PANEL.setIntensity(1, MOONBOARD_BLUERED_INTENSITY);
  MOONBOARD_TOP_PANEL.setIntensity(0, MOONBOARD_BLUERED_INTENSITY);
  MOONBOARD_TOP_PANEL.setIntensity(1, MOONBOARD_BLUERED_INTENSITY);
  m_log->debug2("init done");
}*/

void Panel::clear()
{
  for (uint8_t i = 0; i < ledCtrl.getDeviceCount(); i++)
  {
    ledCtrl.clearDisplay(i);
  }
}

/*void Moonboard_Controller::light(uint8_t c, uint8_t r)
{
  m_log->debug3("light(%i,%i)", c, r);
  memcpy_P(data, led_map + (48 * c + 2 * r), 2);
  uint8_t disp;
  if (r < 10) // Bottom panel
  {
    if (r < 6) // yellow region in layout.xlsx
    {
      disp = 1;
    }
    else // blue region in layout.xlsx
    {
      disp = 0;
    }
    m_log->debug("bottom d%ir%ic%i", disp, data[1] >> 4, data[1] & 0xF);
    MOONBOARD_BOTTOM_PANEL.setLed(disp, data[1] >> 4, data[1] & 0xF, true);
  }
  else if (r >= 10 && r < 18) // Middle panel
  {
    if (c < 6) // gold region in layout.xlsx
    {
      disp = 1;
    }
    else // grey region in layout.xlsx
    {
      disp = 0;
    }
    m_log->debug("middle d%ir%ic%i", disp, data[1] >> 4, data[1] & 0xF);
    MOONBOARD_MIDDLE_PANEL.setLed(disp, data[1] >> 4, data[1] & 0xF, true);
  }
  else // Top panel
  {
    if (c < 6) // pink region in layout.xlsx
    {
      disp = 1;
    }
    else // green region in layout.xlsx
    {
      disp = 0;
    }
    m_log->debug("top d%ir%ic%i", disp, data[1] >> 4, data[1] & 0xF);
    MOONBOARD_TOP_PANEL.setLed(disp, data[1] >> 4, data[1] & 0xF, true);
  }
}*/

int Panel::alphaToInt(char cc)
{
  if (cc >= 'a' && cc <= 'z')
  {
    return cc - 'a';
  }
  if (cc >= 'A' && cc <= 'Z')
  {
    return cc - 'A';
  }
  return -1;
}

void Panel::processCmd(char *buf, int len)
{
  m_log->debug("rcvd \"%s\"", buf);
  uint8_t index = 0;
  char token[2] = " "; // need room for null terminator
  // First grab the command type - HLD=normal, STA=start, END=end
  ptr = strtok(buf, token);
  if (ptr == NULL)
  {
    m_client->println("ERR NOCMD");
    m_log->log("no command");
    return;
  }
  cmdType = ptr;
  if (strcmp(cmdType, "SET") == 0)
  {
    cmd = CMD_SET;
  }
  else if (strcmp(cmdType, "CLR") == 0)
  {
    cmd = CMD_CLR;
  }
  else
  {
    m_client->println("ERR BADCMD");
    m_log->log("bad command");
    return;
  }
  // Then grab the command ID
  ptr = strtok(NULL, token);
  if (ptr == NULL)
  {
    m_client->println("ERR NOID");
    m_log->log("command had no ID");
    return;
  }
  cmdId = ptr;
  if (cmd == CMD_CLR)
  {
    m_log->log("clearing board");
    clear();
    m_client->print("ACK ");
    m_client->println(cmdId);
    return;
  }
  ptr = strtok(NULL, token);
  while (ptr && index < MOONBOARD_MAXHOLDS)
  {
    holds[index++] = ptr;
    ptr = strtok(NULL, token);
  }
  for (uint8_t n = 0; n < index; n++)
  {
    m_log->debug2("hold #%i: %s", n, holds[n]);
    uint8_t holdLen = strlen(holds[n]);
    if (holdLen == 2)
    {
      Moonboard.light(alphaToInt(holds[n][0]), alphaToInt(holds[n][1]));
    }
    else
    {
      m_log->log("hold '%s' has bad length (%i)", holds[n], holdLen);
    }
  }
  m_client->print("ACK ");
  m_client->println(cmdId);
}

Client *Panel::getClient()
{
  return m_client;
}

void Panel::setClient(Client *client)
{
  m_client = client;
}

BasicLog *Panel::getLog()
{
  return m_log;
}

void Panel::setLog(BasicLog *_log)
{
  m_log = _log;
}

Position Panel::getPosition()
{
  return m_pos;
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_MOONBOARD)
Panel Moonboard;
#endif