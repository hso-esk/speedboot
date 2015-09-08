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
 * \file    util.hpp
 * \brief   Different values that are repeatedly used by the BasicUI class
 * 			are defined here to avoid magic constants and to avoid polluting
 * 			the BasicUI space.
 */

#ifndef UTIL_HPP_
#define UTIL_HPP_


/**
 * \brief 	Structure used to store different graphic representations used
 * 			by the BasicUI class.
 */
struct icon
{
	static const char *ARROW;
	static const char *SPACE;
	static const char *ASTERISKS;
};


/**
 * \brief 	Structure used to store different graphic representations used
 * 			by the BasicUI class.
 */
struct width
{
	static const int COLUMN = 10;
	static const int SEPARATOR = 5;
};

const char* icon::ARROW = " --->";
const char* icon::SPACE = "   ";
const char* icon::ASTERISKS = " *** ";


#endif /* #ifndef UTIL_HPP_ */
