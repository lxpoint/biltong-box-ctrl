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

#if !defined( WIFI_TFT_DISPLAY_TFTDISPLAY_HPP )
#define WIFI_TFT_DISPLAY_TFTDISPLAY_HPP

#include "Adafruit_ILI9341.h"

namespace wifi_tft_display
{

//! \brief ??
class TftDisplay
{
    public:
        //! \brief ??
        //! \return ??
		static TftDisplay & instance();

    public:
        //! \brief ??
		//! \param RHS ??
 		TftDisplay(
			TftDisplay const & RHS ) = delete;

        //! \brief ??
		//! \param RHS ??
        void operator=(
			TftDisplay const & RHS ) = delete;

        //! \brief ??
		void clear();

        //! \brief ??
		void btnAutoPressed();

        //! \brief ??
		void btnAutoUnpressed();

        //! \brief ??
		void btnClockPressed();

        //! \brief ??
		void btnHumidityPressed();

        //! \brief ??
		void btnPowerPressed();

        //! \brief ??
		void btnPowerUnpressed();

        //! \brief ??
		void btnReturnPressed();

        //! \brief ??
		void btnReturnUnpressed();

        //! \brief ??
		void btnTemperaturePressed();

        //! \brief ??
		void btnClockUnPressed();

        //! \brief ??
		void btnHumidityUnPressed();

        //! \brief ??
		void btnTemperatureUnPressed();

        //! \brief ??
		void displayButtons();

        //! \brief ??
		//! \param HUMIDITY ??
		void displayHumidity(
			float const HUMIDITY );

        //! \brief ??
		void displayIcons();

        //! \brief ??
		void displayStatus();

        //! \brief ??
		//! \param TEMPERATURE ??
		void displayTemperature(
			float const TEMPERATURE );

        //! \brief ??
		//! \param HOURS ??
		//! \param MINUTES ??
		void displayTime(
			uint8_t const HOURS,
			uint8_t const MINUTES );

        //! \brief ??
		void menuFan();

        //! \brief ??
		//! \param HUMIDITY ??
		void updateHumidity(
			float const HUMIDITY );

        //! \brief ??
		//! \param TEMPERATURE ??
		void updateTemperature(
			float const TEMPERATURE );

        //! \brief ??
		//! \param HOURS ??
		//! \param MINUTES ??
		void updateTime(
			uint8_t const HOURS,
			uint8_t const MINUTES );

	private:
        //! \brief ??
        TftDisplay();

	private:
        //! \brief ??
		Adafruit_ILI9341 display_;

        //! \brief ??
		uint8_t previousHours_;

        //! \brief ??
		char previousHumidity_[ 7 ];

        //! \brief ??
		uint8_t previousMinutes_;

        //! \brief ??
		char previousTemperature_[ 7 ];
};

}

#endif
