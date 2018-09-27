#include "Moonboard.h"

void Moonboard_SPI::begin(int csPin, int numDevices, unsigned long spiSpeedMax, BasicLog *_log)
{
  m_log = _log;
  m_log->debug3("init() start");
  lc.begin(csPin, numDevices, spiSpeedMax);
  //initialize displays (configure light intensity and clear all)
  for (byte i = 0; i < lc.getDeviceCount(); i++)
  {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }
  lc.setIntensity(MOONBOARD_START_DISP, 10); // Green LEDs are a bit weaker
  m_log->debug2("init done");
}

void Moonboard_SPI::lightHold(byte c, byte r)
{
  if (c < 0 || c > 10)
  {
    return;
  }
  if (r < 0 || r > 17)
  {
    return;
  }
  r += 6; // Start holds are rows 1 .. 6 (index 0-5)
  light(c, r);
}

void Moonboard_SPI::lightStartHold(byte c, byte r)
{
  if (c < 0 || c > 10)
  {
    return;
  }
  if (r < 0 || r > 5)
  {
    return;
  }
  light(c, r);
}

void Moonboard_SPI::lightEndHold(byte c, byte r)
{
  if (c < 0 || c > 10)
  {
    return;
  }
  if (r != 17)
  {
    return;
  } // Must be last row
  light(c, r);
}

void Moonboard_SPI::light(byte c, byte r)
{
  memcpy_P(data, led_map + (48 * c + 2 * r), 2);
  lc.setLed(data[0], data[1] >> 4, data[1] & 0xF, true);
  m_log->debug("lighting %i.%i.%i", data[0], data[1] >> 4, data[1] & 0xF);
}

int Moonboard_SPI::alphaToInt(char cc)
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

void Moonboard_SPI::processCmd(char *buf, int len)
{
  m_log->debug("rcvd \"%s\"", buf);
  byte index = 0;
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
  if (strcmp(cmdType, "HLD") == 0)
  {
    cmd = CMD_HLD;
  }
  else if (strcmp(cmdType, "STA") == 0)
  {
    cmd = CMD_STA;
  }
  else if (strcmp(cmdType, "END") == 0)
  {
    cmd = CMD_END;
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
    for (byte i = 0; i < lc.getDeviceCount(); i++)
    {
      lc.clearDisplay(i);
    }
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
  int row = -1;
  int col = -1;
  for (byte n = 0; n < index; n++)
  {
    m_log->debug2("lighting hold %s", holds[n]);
    byte cmdLen = strlen(holds[n]);
    for (byte i = 0; i < cmdLen; i++)
    {
      m_log->debug3("next ch: %c", (holds[n])[i]);
      if (col < 0)
      {
        col = alphaToInt((holds[n])[i]);
      }
      else if (row < 0)
      {
        row = alphaToInt((holds[n])[i]);
      }
      else
      {
        i = cmdLen;
      }
      m_log->debug2("col %i, row %i", col, row);
    }
    if (cmd == CMD_HLD)
    {
      lightHold(col, row);
    }
    if (cmd == CMD_STA)
    {
      lightStartHold(col, row);
    }
    if (cmd == CMD_END)
    {
      lightEndHold(col, row);
    }
    col = -1;
    row = -1;
  }
  m_client->print("ACK ");
  m_client->println(cmdId);
}

Client *Moonboard_SPI::getClient()
{
  return m_client;
}

void Moonboard_SPI::setClient(Client *client)
{
  m_client = client;
}

BasicLog *Moonboard_SPI::getLog()
{
  return m_log;
}

void Moonboard_SPI::setLog(BasicLog *_log)
{
  m_log = _log;
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_MOONBOARD)
Moonboard_SPI Moonboard;
#endif