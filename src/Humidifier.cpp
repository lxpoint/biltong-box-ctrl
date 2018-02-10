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

#include "Arduino.h"
#include "Humidifier.hpp"
#include "Sensor.hpp"

using namespace wifi_tft_display;

// Starting humidity level.
double const HUMIDITY_DEFAULT = 70.0;

// Output pin for humidifier control
int const OUTPUT_HUMIDIFIER = D3;

// Window size of 2 minutes.
int const WINDOW_SIZE = 2 * 60 * 1000;

Humidifier::Humidifier() :
	humidity_( HUMIDITY_DEFAULT ),
	input_( HUMIDITY_DEFAULT ),
	pidController_( &this->input_, &this->output_, &this->humidity_, 2, 5, 1, P_ON_M, DIRECT ),
	windowStartTime_( millis() )
{
	pinMode( OUTPUT_HUMIDIFIER, OUTPUT );
	digitalWrite( OUTPUT_HUMIDIFIER, LOW );
	this->pidController_.SetOutputLimits( 0, WINDOW_SIZE );
}

Humidifier & Humidifier::instance()
{
	static Humidifier instance;
	return instance;
}

void Humidifier::disable()
{
	this->pidController_.SetMode( MANUAL );
}

void Humidifier::enable()
{
	this->pidController_.SetMode( AUTOMATIC );
}

void Humidifier::setHumidity(
	double const HUMIDITY )
{
	if ( ( this->humidity_ >= 0.0 ) &&
		( this->humidity_ <= 100.0 ) )
	{
		this->humidity_ = HUMIDITY;
	}
}

void Humidifier::update()
{
	// Get the latest humidity level.
	this->input_ = Sensor::instance().getHumidity();

	// Update the PID.
	this->pidController_.Compute();

	// Shift the relay window if the current time has progressed beyond the last
	unsigned long now = millis();
	if ( ( now - this->windowStartTime_ ) > WINDOW_SIZE )
	{
		this->windowStartTime_ += WINDOW_SIZE;
	}

	// Turn the humidifier on/off based on the PID output.
	if ( this->output_ > ( now - this->windowStartTime_ ) )
	{
		digitalWrite( OUTPUT_HUMIDIFIER, HIGH );
	}
	else
	{
		digitalWrite( OUTPUT_HUMIDIFIER, LOW );
	}
}
