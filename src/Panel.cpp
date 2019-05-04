#include "Panel.h"

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
      light(alphaToInt(holds[n][0]), alphaToInt(holds[n][1]));
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
