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
 * \file    commands.hpp
 * \brief   lxdialog commands' value definition.
 *			The lxdialog api maps different keyboard inputs into integer
 *			values; these values are mapped here to improve clarity and
 *			to avoid having duplicate definitions.
 * 			Note: This mapping is independent of lxdialog, i.e. if the
 * 			lxdialog values are changed, then these values will no longer
 * 			be valid.
 */

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

/**
 * \brief 	Structure used to store the mapping of keyboard input into user interface
 * 			actions. */
struct command { enum values
	{
		EXIT = 1,
		YES = 5,
		NO = 6,
		MOD = 7,
		TOGGLE = 8,
		SEARCH = 9,
		SHOW_ALL = 10
	};
};


#endif /* #ifndef COMMANDS_HPP_ */
