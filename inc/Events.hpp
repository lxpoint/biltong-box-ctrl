/////////////////////////////////////////////////////////////////////////////
//
// Nixie Clock
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

#if !defined( WIFI_TFT_DISPLAY_EVENTS_HPP )
#define WIFI_TFT_DISPLAY_EVENTS_HPP

#include <boost/statechart/event.hpp>

namespace wifi_tft_display
{

//! \brief ??
struct EvtBtnAuto : boost::statechart::event< EvtBtnAuto >
{
};

//! \brief ??
struct EvtBtnPower : boost::statechart::event< EvtBtnPower >
{
};

//! \brief ??
struct EvtBtnReturn : boost::statechart::event< EvtBtnReturn >
{
};

//! \brief ??
struct EvtChangeMode : boost::statechart::event< EvtChangeMode >
{
};

//! \brief ??
struct EvtScreenPressed : boost::statechart::event< EvtScreenPressed >
{
};

//! \brief ??
struct EvtScreenReleased : boost::statechart::event< EvtScreenReleased >
{
};

//! \brief ??
struct EvtUpdateStatus : boost::statechart::event< EvtUpdateStatus >
{
};

}

#endif
