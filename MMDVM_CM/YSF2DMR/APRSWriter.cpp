/*
 *   Copyright (C) 2010-2014,2016,2017 by Jonathan Naylor G4KLX
 *   Copyright (C) 2018 by Manuel Sanchez EA7EE
 *   Copyright (C) 2018 by Andy Uribe CA6JAU
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

#include "APRSWriter.h"

#include "YSFDefines.h"

#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>

CAPRSWriter::CAPRSWriter(const std::string& callsign, const std::string& suffix, const std::string& password, const std::string& address, unsigned int port) :
m_thread(NULL),
m_enabled(false),
m_idTimer(1000U, 20U * 60U),		// 20 minutes
m_callsign(callsign),
m_txFrequency(0U),
m_rxFrequency(0U),
m_latitude(0.0F),
m_longitude(0.0F),
m_height(0),
m_desc()
{
	assert(!callsign.empty());
	assert(!password.empty());
	assert(!address.empty());
	assert(port > 0U);

	if (!suffix.empty()) {
		m_callsign.append("-");
		m_callsign.append(suffix.substr(0U, 1U));
	}

	m_thread = new CAPRSWriterThread(m_callsign, password, address, port);
}

CAPRSWriter::~CAPRSWriter()
{
}

void CAPRSWriter::setInfo(unsigned int txFrequency, unsigned int rxFrequency, float latitude, float longitude, int height, const std::string& desc)
{
	m_txFrequency = txFrequency;
	m_rxFrequency = rxFrequency;
	m_latitude    = latitude;
	m_longitude   = longitude;
	m_height      = height;
	m_desc        = desc;
}

bool CAPRSWriter::open()
{
	m_idTimer.start();
	return m_thread->start();
}

void CAPRSWriter::write(const unsigned char* source, const char* type, unsigned char radio, float fLatitude, float fLongitude, unsigned int tg_qrv)
{
	assert(source != NULL);
	assert(type != NULL);

	char callsign[11U];

	::memcpy(callsign, source, YSF_CALLSIGN_LENGTH);
	callsign[YSF_CALLSIGN_LENGTH] = 0x00U;

	int n = ::strspn(callsign, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	callsign[n] = 0x00U;

	double tempLat = ::fabs(fLatitude);
	double tempLong = ::fabs(fLongitude);

	double latitude = ::floor(tempLat);
	double longitude = ::floor(tempLong);

	latitude = (tempLat - latitude)  * 60.0 + latitude  * 100.0;
	longitude = (tempLong - longitude) * 60.0 + longitude * 100.0;

	char lat[20U];
	::sprintf(lat, "%07.2lf", latitude);

	char lon[20U];
	::sprintf(lon, "%08.2lf", longitude);

	char symbol;
	char suffix[3];
	switch (radio) {
	case 0x24U:
	case 0x28U:
		symbol = '[';
		strcpy(suffix, "-7");
		break;
	case 0x25U:
	case 0x29U:
		symbol = '>';
		strcpy(suffix, "-9");
		break;
	case 0x26U:
		symbol = 'r';
		strcpy(suffix, "-1");
		break;
	case 0x27U:
		symbol = '-';
		strcpy(suffix, "-2");
		break;		
	default:
		symbol = '-';
		strcpy(suffix, "-2");
		break;
	}
	
	char output[300U];
	::sprintf(output, "%s%s>APDPRS,C4FM*,qAR,%s:!%s%c/%s%c%c %s QRV TG %d via MMDVM",
		callsign, suffix, m_callsign.c_str(),
		lat, (fLatitude < 0.0F) ? 'S' : 'N',
		lon, (fLongitude < 0.0F) ? 'W' : 'E',
		symbol, type, tg_qrv);

	m_thread->write(output);
}

void CAPRSWriter::clock(unsigned int ms)
{
	m_idTimer.clock(ms);

	if (m_idTimer.hasExpired()) {
		//sendIdFrames();
		m_idTimer.start();
	}
}

void CAPRSWriter::close()
{
	m_thread->stop();
}

void CAPRSWriter::sendIdFrames()
{
	if (!m_thread->isConnected())
		return;

	// Default values aren't passed on
	if (m_latitude == 0.0F && m_longitude == 0.0F)
		return;

	char desc[200U];
	if (m_txFrequency != 0U) {
		float offset = float(int(m_rxFrequency) - int(m_txFrequency)) / 1000000.0F;
		::sprintf(desc, "MMDVM Voice %.5LfMHz %c%.4lfMHz%s%s",
			(long double)(m_txFrequency) / 1000000.0F,
			offset < 0.0F ? '-' : '+',
			::fabs(offset), m_desc.empty() ? "" : "; ", m_desc.c_str());
	} else {
		::sprintf(desc, "MMDVM Voice%s%s", m_desc.empty() ? "" : "; ", m_desc.c_str());
	}

	const char* band = "4m";
	if (m_txFrequency >= 1200000000U)
		band = "23cm/1.2GHz";
	else if (m_txFrequency >= 420000000U)
		band = "70cm";
	else if (m_txFrequency >= 144000000U)
		band = "2m";
	else if (m_txFrequency >= 50000000U)
		band = "6m";
	else if (m_txFrequency >= 28000000U)
		band = "10m";

	double tempLat  = ::fabs(m_latitude);
	double tempLong = ::fabs(m_longitude);

	double latitude  = ::floor(tempLat);
	double longitude = ::floor(tempLong);

	latitude  = (tempLat  - latitude)  * 60.0 + latitude  * 100.0;
	longitude = (tempLong - longitude) * 60.0 + longitude * 100.0;

	char lat[20U];
	::sprintf(lat, "%07.2lf", latitude);

	char lon[20U];
	::sprintf(lon, "%08.2lf", longitude);

	std::string server = m_callsign;
	size_t pos = server.find_first_of('-');
	if (pos == std::string::npos)
		server.append("-S");
	else
		server.append("S");

        char output[1500U];
        ::sprintf(output, "%s>APDG03,TCPIP*,qAC,%s:!%s%cW%s%ci/A=%06.0f%s %s\r\n%s>APDG03:>Powered by W0CHP-PiStar-Dash (https://wpsd.w0chp.net)\r\n",                                               
                m_callsign.c_str(), server.c_str(),
                lat, (m_latitude < 0.0F)  ? 'S' : 'N',
                lon, (m_longitude < 0.0F) ? 'W' : 'E',
                float(m_height) * 3.28F, band, desc,
                m_callsign.c_str());

	m_thread->write(output);

	m_idTimer.start();
}
