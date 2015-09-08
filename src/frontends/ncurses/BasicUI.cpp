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
 * \file    BasicUI.cpp
 * \brief   BasicUI class implementation
 */

/*============================================================================*/
/*                                INCLUDES                                    */
/*============================================================================*/

#include "frontends/ncurses/BasicUI.hpp"

#include <curses.h> //getmaxx
#include <iostream>	// std::cout
#include <sstream> // std::ostringstream
#include <iomanip> // std::setw
#include <algorithm> // std::find

#include "model/kconfig_option/KconfigOption.hpp"
#include "model/entry/Entry.hpp"
#include "controller/navigator/Navigator.hpp"
#include "controller/kconfig_handler/KConfigHandler.hpp"

#include "frontends/ncurses/buttons.hpp"
#include "frontends/ncurses/commands.hpp"
#include "frontends/ncurses/tags.hpp"
#include "frontends/ncurses/instructions.hpp"
#include "frontends/ncurses/help.hpp"
#include "frontends/ncurses/util.hpp"

#include "libs/lxdialog/dialog.h" // lxdialog

using namespace std;

/*============================================================================*/
/*		                          CLASS METHODS		                          */
/*============================================================================*/

const char* BasicUI::UI_TITLE = "SpeedBoot v";
const char* BasicUI::VERSION = "1.0";

BasicUI::BasicUI(Navigator &navigator_, KConfigHandler &kconfig_)
			:mNavigator(navigator_)
			,mKconfig(kconfig_)
			,mCurrentEntry(NULL)
			,mCurrentContext(context::MENU)
			,mTerminalOutput("")
			{}


/*=============================================================================
 * start()
 *============================================================================*/
bool BasicUI::start()
{
	// parse and load the Kconfig files
	mKconfig.parse();
	mKconfig.load();
	// initilize the entries of the menu dialog
	mEntries = mNavigator.getRootChildren();

	// always start with a menu dialog
	uiAction next_action = DO_SHOW_MENU;
	// initialize the lxdialog parameters
	if(init_dialog(NULL) == -ERRDISPLAYTOOSMALL)
		next_action = DO_ABORT; // error during initialization

	while(true)
	{
		switch (next_action)
		{
		case DO_SHOW_MENU:
			next_action = showMenu();
			break;
		case DO_SHOW_CHOICE:
			next_action = showChoice();
			break;
		case DO_SHOW_INPUTBOX:
			next_action = showInputboxString();
			break;
		case DO_SHOW_HELP:
			next_action = showHelp();
			break;
		case DO_SHOW_LOAD:
			next_action = showLoad();
			break;
		case DO_SHOW_SAVE:
			next_action = showSave();
			break;
		case DO_SHOW_SEARCH:
			next_action = showSearch();
			break;
		case DO_SHOW_EXIT:
			next_action = showExit();
			break;
		case DO_EXIT:
			end_dialog(saved_x, saved_y);
			cout << mTerminalOutput;
			return true;
		case DO_ABORT:	// error during execution, probably resized window
			end_dialog(saved_x, saved_y);
			cout << endl << endl
				 << "Your display is too small to run Menuconfig" << endl
				 << "It must be at least 19 lines by 80 columns."
				 << endl << endl;
			return false;
		default: // Error: unknown action
			return false;
		}
	}
	return true;
} /*EOF start()*/


/*=============================================================================
 * showMenu()
 *============================================================================*/
BasicUI::uiAction BasicUI::showMenu()
{
	mCurrentContext = context::MENU;

	// set the scroll of the window to the top
	int s_scroll = 0;
	string uiTitle(BasicUI::UI_TITLE);
	uiTitle += VERSION;

	// Change the title to the parent Entry
	if(!mNavigator.isInRootMenu())
		uiTitle = mNavigator.getParent().getPrompt();

	// delete any previously stored items
	item_reset();
	// lxdialog doesn't allow a menu to be empty
	// insert 5 columns to hold the time, size and prompt and two more to
	// separate each column from the others
	ostringstream first_row;
	first_row 	<< setw(width::COLUMN) << " Time [s] " << setw(width::SEPARATOR) << "*****"
				<< setw(width::COLUMN) << " Size [kB] "<< setw(width::SEPARATOR) << "*****"
				<< " Prompt " << setw(width::SEPARATOR) << "*****";
	item_make(first_row.str().c_str());
	item_set_tag(tag::LABEL);

	// populate the dialog menu items
	for (vector<Entry>::iterator entry = mEntries.begin(); entry != mEntries.end(); ++entry)
		makeMenuEntryLabel(*entry);

	/* Creates a dash line to separate the entries from the total */
	ostringstream dash_line;
	dash_line << setw(width::COLUMN) << "-----------" << setw(width::SEPARATOR) << " "
			  << setw(width::COLUMN) << "-----------" << setw(width::SEPARATOR) << " "
			  << "-----------" << setw(width::SEPARATOR) << " ";
	item_make(dash_line.str().c_str());
	item_set_tag(tag::LABEL);

	// calculate and output the total of the current parent entry
	Entry parent(mNavigator.getParent());
	ostringstream last_row;
	last_row << setw(width::COLUMN) << parent.printBootingTime()
			 << setw(width::SEPARATOR) << " "
			 << setw(width::COLUMN) << parent.printSize()
			 << setw(width::SEPARATOR) << " "
			 << " Total ";
	item_make(last_row.str().c_str());
	item_set_tag(tag::LABEL);
	//TODO put a note at the end of the menu that says "hidden options may be selected"

	// sets an upper left title with info of the current configuration file
	// being used
	set_dialog_backtitle(mKconfig.getConfigPath().c_str());
	// clear the window of any previously drawn elements
	dialog_clear();
	// start the menu dialog and wait for either a user event or an error catch
	int event = dialog_menu(uiTitle.c_str(), instructions::GUI, mCurrentEntry,  &s_scroll);

	// get the last selected Entry before the event happened
	mCurrentEntry = static_cast<Entry*>(item_data());
	switch(event)
	{
	case buttonMenu::SELECT:
		if(item_is_tag(tag::MENU) || item_is_tag(tag::MENUCONFIG))
		{
			mEntries = mNavigator.getChildren(*mCurrentEntry);
			mCurrentEntry = NULL; 	// reset selected entry
			return DO_SHOW_MENU;
		}
		if (item_is_tag(tag::CHOICE))
		{
			mEntries = mNavigator.getChildren(*mCurrentEntry);
			mCurrentEntry = NULL;	// reset selected entry
			return DO_SHOW_CHOICE;
		}
		if (item_is_tag(tag::OPTION) && mCurrentEntry->getOption().isRewritable())
			return DO_SHOW_INPUTBOX;	// Don't reset selected entry
		return DO_SHOW_MENU;
	case KEY_ESC: // fall through
	case buttonMenu::EXIT:
	{
		if(mNavigator.isInRootMenu())
		{
			if(mKconfig.hasChanged())
				return DO_SHOW_EXIT;
			return DO_EXIT;
		}
		// return to the parent entry used to come here
		Entry parent(mNavigator.getParent());
		mEntries = mNavigator.getParentSiblings();
		vector<Entry>::iterator result = find(mEntries.begin(), mEntries.end(), parent);
		mCurrentEntry = (result != mEntries.end()) ? &*result
												   : NULL;
		return DO_SHOW_MENU;
	}
	case buttonMenu::LOAD:
		return DO_SHOW_LOAD;
	case buttonMenu::SAVE:
		return DO_SHOW_SAVE;
	case buttonMenu::HELP:
		return DO_SHOW_HELP;
	case command::MOD:
		if(item_is_tag(tag::OPTION) || item_is_tag(tag::MENUCONFIG))
		{
			mCurrentEntry->getOption().setValue(KconfigOption::MOD);
			// check for dependency changes
			mEntries = mNavigator.refresh();
		}
		return DO_SHOW_MENU;
	case command::NO:
		if(item_is_tag(tag::OPTION) || item_is_tag(tag::MENUCONFIG))
		{
			mCurrentEntry->getOption().setValue(KconfigOption::NO);
			// check for dependency changes
			mEntries = mNavigator.refresh();
		}
		return DO_SHOW_MENU;
	case command::YES:
		if(item_is_tag(tag::OPTION) || item_is_tag(tag::MENUCONFIG))
		{
			mCurrentEntry->getOption().setValue(KconfigOption::YES);
			// check for dependency changes
			mEntries = mNavigator.refresh();
		}
		return DO_SHOW_MENU;
	case command::SEARCH:
		return DO_SHOW_SEARCH;
	case command::SHOW_ALL:
		// show or hide invisible entries
		mEntries = mNavigator.toggleShowAll();
		return DO_SHOW_MENU;
	case command::TOGGLE:
		if(item_is_tag(tag::OPTION) || item_is_tag(tag::MENUCONFIG))
		{
			mCurrentEntry->getOption().toggleTristate();
			// check for dependency changes
			mEntries = mNavigator.refresh();
		}
		return DO_SHOW_MENU;
	case -ERRDISPLAYTOOSMALL:
		return DO_ABORT;
	}
	return DO_EXIT; // Error unknown event
}	/*EOF showMenu()*/


/*=============================================================================
 * showChoice()
 *============================================================================*/
BasicUI::uiAction BasicUI::showChoice()
{
	mCurrentContext = context::CHOICE;

	// checklist dialog parameters initialization
	int height = 15;
	int width = 70;
	int list_height = 6;

	// set checklist dialog text
	Entry parent(mNavigator.getParent());
	string choice_value(parent.getOption().valueToString());
	string title(parent.getPrompt());
	string prompt(instructions::CHOICE);

	// delete any previously stored items
	item_reset();
	// insert new items
	vector<Entry>::iterator entry;
	for(entry = mEntries.begin(); entry != mEntries.end(); ++entry)
	{
		item_make(entry->getPrompt().c_str());
		item_set_data( &(*entry) );
		// find current choice value and set a special tag for it
		if(entry->getPrompt() == choice_value)
			item_set_tag(tag::CHOICE_VALUE);
	}

	// clear the window of any previously drawn elements
	dialog_clear();
	// start the checklist dialog and wait for either a user event or an error
	int event = dialog_checklist(title.c_str(), prompt.c_str(), height, width, list_height);

	// get the last selected entry before the event
	mCurrentEntry = static_cast<Entry*>(item_data());
	switch(event)
	{
	case buttonChoice::SELECT:
		if(mCurrentEntry->isOption())
			mCurrentEntry->getOption().setValue(KconfigOption::YES);
	case KEY_ESC: // fallthrough
	{
		// return to the parent entry used to come here
		Entry parent(mNavigator.getParent());
		mEntries = mNavigator.getParentSiblings();
		vector<Entry>::iterator result = find(mEntries.begin(), mEntries.end(), parent);
		mCurrentEntry = (result != mEntries.end()) ? &*result
												   : NULL;
		return DO_SHOW_MENU;
	}
	case buttonChoice::HELP:
		return DO_SHOW_HELP;
	case -ERRDISPLAYTOOSMALL:
		return DO_ABORT;
	}
	return DO_EXIT;		// error: unknown event
}	/*EOF showChoice()*/


/*=============================================================================
 * showExit()
 *============================================================================*/
BasicUI::uiAction BasicUI::showExit()
{
	if(!mKconfig.hasChanged())
		return DO_EXIT;

	// initialize yes_no dialog parameters
	const char* title = "Save before exiting?";
	int height = 6;
	int width = 60;

	// clear the window of any previously drawn elements
	dialog_clear();
	// start the yes_no dialog and wait for either a user event or an error
	int event = dialog_yesno(title, instructions::EXIT, height, width);
	switch(event)
	{
	case buttonYesNo::YES:
		if( !mKconfig.write())
		{
			// writing error
			mTerminalOutput = "\n\nError while writing of the configuration.";
			mTerminalOutput += "\nYour configuration changes were NOT saved.\n";
			return DO_EXIT;
		}
		return DO_EXIT;
	case buttonYesNo::NO:
		mTerminalOutput = "\n\nYour configuration changes were NOT saved.\n";
		return DO_EXIT;
	case KEY_ESC:
		return DO_SHOW_MENU;
	case -ERRDISPLAYTOOSMALL:
		return DO_ABORT;
	}
	return DO_EXIT; // Error: unknown event
}	/*EOF showExit()*/


/*=============================================================================
 * showHelp()
 *============================================================================*/
BasicUI::uiAction BasicUI::showHelp()
{
	// initialize textbox dialog parameters
	int max_width = getmaxx(stdscr) - 10;
	int row = 0;
	int column = 0;

	// Choose text to display base on the current context
	string title;
	string help_text;
	switch(mCurrentContext)
	{
	case context::INPUTBOX:
	case context::CHOICE:
	case context::MENU:
		if(item_is_tag(tag::COMMENT) || item_is_tag(tag::LABEL) ||
		  (item_is_tag(tag::MENU) && mNavigator.isInRootMenu()) )
		{
			title = "Overview";
			help_text = help::MENU;
		}
		else	// get the info provided in the Kconfig option
		{
			title = mCurrentEntry->getPrompt();
			help_text = mCurrentEntry->getHelpText(max_width);
		}
		break;
	case context::LOAD:
		title = "Help Load Configuration";
		help_text = help::LOAD_CONFIG;
		break;
	case context::SAVE:
		title = "Help Save Configuration";
		help_text = help::SAVE_CONFIG;
		break;
	case context::SEARCH:
		title = "Help Search Configuration";
		help_text = help::SEARCH;
		break;
	default: //Error
		title = "ERROR HELP TEXT";
		help_text = "ERROR: HELP NOT FOUND";
		break;
	}

	// start the textbox dialog and ignore any event
	dialogTextbox(title, help_text, false);

	// Decide where to return to
	switch(mCurrentContext)
	{
	case context::MENU:
		return DO_SHOW_MENU;
	case context::CHOICE:
		return DO_SHOW_CHOICE;
	case context::INPUTBOX:
		return DO_SHOW_INPUTBOX;
	case context::LOAD:
		return DO_SHOW_LOAD;
	case context::SAVE:
		return DO_SHOW_SAVE;
	case context::SEARCH:
		return DO_SHOW_SEARCH;
	}
	return DO_EXIT; // Unknown context
}	/*EOF showHelp()*/


/*=============================================================================
 * showLoad()
 *============================================================================*/
BasicUI::uiAction BasicUI::showLoad()
{
	mCurrentContext = context::LOAD;

	// initialize text to display in the inputbox
	string title("Load Configuration");
	string filename(mKconfig.getConfigPath());

	// start the inputbox dialog and retrieve both the event and the input text
	pair<int, string> result;
	result = dialogInputbox(title, instructions::LOAD_CONFIG, filename);

	switch (result.first)
	{
	case buttonString::OK_:
	{
		if(result.second.empty())  // Ignore input
			return DO_SHOW_MENU;
		else if(mKconfig.load(result.second))
			return DO_SHOW_MENU; // configuration loaded
		// error while loading configuration
		title = "ERROR";
		const char* load_error = "File does not exists! ";
		// display textbox dialog to show the error
		dialogTextbox(title, load_error, true);
		return DO_SHOW_MENU;
	}
	case buttonString::HELP:
		return DO_SHOW_HELP;
	case KEY_ESC:
		return DO_SHOW_MENU;
	}
	return DO_EXIT;
}	/*EOF showLoad()*/


/*=============================================================================
 * showSave()
 *============================================================================*/
BasicUI::uiAction BasicUI::showSave()
{
	mCurrentContext = context::SAVE;

	// initialize text to display in the inputbox
	string title("Save Configuration");
	string filename(mKconfig.getConfigPath());

	// start the inputbox dialog and retrieve both the event and the input text
	pair<int, string> result;
	result = dialogInputbox(title, instructions::SAVE_CONFIG, filename);

	switch (result.first)
	{
	case buttonString::OK_:
	{
		if(result.second.empty())	// Ignore input
			return DO_SHOW_MENU;
		else if(mKconfig.write(result.second))
			return DO_SHOW_MENU; 	// configuration saved
		// error while writing configuration
		title = "ERROR";
		const char* load_error = "Can't create file! Probably a nonexistent directory";
		// display textbox dialog to show the error
		dialogTextbox(title, load_error, true);
			return DO_SHOW_MENU;
	}
	case buttonString::HELP:
		return DO_SHOW_HELP;
	case KEY_ESC:
		return DO_SHOW_MENU;
	}
	return DO_EXIT; // ERROR
}	/*EOF showSave()*/


/*=============================================================================
 * showSearch()
 *============================================================================*/
BasicUI::uiAction BasicUI::showSearch()
{
	mCurrentContext = context::SEARCH;

	// Initialize text to display
	string title("Search");
	string init_value("");

	// start the inputbox dialog and retrieve both the event and the input text
	pair<int, string> result;
	result = dialogInputbox(title, instructions::SEARCH,init_value);
	switch (result.first)
	{
	case buttonString::OK_:
	{
		// search for the requested string and stored all related results
		// in another string
		string search_result(mNavigator.searchOption(result.second));
		title = "Search Results";
		// display a single textbox with the results
		dialogTextbox(title, search_result, false);
			return DO_SHOW_MENU;
	}
	case buttonString::HELP:
		return DO_SHOW_HELP;
	case KEY_ESC:
		return DO_SHOW_MENU;
	case -ERRDISPLAYTOOSMALL:
		return DO_ABORT;
	}
	return DO_EXIT; // ERROR
}	/*EOF showSave()*/


/*=============================================================================
 * showInputboxString()
 *============================================================================*/
BasicUI::uiAction BasicUI::showInputboxString()
{
	mCurrentContext = context::INPUTBOX;

	// Initialize text to display
	string title(mCurrentEntry->getPrompt());
	string instructions(""); // default

	// get option current value
	KconfigOption option(mCurrentEntry->getOption());
	string old_value(option.valueToString());

	// choose instructions to use
	if(option.isInteger())
		instructions = instructions::INPUTBOX_INT;
	else if(option.isHexadecimal())
		instructions = instructions::INPUTBOX_HEX;
	else if(option.isString())
		instructions = instructions::INPUTBOX_STRING;

	// start the inputbox dialog and retrieve both the event and the input text
	pair<int, string> result;
	result = dialogInputbox( title, instructions, old_value);

	switch (result.first)
	{
	case buttonString::OK_:
	{
		if(option.setValue(result.second))
			return DO_SHOW_MENU; // ok, value changed
		// Error, new value is not valid
		title = "INPUT ERROR";
		const char* input_error("You have made an invalid entry");
		// display textbox dialog to show the error
		dialogTextbox(title, input_error, true);
		return DO_SHOW_INPUTBOX;
	}
	case buttonString::HELP:
		return DO_SHOW_HELP;
	case KEY_ESC:
		return DO_SHOW_MENU;
	case -ERRDISPLAYTOOSMALL:
		return DO_ABORT;
	}
	return DO_EXIT; // ERROR
}	/*EOF showInputboxString()*/


/*=============================================================================
 * makeMenuEntryLabel()
 *============================================================================*/
void BasicUI::makeMenuEntryLabel(Entry &entry)
{
	ostringstream row;
	char tag = tag::UNKNOWN; // default
	bool entry_is_visible = entry.isVisible();

	// creates the two columns with time and size
	row << right << setw(width::COLUMN) << entry.printBootingTime()
		<< setw(width::SEPARATOR) << ""
		<< right << setw(width::COLUMN) << entry.printSize()
		<< setw(width::SEPARATOR) << "";

	// print and tag the last column base on the entry type
	if(entry.isMenu())
	{
	    row << icon::SPACE << entry.getPrompt() << icon::ARROW;
		tag = tag::MENU;
	}
	else if(entry.isMenuconfig())
	{
		KconfigOption option(entry.getOption());
		row << option.wrapValue(entry_is_visible) << entry.getPrompt()
			<< icon::ARROW;
		tag = tag::MENUCONFIG;
	}
	else if (entry.isComment())
	{
		// Comments shouldn't display a value for time or size
		row.str(""); // reset
		row << setw(width::COLUMN + width::SEPARATOR) << ""
		   	<< setw(width::COLUMN + width::SEPARATOR) << ""
		   	<< icon::ASTERISKS + entry.getPrompt() + icon::ASTERISKS;
		tag = tag::COMMENT;
	}
	else if (entry.isChoice())
	{
		KconfigOption option(entry.getOption());
		row << icon::SPACE + entry.getPrompt()
			<< option.wrapValue(entry_is_visible);
		if(entry_is_visible)
			row << icon::ARROW;
		tag = tag::CHOICE;
	}
	else if (entry.isOption())
	{
		KconfigOption option(entry.getOption());
		row << option.wrapValue(entry_is_visible) << entry.getPrompt();
		tag = tag::OPTION;
	}
	else
		row << " UNKNOWN ITEM";

	item_make(row.str().c_str());
	item_set_tag(tag);
	item_set_data(&entry);
}	/*EOF MakeMenuEntryLabel()*/


/*=============================================================================
 * dialogTextbox()
 *============================================================================*/
void BasicUI::dialogTextbox(string title, string text, bool centered)
{
	// start text box at the top left of the window
	int row = 0;
	int column = 0;

	if(centered)
	{
		// start text box at the center of the window
		row = 5;
		column = 38;
	}
	// keys: required for lxdialog
	int keys[] = {0};

	// clear all previous windows graphics
	dialog_clear();
	dialog_textbox(title.c_str(), const_cast<char*>(text.c_str()),
					row, column, keys, NULL, NULL, NULL, NULL);
}	/*EOF dialogTextbox()*/


/*=============================================================================
 * dialogInputBox()
 *============================================================================*/
pair<int, string> BasicUI::dialogInputbox(string title, string text, string init_value)
{
	// generic values for an inputbox
	int height = 11;
	int width = 55;

	// clear all previous windows graphics
	dialog_clear();
	// start the inputbox dialog and retrieve both the event
	int event = dialog_inputbox(title.c_str(), text.c_str(), height, width, init_value.c_str());
	// dialog_input_result is a global variable that holds the input text
	return make_pair(event, dialog_input_result);
	 	 	 	 	 	 	// global variable
}	/*EOF dialogInputBox()*/
