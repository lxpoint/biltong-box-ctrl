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

#if !defined( WIFI_TFT_DISPLAY_SENSOR_HPP )
#define WIFI_TFT_DISPLAY_SENSOR_HPP

#include "Adafruit_SHT31.h"

namespace wifi_tft_display
{

//! \brief ??
class Sensor
{
    public:
        //! \brief ??
        //! \return ??
		static Sensor & instance();

    public:
        //! \brief ??
		//! \param RHS ??
 		Sensor(
			Sensor const & RHS ) = delete;

        //! \brief ??
		//! \param RHS ??
        void operator=(
			Sensor const & RHS ) = delete;

        //! \brief ??
		//! \return ??
		float getHumidity();

        //! \brief ??
		//! \return ??
		float getTemperature();

        //! \brief ??
		//! \param ENABLED ??
		void setHeater(
			bool const ENABLED );

        //! \brief ??
		void update();

	private:
        //! \brief ??
        Sensor();

	private:
        //! \brief ??
		float humidity_;

        //! \brief ??
		Adafruit_SHT31 sensor_;

        //! \brief ??
		float temperature_;
};

}

#endif
