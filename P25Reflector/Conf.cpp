/*
 *   Copyright (C) 2015,2016,2020 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "Conf.h"
#include "Log.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

const int BUFFER_SIZE = 500;

enum SECTION {
  SECTION_NONE,
  SECTION_GENERAL,
  SECTION_ID_LOOKUP,
  SECTION_LOG,
  SECTION_NETWORK,
  SECTION_TELEGRAM
};

CConf::CConf(const std::string& file) :
m_file(file),
m_daemon(false),
m_lookupName(),
m_lookupTime(0U),
m_logDisplayLevel(0U),
m_logFileLevel(0U),
m_logFilePath(),
m_logFileRoot(),
m_logFileRotate(true),
m_networkPort(0U),
m_networkDebug(false),
m_TelegramBotEnable(false),
m_TelegramBotHTMLEnable(false),
m_TelegramBotAPIToken(),
m_TelegramBotChannelId()

{
}

CConf::~CConf()
{
}

bool CConf::read()
{
  FILE* fp = ::fopen(m_file.c_str(), "rt");
  if (fp == NULL) {
    ::fprintf(stderr, "Couldn't open the .ini file - %s\n", m_file.c_str());
    return false;
  }

  SECTION section = SECTION_NONE;

  char buffer[BUFFER_SIZE];
  while (::fgets(buffer, BUFFER_SIZE, fp) != NULL) {
	  if (buffer[0U] == '#')
		  continue;

	  if (buffer[0U] == '[') {
		  if (::strncmp(buffer, "[General]", 9U) == 0)
			  section = SECTION_GENERAL;
		  else if (::strncmp(buffer, "[Id Lookup]", 11U) == 0)
			  section = SECTION_ID_LOOKUP;
		  else if (::strncmp(buffer, "[Log]", 5U) == 0)
			  section = SECTION_LOG;
		  else if (::strncmp(buffer, "[Network]", 9U) == 0)
			  section = SECTION_NETWORK;
		  else if (::strncmp(buffer, "[Telegram Bot]", 14U) == 0)
			  section = SECTION_TELEGRAM;
		  else
			  section = SECTION_NONE;

		  continue;
	  }

	  char* key = ::strtok(buffer, " \t=\r\n");
	  if (key == NULL)
		  continue;

	  char* value = ::strtok(NULL, "\r\n");
	  if (value == NULL)
		  continue;

	  // Remove quotes from the value
	  size_t len = ::strlen(value);
	  if (len > 1U && *value == '"' && value[len - 1U] == '"') {
		  value[len - 1U] = '\0';
		  value++;
	  } else {
		  char *p;

		  // if value is not quoted, remove after # (to make comment)
		  if ((p = strchr(value, '#')) != NULL)
			  *p = '\0';

		  // remove trailing tab/space
		  for (p = value + strlen(value) - 1U; p >= value && (*p == '\t' || *p == ' '); p--)
			  *p = '\0';
	  }

	  if (section == SECTION_GENERAL) {
		  if (::strcmp(key, "Daemon") == 0)
			  m_daemon = ::atoi(value) == 1;
	  } else if (section == SECTION_ID_LOOKUP) {
		  if (::strcmp(key, "Name") == 0)
			  m_lookupName = value;
		  else if (::strcmp(key, "Time") == 0)
			  m_lookupTime = (unsigned int)::atoi(value);
	  } else if (section == SECTION_LOG) {
		  if (::strcmp(key, "FilePath") == 0)
			  m_logFilePath = value;
		  else if (::strcmp(key, "FileRoot") == 0)
			  m_logFileRoot = value;
		  else if (::strcmp(key, "FileLevel") == 0)
			  m_logFileLevel = (unsigned int)::atoi(value);
		  else if (::strcmp(key, "DisplayLevel") == 0)
			  m_logDisplayLevel = (unsigned int)::atoi(value);
		  else if (::strcmp(key, "FileRotate") == 0)
			  m_logFileRotate = ::atoi(value) == 1;
	  } else if (section == SECTION_NETWORK) {
		  if (::strcmp(key, "Port") == 0)
			  m_networkPort = (unsigned short)::atoi(value);
		  else if (::strcmp(key, "Debug") == 0)
			  m_networkDebug = ::atoi(value) == 1;
	  } else if (section == SECTION_TELEGRAM) {
		  if (::strcmp(key, "Enable") == 0)
			  m_TelegramBotEnable = ::atoi(value) == 1;
		  else if (::strcmp(key, "HTMLEnable") == 0)
			  m_TelegramBotHTMLEnable = ::atoi(value) == 1;
		  else if (::strcmp(key, "APIToken") == 0)
			  m_TelegramBotAPIToken = value;
		  else if (::strcmp(key, "ChannelId") == 0)
			  m_TelegramBotChannelId = value;
	  } 
  }

  ::fclose(fp);

  return true;
}

bool CConf::getDaemon() const
{
	return m_daemon;
}

std::string CConf::getLookupName() const
{
	return m_lookupName;
}

unsigned int CConf::getLookupTime() const
{
	return m_lookupTime;
}

unsigned int CConf::getLogDisplayLevel() const
{
	return m_logDisplayLevel;
}

unsigned int CConf::getLogFileLevel() const
{
	return m_logFileLevel;
}

std::string CConf::getLogFilePath() const
{
  return m_logFilePath;
}

std::string CConf::getLogFileRoot() const
{
  return m_logFileRoot;
}

bool CConf::getLogFileRotate() const
{
	return m_logFileRotate;
}

unsigned short CConf::getNetworkPort() const
{
	return m_networkPort;
}

bool CConf::getNetworkDebug() const
{
	return m_networkDebug;
}

bool CConf::getTelegramBotEnable() const
{
	return m_TelegramBotEnable;
}

bool CConf::getTelegramBotHTMLEnable() const
{
	return m_TelegramBotHTMLEnable;
}


std::string CConf::getTelegramBotAPIToken() const
{
  return m_TelegramBotAPIToken;
}

std::string CConf::getTelegramBotChannelId() const
{
  return m_TelegramBotChannelId;
}


