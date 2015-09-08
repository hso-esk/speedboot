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
 * \file    tags.hpp
 * \brief   lxdialog item tags definition.
 * 			Every item that is inserted using the lxdialog api, requires a
 * 			tag to be set for later retrieval and comparison.
 * 			Note: This mapping is independent of lxdialog, i.e. if the lxdialog
 * 			values are changed, then these values will no longer be valid.
 * 			So far only the choice_value tag is necessary to be 'X', all other
 * 			values were chosen manually.
 */

#ifndef TAGS_HPP_
#define TAGS_HPP_


/**
 * \brief 	Structure used to store the lxdialog item tags used by
 * 			the BasicUI class to indentify stored entries.
 */
struct tag { enum values
	{
		MENU = 'm',
		MENUCONFIG = 'n',
		COMMENT = '*',
		CHOICE = 'c',
		CHOICE_VALUE = 'X',
		OPTION = 's',
		LABEL = 'T',
		UNKNOWN = 'E'
	};
};

#endif /* #ifndef TAGS_HPP_ */
