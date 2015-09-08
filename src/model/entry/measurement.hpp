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
 * \file    measurement.hpp
 * \brief   measurement precision prefix definition
 */

#ifndef MEASUREMENT_HPP_
#define MEASUREMENT_HPP_

/**
 * \brief 	Structure used to store the possible prefixes used to distinguish
 * 			the precision type of the Kconfig entries, these values are stored
 * 			inside a struct to avoid polluting the global space.
 */
struct measurement
{
public:
    static const char* UNKNOWN;
    static const char* APROX;
    static const char* EXACT;
    static const char* EMPTY;
};

const char* measurement::APROX = "~";
const char* measurement::UNKNOWN = "?";
const char* measurement::EXACT = "+";
const char* measurement::EMPTY = " ";

#endif /* #ifndef MEASUREMENT_HPP_ */
