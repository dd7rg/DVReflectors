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
        struct curl_slist *slist1;
        slist1 = NULL;
        slist1 = curl_slist_append(slist1, "Content-Type: application/json");
        curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, slist1);

        std::string url = m_apitoken + "sendMessage";

        char* channelid = curl_easy_escape(m_curl, m_channelid.c_str(),0);
        std::string strtext;
        std::string data;

        if(!m_htmlenable) {
                strtext = ("Call: " + Call + " Id: " + Id + " Gateway: " + Gateway);
                data = "{\"chat_id\":\"" + std::string(channelid) +"\", \"text\":\"" + strtext +"\"}";
        }
        else
        {
                strtext = ("Call: <a href=\\\"https://www.qrz.com/lookup/" + Call + "\\\"><b>" + Call + "</b></a> Id: " + Id + " Gateway:" + Gateway);
                data = "{ \"parse_mode\":\"HTML\",\"chat_id\":\"" + std::string(channelid) +"\", \"disable_web_page_preview\": true, \"text\":\"" + strtext +"\"}";
        }

        curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, (long)strlen(data.c_str()));
        curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
        //LogInfo("URL for Telegram used: %s Data: %s", url.c_str() , data.c_str());


        res = curl_easy_perform(m_curl);
        if(res != CURLE_OK)
        {
                LogInfo("Telegram did not work %s" , curl_easy_strerror(res));
        }
        else
        {
                LogInfo("Writing Telegram Bot Information");
        }

        curl_free(channelid);
        curl_slist_free_all(slist1);
        slist1 = NULL;

        return 0;
}

void CTelegram::close()
{
        curl_easy_cleanup(m_curl);
	LogInfo("Closing Telegram Bot connection");

}
