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

#include "Sensor.hpp"

using namespace wifi_tft_display;

Sensor::Sensor() :
	humidity_( 0.0 ),
	temperature_( 0.0 )
{
	this->sensor_.begin();
	this->humidity_ = this->sensor_.readHumidity();
	this->temperature_ = this->sensor_.readTemperature();
}

Sensor & Sensor::instance()
{
	static Sensor instance;
	return instance;
}

float Sensor::getHumidity()
{
	return this->humidity_;
}

float Sensor::getTemperature()
{
	return this->temperature_;
}

void Sensor::setHeater(
	bool const ENABLED )
{
	this->sensor_.heater( ENABLED );
}

void Sensor::update()
{
	this->humidity_ = this->sensor_.readHumidity();
	this->temperature_ = this->sensor_.readTemperature();
}
