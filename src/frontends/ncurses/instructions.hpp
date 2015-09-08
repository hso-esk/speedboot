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
 * \file    isntructions.hpp
 * \brief   lxdialog user interface instructions.
 * 			Every screen in lxdialog (main menu, search, load, save,
 * 			inputbox, exit) needs to provide the user with information about
 * 			how to navigate and interact with it, such information is saved
 * 			here to avoid polluting the BasicUI class space.
 */

#ifndef INSTRUCTIONS_HPP_
#define INSTRUCTIONS_HPP_


/**
 * \brief 	Structure used to store char pointers to the instruction definitions
 * 			of each screen possible in lxdialog.
 */
struct instructions
{
public:
	static const char *GUI;
	static const char *CHOICE;
	static const char *INPUTBOX_INT;
	static const char *INPUTBOX_HEX;
	static const char *INPUTBOX_STRING;
	static const char *MODULE;
	static const char *LOAD_CONFIG;
	static const char *SAVE_CONFIG;
	static const char *SEARCH;
	static const char *EXIT;
};

const char *instructions::GUI =
		"Arrow keys navigate the menu.  "
		"<Enter> selects submenus --->.  "
		"Highlighted letters are hotkeys.  "
		"Pressing <Y> includes, <N> excludes, <M> modularizes features.  "
		"Press <Esc><Esc> to exit, <?> for Help, </> for Search.  "
		"Legend: [*] built-in  [ ] excluded  <M> module  < > module capable";

const char *instructions::CHOICE =
		"Use the arrow keys to navigate this window or "
		"press the hotkey of the item you wish to select "
		"followed by the <SPACE BAR>. "
		"Press <?> for additional information about this option.";

const char *instructions::INPUTBOX_INT =
		"Please enter a decimal value. "
		"Fractions will not be accepted.  "
		"Use the <TAB> key to move from the input field to the buttons below it.";

const char *instructions::INPUTBOX_HEX =
		"Please enter a hexadecimal value. "
		"Use the <TAB> key to move from the input field to the buttons below it.";

const char *instructions::INPUTBOX_STRING =
		"Please enter a string value. "
			"Use the <TAB> key to move from the input field to the buttons below it.";

const char *instructions::MODULE =
		"This feature depends on another which has been configured as a module.\n"
		"As a result, this feature will be built as a module.";

const char *instructions::LOAD_CONFIG =
		"Enter the name of the configuration file you wish to load.  "
		"Accept the name shown to restore the configuration you "
		"last retrieved.  Leave blank to abort.";

const char *instructions::SAVE_CONFIG =
		"Enter a filename to which this configuration should be saved "
		"as an alternate.  Leave blank to abort.";

const char *instructions::SEARCH =
		"Enter CONFIG (sub)string to search for (with or without CONFIG_";

const char *instructions::EXIT =
		"Do you wish to save your new configuration ? <ESC><ESC> to continue. ";

#endif /* INSTRUCTIONS_HPP_ */
