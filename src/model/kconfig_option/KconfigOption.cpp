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
 * \file    KconfigOption.cpp
 * \brief   KconfigOption class implementation
 */

/*============================================================================*/
/*                                INCLUDES                                    */
/*============================================================================*/

#include "model/kconfig_option/KconfigOption.hpp"
#include <sstream>  //ostringstream
#include <stdlib.h> // gentenv() strtof
#include "libs/parser/2.6.39/lkc.h"// parser

using namespace std;

/*============================================================================*/
/*		                          CLASS METHODS		                          */
/*============================================================================*/

KconfigOption::KconfigOption(struct symbol *new_symbol)
    :mWrappedSymbol(new_symbol)// set the menu struct to be wrapped
	{}

bool KconfigOption::isRewritable() const
{
	// Only these three types allow string values i.e write operation
	switch(sym_get_type(mWrappedSymbol))
	{
	case S_HEX:
	case S_INT:
	case S_STRING:
		return true;
	}
	return false;
}

bool KconfigOption::isInteger() const
{
	if(sym_get_type(mWrappedSymbol) == S_INT)
		return true;
	return false;
}

bool KconfigOption::isString() const
{
	if(sym_get_type(mWrappedSymbol) == S_STRING)
		return true;
	return false;
}

bool KconfigOption::isHexadecimal() const
{
	if(sym_get_type(mWrappedSymbol) == S_HEX)
		return true;
	return false;
}

bool KconfigOption::setValue(string new_value)
{
	return sym_set_string_value(mWrappedSymbol, new_value.c_str());
}

bool KconfigOption::setValue(char new_value)
{
	// Any not defined value is ignored and results in error
	switch(new_value)
	{
	case YES:
		return sym_set_tristate_value(mWrappedSymbol, yes);
	case NO:
		return sym_set_tristate_value(mWrappedSymbol, no);
	case MOD:
		return sym_set_tristate_value(mWrappedSymbol, mod);
	}
	// ERROR
	return false;
}

bool KconfigOption::setValue(KconfigOption& new_value)
{
	return sym_set_choice_value(this->mWrappedSymbol, new_value.mWrappedSymbol);
}

string KconfigOption::valueToString() const
{
	// get the value of the Kconfig option
	string value = sym_get_string_value(mWrappedSymbol);
	// If this option is a choice, the value is the selected symbol prompt
	if(sym_is_choice(mWrappedSymbol) && sym_get_tristate_value(mWrappedSymbol) == yes)
	{
		KconfigOption choice_value(sym_get_choice_value(mWrappedSymbol));
		return choice_value.getPrompt();
	}
	// for boolean and tristate transform the value to the printable
	// convention
	if(value == "n")
		value = NO;
	else if(value == "y")
		value = YES;
	else if(value == "m")
		value = MOD;

	return value;
}

string KconfigOption::getPrompt()
{
	// Check if this Kconfig option has a prompt property stored in it.
	struct property* prop = NULL;
	for_all_properties(mWrappedSymbol, prop, P_PROMPT)
		return prop->text;
	// Make sure to return a value in case no prompt was found
	return sym_get_string_value(mWrappedSymbol);
}

string KconfigOption::wrapValue(bool& visible) const
{
	string value = this->valueToString();

	// The following are the printing conventions used by default
	// in the lxdialog menuconfig GUI.
	if(sym_is_choice(mWrappedSymbol))
	{
		return (visible == true) ? " (" + value + ") "
								 : " ";
	}

	switch(sym_get_type(mWrappedSymbol))
	{
	case S_BOOLEAN:
		if(visible)
			return "[" + value + "] ";
		else
			return "-" + value + "- ";
	case S_TRISTATE:
		return "<" + value + "> ";
	case S_HEX:
	case S_INT:
	case S_STRING:
		return "(" + value + ") ";
	default: // S_UNKNOWN
		return "### "; // ERROR
	}
}

void KconfigOption::toggleTristate()
{
	sym_toggle_tristate_value(mWrappedSymbol);
}

bool KconfigOption::isEnable() const
{
	if(sym_get_tristate_value(mWrappedSymbol) == yes)
		return true;
	return false;
}

float KconfigOption::getBootingTime() const
{
	return this->getInfoValue(true);
}

float KconfigOption::getSize() const
{
	return this->getInfoValue(false);
}

float KconfigOption::getInfoValue(bool get_time) const
{
	// Check if this Kconfig option has a time property defined
	struct property* info_prop = NULL;
	info_prop = (get_time == true) ? sym_get_time_prop(mWrappedSymbol)
								   : sym_get_size_prop(mWrappedSymbol);
	if(info_prop != NULL)
		// convert the string value to a float
		return strtof( info_prop->expr->left.sym->name, NULL);
	return 0;
}
