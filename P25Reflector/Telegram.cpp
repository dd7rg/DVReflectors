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

#include "Telegram.h"
#include "Utils.h"
#include "Log.h"

#include <cstdio>
#include <cassert>
#include <cstring>
#include <curl/curl.h>

CTelegram::CTelegram()
{
}

CTelegram::~CTelegram()
{
}

bool CTelegram::open( const std::string &APIToken, const std::string &Channelid, const bool &htmlenable)
{
	m_curl = curl_easy_init();
	curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
	m_apitoken = APIToken;
	m_channelid = Channelid;
	m_htmlenable = htmlenable;
	LogInfo("Opening Telegram Bot connection with curl");
	return 0;

}

bool CTelegram::writeData(const std::string &Call, const std::string &Id, const std::string &Gateway)
{
	std::string url = m_apitoken + "sendMessage?chat_id=" + m_channelid + "&text=TTCall: " + Call + " Id: " + Id + " Gateway: " + Gateway;
	std::string url_html = "\"" + m_apitoken + "sendMessage?parse_mode=HTML&chat_id=" + m_channelid + "&text=Call:%20<a%20href=\\\"https://www.qrz.com/lookup/" + Call + "/?timestamp\\\"><b>" + Call + "</b></a>%20Id:%20" + Id + "%20Gateway:%20\""; // + Gateway +"\"";

        if(!m_htmlenable) {
                curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
                LogInfo("URL for Telegram used: %s", url.c_str());
        }
        else
        {
                curl_easy_setopt(m_curl, CURLOPT_URL, url_html.c_str());
                LogInfo("URL for Telegram used: %s", url_html.c_str());

        }

	res = curl_easy_perform(m_curl);
	if(res != CURLE_OK)
	{
		LogInfo("Telegram did not work %s" , curl_easy_strerror(res));
	}
	else
	{
	LogInfo("Writing Telegram Bot Information");
	}
	return 0;


}

void CTelegram::close()
{
        curl_easy_cleanup(m_curl);
	LogInfo("Closing Telegram Bot connection");

}
