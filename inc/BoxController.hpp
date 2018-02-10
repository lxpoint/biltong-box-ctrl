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

#if !defined( WIFI_TFT_DISPLAY_BOXCONTROLLER_HPP )
#define WIFI_TFT_DISPLAY_BOXCONTROLLER_HPP

#include "Events.hpp"
#include "Fan.hpp"
#include "Sensor.hpp"
#include "TftDisplay.hpp"
#include "TouchScreen.hpp"

#include <cstdint>

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/in_state_reaction.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/mpl/list.hpp>

namespace wifi_tft_display
{


struct SystemActive;
struct StatusDisplay;
struct TopLevelMenu;
struct AwaitingInput;
struct ButtonClockPressed;
struct ButtonHumidityPressed;
struct ButtonReturnPressed;
struct ButtonTemperaturePressed;
struct FanMenu;
struct FanMenuPowerPressed;
struct FanMenuPowerUnpressed;
struct FanMenuAutoPressed;
struct FanMenuAutoUnpressed;
struct FanMenuReturnPressed;
struct FanMenuReturnUnpressed;

struct FanOff;
struct FanOn;


//! \brief ??
struct BoxController : boost::statechart::state_machine< BoxController, SystemActive >
{
};


//! \brief ??
struct SystemActive : boost::statechart::simple_state< SystemActive, BoxController, boost::mpl::list< FanOff, StatusDisplay > >
{
};


//! \brief ??
struct FanOff : boost::statechart::simple_state< FanOff, SystemActive::orthogonal< 0 > >
{
	public:
		//! \brief ??
		FanOff()
		{
			Fan::instance().disable();
		}

	public:
		//! \brief ??
		typedef boost::statechart::transition< EvtFan, FanOn > reactions;
};


//! \brief ??
struct FanOn : boost::statechart::simple_state< FanOn, SystemActive::orthogonal< 0 > >
{
	public:
		//! \brief ??
		FanOn()
		{
			Fan::instance().enable();
		}

	public:
		//! \brief ??
		typedef boost::statechart::transition< EvtFan, FanOff > reactions;
};


//! \brief ??
struct StatusDisplay : boost::statechart::simple_state< StatusDisplay, SystemActive::orthogonal< 1 > >
{
	public:
		//! \brief ??
		StatusDisplay()
		{
			TftDisplay & display = TftDisplay::instance();
			display.clear();
			display.displayIcons();
			display.displayTime( Time.hour(), Time.minute() );
			display.displayHumidity( Sensor::instance().getHumidity() );
			display.displayTemperature( Sensor::instance().getTemperature() );
		}

		//! \brief ??
		//! \param EVENT ??
		void update(
			EvtUpdateStatus const & EVENT )
		{
			TftDisplay & display = TftDisplay::instance();
			display.updateTime( Time.hour(), Time.minute() );
			display.updateTemperature( Sensor::instance().getTemperature() );
			display.updateHumidity( Sensor::instance().getHumidity() );
		}

	public:
		typedef boost::mpl::list<
			boost::statechart::transition< EvtScreenPressed, TopLevelMenu >,
			boost::statechart::in_state_reaction< EvtUpdateStatus, StatusDisplay, &StatusDisplay::update > > reactions;
};


//! \brief ??
struct TopLevelMenu : boost::statechart::simple_state< TopLevelMenu, SystemActive::orthogonal< 1 >, AwaitingInput >
{
	public:
		//! \brief ??
		TopLevelMenu()
		{
			TftDisplay::instance().displayButtons();
		}
};


//! \brief ??
struct AwaitingInput : boost::statechart::simple_state< AwaitingInput, TopLevelMenu >
{
	public:
		//! \brief ??
		AwaitingInput()
		{
		}

		//! \brief ??
		boost::statechart::result react( EvtScreenPressed const & )
		{
			TS_Point location = TouchScreen::instance().getPoint();
			if ( ( location.x > 130 ) && ( location.y > 30 ) && ( location.x < 224 ) && ( location.y < 150 ) )
			{
				return transit< ButtonTemperaturePressed >();
			}
			if ( ( location.x > 130 ) && ( location.y > 170 ) && ( location.x < 224 ) && ( location.y < 290 ) )
			{
				return transit< ButtonClockPressed >();
			}
			if ( ( location.x > 16 ) && ( location.y > 30 ) && ( location.x < 110 ) && ( location.y < 150 ) )
			{
				return transit< ButtonHumidityPressed >();
			}
			if ( ( location.x > 16 ) && ( location.y > 170 ) && ( location.x < 110 ) && ( location.y < 290 ) )
			{
				return transit< ButtonReturnPressed >();
			}
			return transit< AwaitingInput >();
		}

	public:
		//! \brief ??
		typedef boost::statechart::custom_reaction< EvtScreenPressed > reactions;
};


struct ButtonClockPressed : boost::statechart::simple_state< ButtonClockPressed, TopLevelMenu >
{
	public:
		//! \brief ??
		ButtonClockPressed()
		{
			TftDisplay::instance().btnClockPressed();
		}

	public:
		//! \brief ??
		typedef boost::statechart::transition< EvtScreenReleased, FanMenu > reactions;
};


struct ButtonHumidityPressed : boost::statechart::simple_state< ButtonHumidityPressed, TopLevelMenu >
{
	public:
		//! \brief ??
		ButtonHumidityPressed()
		{
			TftDisplay::instance().btnHumidityPressed();
		}

	public:
		//! \brief ??
		typedef boost::statechart::transition< EvtScreenReleased, StatusDisplay > reactions;
};


struct ButtonReturnPressed : boost::statechart::simple_state< ButtonReturnPressed, TopLevelMenu >
{
	public:
		//! \brief ??
		ButtonReturnPressed()
		{
			TftDisplay::instance().btnReturnPressed();
		}

	public:
		//! \brief ??
		typedef boost::statechart::transition< EvtScreenReleased, StatusDisplay > reactions;
};


struct ButtonTemperaturePressed : boost::statechart::simple_state< ButtonTemperaturePressed, TopLevelMenu >
{
	public:
		//! \brief ??
		ButtonTemperaturePressed()
		{
			TftDisplay::instance().btnTemperaturePressed();
		}

	public:
		//! \brief ??
		typedef boost::statechart::transition< EvtScreenReleased, StatusDisplay > reactions;
};


//! \brief ??
struct FanMenu : boost::statechart::simple_state< FanMenu, SystemActive::orthogonal< 1 >, boost::mpl::list< FanMenuPowerUnpressed, FanMenuAutoUnpressed, FanMenuReturnUnpressed > >
{
	public:
		//! \brief ??
		FanMenu()
		{
			TftDisplay::instance().menuFan();
		}

		//! \brief ??
		//! \param EVENT ??
		boost::statechart::result react(
			EvtScreenPressed const & )
		{
			TS_Point location = TouchScreen::instance().getPoint();
			if ( ( location.x > 130 ) && ( location.y > 30 ) && ( location.x < 224 ) && ( location.y < 150 ) )
			{
				post_event( EvtBtnPower() );
			}
			else if ( ( location.x > 130 ) && ( location.y > 170 ) && ( location.x < 224 ) && ( location.y < 290 ) )
			{
				post_event( EvtBtnAuto() );
			}
			else if ( ( location.x > 16 ) && ( location.y > 170 ) && ( location.x < 110 ) && ( location.y < 290 ) )
			{
				post_event( EvtBtnReturn() );
			}
			return discard_event();
		}

		//! \brief ??
		//! \param EVENT ??
		boost::statechart::result react(
			EvtScreenReleased const & )
		{
			TS_Point location = TouchScreen::instance().getPoint();
			if ( ( location.x > 130 ) && ( location.y > 30 ) && ( location.x < 224 ) && ( location.y < 150 ) )
			{
				post_event( EvtBtnPower() );
			}
			else if ( ( location.x > 130 ) && ( location.y > 170 ) && ( location.x < 224 ) && ( location.y < 290 ) )
			{
				post_event( EvtBtnAuto() );
			}
			else if ( ( location.x > 16 ) && ( location.y > 170 ) && ( location.x < 110 ) && ( location.y < 290 ) )
			{
				post_event( EvtBtnReturn() );
//				return transit< TopLevelMenu >();
			}
			return discard_event();
		}

		//! \brief ??
		//! \param EVENT ??
/*
		void btnReturnPressed(
			EvtBtnReturn const & )
		{
			TftDisplay::instance().btnReturnPressed();
		}
*/

	public:
		//! \brief ??
		typedef boost::mpl::list<
			boost::statechart::custom_reaction< EvtScreenPressed >,
			boost::statechart::custom_reaction< EvtScreenReleased > > reactions;
};


//! \brief ??
struct FanMenuPowerPressed : boost::statechart::simple_state<
	FanMenuPowerPressed, FanMenu::orthogonal< 0 > >
{
	public:
		//! \brief ??
		FanMenuPowerPressed()
		{
			TftDisplay::instance().btnPowerPressed();
			Fan::instance().enable();
		}

	public:
		//! \brief ??
		typedef boost::statechart::transition< EvtBtnPower, FanMenuPowerUnpressed > reactions;
};


//! \brief ??
struct FanMenuPowerUnpressed : boost::statechart::simple_state<
	FanMenuPowerUnpressed, FanMenu::orthogonal< 0 > >
{
	public:
		//! \brief ??
		FanMenuPowerUnpressed()
		{
			TftDisplay::instance().btnPowerUnpressed();
			Fan::instance().disable();
		}

	public:
		//! \brief ??
		typedef boost::statechart::transition< EvtBtnPower, FanMenuPowerPressed > reactions;
};


//! \brief ??
struct FanMenuAutoPressed : boost::statechart::simple_state<
	FanMenuAutoPressed, FanMenu::orthogonal< 1 > >
{
	public:
		//! \brief ??
		FanMenuAutoPressed()
		{
			TftDisplay::instance().btnAutoPressed();
		}

	public:
		//! \brief ??
		typedef boost::statechart::transition< EvtBtnAuto, FanMenuAutoUnpressed > reactions;
};


//! \brief ??
struct FanMenuAutoUnpressed : boost::statechart::simple_state<
	FanMenuAutoUnpressed, FanMenu::orthogonal< 1 > >
{
	public:
		//! \brief ??
		FanMenuAutoUnpressed()
		{
			TftDisplay::instance().btnAutoUnpressed();
		}

	public:
		//! \brief ??
		typedef boost::statechart::transition< EvtBtnAuto, FanMenuAutoPressed > reactions;
};


//! \brief ??
struct FanMenuReturnUnpressed : boost::statechart::simple_state<
	FanMenuReturnUnpressed, FanMenu::orthogonal< 2 > >
{
	public:
		//! \brief ??
		FanMenuReturnUnpressed()
		{
			TftDisplay::instance().btnReturnUnpressed();
		}

	public:
		//! \brief ??
		typedef boost::statechart::transition< EvtBtnReturn, FanMenuReturnPressed > reactions;
};


//! \brief ??
struct FanMenuReturnPressed : boost::statechart::simple_state<
	FanMenuReturnPressed, FanMenu::orthogonal< 2 > >
{
	public:
		//! \brief ??
		FanMenuReturnPressed()
		{
			TftDisplay::instance().btnReturnPressed();
		}

	public:
		//! \brief ??
		typedef boost::statechart::transition< EvtBtnReturn, TopLevelMenu > reactions;
};


}

#endif
