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

#include "application.h"
#include "system.hpp"
#include "BoxController.hpp"
#include "Fan.hpp"
#include "Heater.hpp"
#include "Humidifier.hpp"
#include "Sensor.hpp"
#include "TftDisplay.hpp"
#include "TouchScreen.hpp"

#include <cstring>

using namespace wifi_tft_display;

// Timer (one-shot) for turning off the fan:	after 5 minutes.
uint32_t const TIME_FAN_OFF_MS = 1 * 60 * 1000;
Timer timerFanOff( TIME_FAN_OFF_MS, callbackFanOff, true );

// Timer (one-shot) for turning on the fan:		after 5 minutes.
uint32_t const TIME_FAN_ON_MS = 20 * 60 * 1000;
Timer timerFanOn( TIME_FAN_ON_MS, callbackFanOn, true );

// Timer for publishing the current status:		every 60 seconds.
uint32_t const TIME_PUBLISH_STATUS_MS = 60 * 1000;
Timer timerPublishStatus( TIME_PUBLISH_STATUS_MS, callbackPublishStatus );

// Timer for retrieving the sensor values:		every 10 seconds.
uint32_t const TIME_SENSOR_UPDATE_MS = 10 * 1000;
Timer timerSensorUpdate( TIME_SENSOR_UPDATE_MS, callbackSensorUpdate );

// Timer for checking the touchscreen: 			every 50 ms.
uint32_t const TIME_TOUCHSCREEN_MS = 50;
Timer timerTouchScreen( TIME_TOUCHSCREEN_MS, 	callbackTouchScreen );

// Timer for updating the display: 				every 10 seconds.
uint32_t const TIME_UPDATE_DISPLAY_MS = 10 * 1000;
Timer timerUpdateDisplay( TIME_UPDATE_DISPLAY_MS, callbackUpdateDisplay );

// Timer for updating the system time: 			every 10 minutes.
uint32_t const TIME_UPDATE_TIME_MS = 10 * 60 * 1000;
Timer timerUpdateTime( TIME_UPDATE_TIME_MS, 	callbackUpdateTime );

char stringBuffer[ 9 ];
bool flagFanOff = false;
bool flagFanOn = false;
bool flagPublishStatus = false;
bool flagScreenPressed = false;
bool flagSensorUpdate = false;
bool flagTouchScreen = false;
bool flagUpdateDisplay = false;
bool flagUpdateTime = false;
BoxController boxController;

STARTUP( WiFi.selectAntenna( ANT_EXTERNAL ) );

void callbackFanOff()
{
	flagFanOff = true;
}

void callbackFanOn()
{
	flagFanOn = true;
}

void callbackPublishStatus()
{
	flagPublishStatus = true;
}

void callbackSensorUpdate()
{
	flagSensorUpdate = true;
}

void callbackTouchScreen()
{
	flagTouchScreen = true;
}

void callbackUpdateDisplay()
{
	flagUpdateDisplay = true;
}

void callbackUpdateTime()
{
	flagUpdateTime = true;
}

int cloudFan(
	String command )
{
	return 1;
}

int cloudHeater(
	String command )
{
	return 1;
}

int cloudHumidifier(
	String command )
{
	return 1;
}

void loop()
{
	if ( flagFanOff )
	{
		Fan::instance().disable();
		Heater::instance().disable();
		timerFanOn.start();
		flagFanOff = false;
	}

	if ( flagFanOn )
	{
		Fan::instance().enable();
		Heater::instance().enable();
		timerFanOff.start();
		flagFanOn = false;
	}

	if ( flagPublishStatus )
	{
		// Status: temperature
		sprintf( stringBuffer, "%2.1f", Sensor::instance().getTemperature() );
		Particle.publish( "temperature:", stringBuffer, PRIVATE );

		// Status: humidity
		sprintf( stringBuffer, "%2.1f", Sensor::instance().getHumidity() );
		Particle.publish( "humidity:", stringBuffer, PRIVATE );

		// Status: fan
		if ( Fan::instance().status() )
		{
			std::strcpy( stringBuffer, "on" );
		}
		else
		{
			std::strcpy( stringBuffer, "off" );
		}
		Particle.publish( "fan:", stringBuffer, PRIVATE );

		// Status: heater

		// Status: humidifier

		flagPublishStatus = false;
	}

	if ( flagSensorUpdate )
	{
		Sensor::instance().update();
		flagSensorUpdate = false;
	}

	if ( flagTouchScreen )
	{
		bool pressDetected = TouchScreen::instance().touched();
		if ( pressDetected && !flagScreenPressed )
		{
			flagScreenPressed = true;
			boxController.process_event( EvtScreenPressed() );
		}
		else if ( !pressDetected && flagScreenPressed )
		{
			flagScreenPressed = false;
			boxController.process_event( EvtScreenReleased() );
		}
		flagTouchScreen = false;
	}

	if ( flagUpdateDisplay )
	{
		boxController.process_event( EvtUpdateStatus() );
		flagUpdateDisplay = false;
	}

	if ( flagUpdateTime )
	{
		Particle.syncTime();
		flagUpdateTime = false;
	}

//	Humidifier::instance().update();
}

void setup()
{
	// Set up the cloud functions for control.
	Particle.function( "fan",		cloudFan );
	Particle.function( "heater",	cloudHeater );
	Particle.function( "humidifer", cloudHumidifier );

	// Set the clock's time, currently +1 UTC.
	Time.zone( 1 );

	// Enable the humidifier.
//	Humidifier::instance().enable();

	boxController.initiate();

	// Start the timers.
	timerFanOn.start();
	timerPublishStatus.start();
	timerSensorUpdate.start();
	timerTouchScreen.start();
	timerUpdateDisplay.start();
	timerUpdateTime.start();

//	Fan::instance().enable();
//	Heater::instance().enable();
}
