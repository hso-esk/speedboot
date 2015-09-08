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
 * \file    BasicUI.hpp
 * \brief   BasicUI class declaration
 */

#ifndef BASIC_UI_HPP_
#define BASIC_UI_HPP_

/*============================================================================*/
/*                                INCLUDES                                    */
/*============================================================================*/

class Entry;
class Navigator;
class KConfigHandler;

#include <vector>
#include <utility>
#include <string>
#include "frontends/ncurses/context.hpp"

/*============================================================================*/
/*		                    CLASS PROTOTYPE 				                  */
/*============================================================================*/

/**
 * \brief Class used encapsulate the graphical user interface. It uses the lxdialog
 * api to draw the graphic into a terminal.
 */
class BasicUI
{
private:
	/** \brief Software Name to display at the GUI */
	static const char* 	UI_TITLE;

	/** \brief Version of the software */
	static const char* 	VERSION;

	/** \brief Instance used to navigate through the Kconfig tree created
	 * 			by the parser */
	Navigator&			mNavigator;

	/** \brief Container of the current entries being in the UI */
	std::vector<Entry> 	mEntries;

	/** \brief Current entry to which the user requested an action */
	Entry* 				mCurrentEntry;

	/** \brief Manager of the .config files; read, write, check changes */
	KConfigHandler&		mKconfig;

	/** \brief Current context at which the interface is; used for
	 * status-tracking */
	context::value		mCurrentContext;

	/** \brief Used to avoid printing text while the lxdialog api is
	 * running. This operation is not possible by default. */
	std::string 		mTerminalOutput;

	/** \brief Used to stored the possible effects that a user action
	 * 		   may carry */
	enum uiAction { DO_ABORT, DO_EXIT, DO_SHOW_EXIT, DO_SHOW_MENU,
				 	DO_SHOW_HELP, DO_SHOW_SAVE, DO_SHOW_LOAD, DO_SHOW_CHOICE,
				 	DO_SHOW_INPUTBOX, DO_SHOW_SEARCH };


    /**
     * \brief  	shows a menu dialog using the lxdialog api. The values displayed
     * 			are read from the mEntries member variable.
     *
     * \return  uiAction signaling the next method to call or abort if not
     * 			enough space is found on the screen.
     */
	uiAction showMenu();


    /**
     * \brief  	shows a checklist dialog using the lxdialog api. The values
     * 			displayed are read from the mEntries member variable.
     *
     * \return  uiAction signaling the next method to call or abort if not
     * 			enough space is found on the screen.
     */
	uiAction showChoice();


	/**
     * \brief  	shows an exit confirmation dialog in case that the user might
     * 			have not saved his current changes.
     *
     * \return  uiAction signaling the next method to call or abort if not
     * 			enough space is found on the screen.
     */
	uiAction showExit();


	/**
     * \brief  	shows an textbox dialog with help information about the
     * 			requested item or interface.
     *
     * \return  uiAction signaling the next method to call or abort if not
     * 			enough space is found on the screen.
     */
	uiAction showHelp();


	/**
     * \brief  	shows an inputbox dialog to enter the filename and path
     * 			of the configuration file to load.
     *
     * \return  uiAction signaling the next method to call or abort if not
     * 			enough space is found on the screen.
     */
	uiAction showLoad();


	/**
     * \brief  	shows an inputbox dialog to enter the filename and path
     * 			of the destination file of the current configuration.
     *
     * \return  uiAction signaling the next method to call or abort if not
     * 			enough space is found on the screen.
     */
	uiAction showSave();


	/**
     * \brief  	shows an inputbox dialog to enter the name of a Kconfig
     * 			option to search for.
     *
     * \return  uiAction signaling the next method to call or abort if not
     * 			enough space is found on the screen.
     */
	uiAction showSearch();


	/**
     * \brief  	shows an inputbox dialog to enter the value of a string, hex
     * 			or int Kconfig option.
     *
     * \return  uiAction signaling the next method to call or abort if not
     * 			enough space is found on the screen.
     */
	uiAction showInputboxString();



	/**
     * \brief  	inserts a single item to a menu dialog base on the
     * 			characteristics of the Entry that is passed to it.
     *
     * \param 	entry	Entry instance whose information is going to be
     * 			inserted into the menu dialog.
     */
	void makeMenuEntryLabel(Entry &entry);


	/**
     * \brief  	encapsulation of the parameter overhead necessary to display
     * 			a textbox with the information requested.
     *
     * \param 	title		Title of the textbox dialog
     * \param 	text		Text to be displayed in the body of the dialog
     * \param 	centered 	true if the textbox dialog is to start at the
     * 						center of the window, false otherwise.
     */
	void dialogTextbox(std::string title, std::string text, bool centered);


	/**
     * \brief  	encapsulation of the parameter overhead necessary to display
     * 			an inputbox dialog.
     *
     * \param 	title		Title of the inputbox dialog
     * \param 	text		Text to be displayed as instructions to the user
     * \param 	init_value	Current value of the element to be edited
     *
     * \return  int with information of the event that ocurred on execution.
     * 			string with the value of the inputbox.
     */
	std::pair<int, std::string>
	dialogInputbox(std::string title, std::string text, std::string init_value);

public:
    /**
     * \brief 	Constructor of the BasicUI class, only explicit invocation is
     * 			allowed.
   	 * \param navigator		instance of a Navigator class necessary to get
   	 * 						the information from the Kconfig options.
   	 * \param kconfig_		instance of a KConfigHandler class necessary to
   	 * 						perform operations such as save, load, check
   	 * 						changes, etc.
   	 */
	explicit BasicUI(Navigator &navigator, KConfigHandler &kconfig_);


    /**
     * \brief  	initialize the lxdialog parameters, parse and load the Kconfig
     * 			files and start the graphical user interface.
     *
     * \return  true if the gui stopped execution sucessfully,
     * 			false otherwise.
     */
	bool start();
};

#endif /* BASIC_UI_HPP_ */
