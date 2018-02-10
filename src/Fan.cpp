/////////////////////////////////////////////////////////////////////////////
//
// WiFi TFT Display
//
// Copyright (c) 2017 Colin Irwin
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// For all other enquiries, contact Colin Irwin at lagrangianpoint:
// colin@lagrangianpoint.net.
//
/////////////////////////////////////////////////////////////////////////////

#include "Fan.hpp"
#include "Arduino.h"

using namespace wifi_tft_display;

int const OUTPUT_FAN = D2;

Fan::Fan()
{
	pinMode( OUTPUT_FAN, OUTPUT );
	digitalWrite( OUTPUT_FAN, LOW );
}

Fan & Fan::instance()
{
	static Fan instance;
	return instance;
}

void Fan::disable()
{
	digitalWrite( OUTPUT_FAN, LOW );
	this->state_ = false;
}

void Fan::enable()
{
	digitalWrite( OUTPUT_FAN, HIGH );
	this->state_ = true;
}

bool Fan::status()
{
	return this->state_;
}
