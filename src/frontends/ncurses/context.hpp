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
 * \file    context.hpp
 * \brief   BasicUi context definition
 * 			Every possible screen type in lxdialog is named here to provide
 * 			a way to the the BasicUI Class to know to which screen to return
 * 			without using a recursion model.
 * 			This model creates a status-tracking problem but it improves
 * 			the maintainability, debugging and isolation of each step, as
 * 			each method can isolated and debugged purely by what is defined
 * 			inside of it, and not by any carried-bug from previous steps.
 */

#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_


/**
 * \brief 	Structure used to store the possible context types that the BasicUI class
 * 			can have.
 */
struct context { enum value
	{
		MENU,
		CHOICE,
		LOAD,
		SAVE,
		SEARCH,
		INPUTBOX
	};
};

#endif /* #ifndef CONTEXT_HPP_ */
