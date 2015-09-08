/* 
* SpeedBoot, a boot time optimization tool
*
* Copyright (c) 2015,
* Hochschule Offenburg, University of Applied Sciences
* Laboratory Embedded Systems and Communications Electronics.
*
*
* This file is part of SpeedBoot.
*
* SpeedBoot is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* SpeedBoot is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with SpeedBoot.  If not, see <http://www.gnu.org/licenses/>.
*
* This work is licensed under the terms of the GNU GPL, version 2. For the full
* license text please refer to the COPYING file in the top-level directory.
*/

/**
 * \file    Entry.cpp
 * \brief   Entry class implementation
 */

/*============================================================================*/
/*                                INCLUDES                                    */
/*============================================================================*/

#include "model/entry/Entry.hpp"
#include <stdlib.h> // gentenv()
#include <sstream>  //ostringstream
#include "libs/parser/2.6.39/lkc.h"    //parser

#include "model/entry/measurement.hpp"
#include "model/kconfig_option/KconfigOption.hpp"

using namespace std;

/*============================================================================*/
/*		                          CLASS METHODS		                          */
/*============================================================================*/

Entry::Entry(struct menu *new_menu)
    :mWrappedMenu(new_menu) // set the menu struct to be wrapped
	{
	// Note: It is assumed that the Entry class only wraps menu struct
	// that have a prompt. i.e. menu->prompt != NULL
	}

bool Entry::operator==(const Entry& other) const
{
	// The addresses of the pointers are compared, not the actual content
	if(this->mWrappedMenu == other.mWrappedMenu)
		return true;
	return false;
}

bool Entry::isMenu() const
{
	// A Kconfig menu entry can't be a config option.
	if(mWrappedMenu->prompt->type == P_MENU && mWrappedMenu->sym == NULL)
		return true;
	return false;
}

bool Entry::isMenuconfig() const
{
	// A Kconfig menuconfig entry is both a menu and a config option
	if(mWrappedMenu->prompt->type == P_MENU && mWrappedMenu->sym != NULL)
		return true;
	return false;
}

bool Entry::isComment() const
{
	if(mWrappedMenu->prompt->type == P_COMMENT)
		return true;
	return false;
}

bool Entry::isChoice() const
{
	// Only a menu struct containing a symbol can be a Kconfig choice
	if(mWrappedMenu->sym == NULL)
		return false;
	else
		return sym_is_choice(mWrappedMenu->sym);
}

bool Entry::isOption() const
{
	// first check if the this instance is not of any of the other types
	if(this->isComment())
		return false;
	if(this->isMenuconfig())
		return false;
	if(this->isMenu())
		return false;
	if(this->isChoice())
		return false;
	if(mWrappedMenu->sym == NULL)
		return false;
	return true;
}

KconfigOption Entry::getOption() const
{
	return KconfigOption(mWrappedMenu->sym);
}

bool Entry::isVisible() const
{
    return menu_is_visible(mWrappedMenu);
    //NOTE: menu_is_visible has side effect that
    // it will recalc the value of the symbol
}

string Entry::getPrompt() const
{
    return menu_get_prompt(mWrappedMenu);
}

string Entry::getHelpText(int max_width) const
{
	// allocate a growable string structure
	struct gstr help = str_new();
	// limit the max width of the printed string
	help.max_width = max_width;
	// put the help string into the growable string
	menu_get_ext_help(mWrappedMenu, &help);
	// deep copy the text into a string instance
	string help_text(str_get(&help));
	// deallocate the growable string
	str_free(&help);
	return help_text;
}

string Entry::printBootingTime() const
{
	return this->printInfo(true);
}

float Entry::calculateBootingTime() const
{
	return this->calculateInfoValue(true);
}

string Entry::printSize() const
{
	return this->printInfo(false);
}

float Entry::calculateSize() const
{
	return this->calculateInfoValue(false);
}

float Entry::calculateInfoValue(bool time) const
{
	// get the value regardless of the state: enable, mod, no
	if(this->isOption())
		return (time == true) ? getOption().getBootingTime()
							  : getOption().getSize();
	// Only get the value for the Kconfig options that are enabled or mod
	else
		return menu_calc_prop(mWrappedMenu, time);
}

string Entry::printInfo(bool time) const
{
	ostringstream out;

	/** getInfoType */
	enum info_type entry_type;
	if(this->isOption())
	{
		// For Kconfig options, we do not care about its state
		struct property* prop = NULL;
		prop = (time == true) ? sym_get_time_prop(mWrappedMenu->sym)
							  : sym_get_size_prop(mWrappedMenu->sym);
		// Ignore string, hex and int by default
		enum symbol_type type = sym_get_type(mWrappedMenu->sym);
		if(prop == NULL && (type == S_STRING || type == S_HEX || type == S_INT))
			entry_type = I_UNAPPLICABLE;
		else // account for tristate, bool or explicit string, hex, int
			entry_type = prop_get_info_type(prop);
	}
	// For Organizational elements, the state of the children is important
	else
		entry_type = menu_get_info_type(this->mWrappedMenu, time);
	/** EOF getInfoType */

	// store the precision character first
	switch(entry_type)
	{
	case I_COARSE:
		out << measurement::APROX;
		break;
	case I_EXACT:
		out << measurement::EXACT;
		break;
	case I_UNKNOWN:
		return measurement::UNKNOWN;
	case I_UNAPPLICABLE:
		return measurement::EMPTY;
	}
	// Now calculate the value and store it
	out << calculateInfoValue(time);
	return out.str();
}
