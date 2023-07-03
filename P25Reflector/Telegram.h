/*
 *   Copyright (C) 2023 by Ralf Geiger DD7RG
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

#ifndef	Telegram_H
#define	Telegram_H


#include <cstdint>
#include <string>
#include <curl/curl.h>
#include "Log.h"

class CTelegram {
public:
	CTelegram();
	~CTelegram();

	bool open(const std::string &APIToken, const std::string &ChannelId, const bool &htmlenable);

	bool writeData(const std::string &Call, const std::string &Id, const std::string &Gateway);

	void close();

private:
	std::string m_apitoken;
	std::string m_channelid;
	bool        m_htmlenable;
	CURL*        m_curl;
	CURLcode    res;
};

#endif
