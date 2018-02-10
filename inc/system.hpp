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

#if !defined( WIFI_TFT_DISPLAY_SYSTEM_HPP )
#define WIFI_TFT_DISPLAY_SYSTEM_HPP

#include "Arduino.h"

//! Constant declarations.

//! \brief ??
int const RELAY_1 = D2;

//! \brief ??
int const RELAY_2 = D3;

//! \brief ??
int const RELAY_3 = D4;


//! Function declarations.

//! \brief ??
void callbackFanOff();

//! \brief ??
void callbackFanOn();

//! \brief ??
void callbackPublishStatus();

//! \brief ??
void callbackSensorUpdate();

//! \brief ??
void callbackTouchScreen();

//! \brief ??
void callbackUpdateDisplay();

//! \brief ??
void callbackUpdateTime();

//! \brief ??
//! \param command ??
int cloudFan(
	String command );

//! \brief ??
//! \param command ??
int cloudHeater(
	String command );

//! \brief ??
//! \param command ??
int cloudHumidifier(
	String command );

#endif
