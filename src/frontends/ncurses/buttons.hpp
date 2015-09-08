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

/*
 * \file    buttons.hpp
 * \brief   lxdialog buttons value definition.
 * 			Every screen type in lxdialog (menu, choice, yes_no, string_input)
 * 			has their own buttons mapping, therefore a mapping of buttons to
 * 			integers must be done for each one to avoid confusion and to avoid
 * 			having duplicate definitions.
 * 			Note: This mapping is independent of lxdialog, i.e. if the lxdialog
 * 			values are changed, then these values will no longer be valid.
 */

#ifndef BUTTONS_HPP_
#define BUTTONS_HPP_

/**
 * \brief 	Structure used to store the button values that are returned by
 * 			dialog_menu() in case the user presses one of them.
 */
struct buttonMenu { enum value
	{
		SELECT = 0,
		EXIT = 1,
		HELP = 2,
		SAVE = 3,
		LOAD = 4
	};
};


/**
 * \brief 	Structure used to store the button values that are returned by
 * 			dialog_checklist() in case the user presses one of them.
 */
struct buttonChoice { enum value
	{
		SELECT = 0,
		HELP = 1
	};
};


/**
 * \brief 	Structure used to store the button values that are returned by
 * 			dialog_yesno() in case the user presses one of them.
 */
struct buttonYesNo { enum value
	{
		YES = 0,
		NO = 1
	};
};


/**
 * \brief 	Structure used to store the button values that are returned by
 * 			dialog_inputbox() in case the user presses one of them.
 */
struct buttonString { enum value
	{
		OK_ = 0,
		HELP = 1
	};
};

#endif /* #ifndef BUTTONS_HPP_ */
