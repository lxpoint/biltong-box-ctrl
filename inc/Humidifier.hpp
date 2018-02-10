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

#if !defined( WIFI_TFT_DISPLAY_HUMIDIFIER_HPP )
#define WIFI_TFT_DISPLAY_HUMIDIFIER_HPP

#include "PID_v1.h"

namespace wifi_tft_display
{

//! \brief ??
class Humidifier
{
    public:
        //! \brief ??
        //! \return ??
		static Humidifier & instance();

    public:
        //! \brief ??
		//! \param RHS ??
 		Humidifier(
			Humidifier const & RHS ) = delete;

        //! \brief ??
		//! \param RHS ??
        void operator=(
			Humidifier const & RHS ) = delete;

        //! \brief ??
		void disable();

        //! \brief ??
		void enable();

        //! \brief ??
		//! \param ENABLED ??
		void setHumidity(
			double const HUMIDITY );

        //! \brief ??
		void update();

	private:
        //! \brief ??
        Humidifier();

	private:
        //! \brief ??
		double humidity_;

        //! \brief ??
		double input_;

        //! \brief ??
		double output_;

        //! \brief ??
		PID pidController_;

        //! \brief ??
		unsigned long windowStartTime_;
};

}

#endif
