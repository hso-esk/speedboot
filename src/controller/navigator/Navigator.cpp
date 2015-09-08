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
 * \file    Navigator.cpp
 * \brief   Navigator class implementation
 */

/*============================================================================*/
/*                                INCLUDES                                    */
/*============================================================================*/

#include "controller/navigator/Navigator.hpp"
#include <cstring>	// strlen
#include <stdlib.h> // gentenv()
#include <strings.h> // strncasecmp()
#include "libs/parser/2.6.39/lkc.h" // parser
#include "model/entry/Entry.hpp"

using namespace std;

/*============================================================================*/
/*		                          CLASS METHODS		                          */
/*============================================================================*/

Navigator::Navigator()
    :mRootMenu(rootmenu)
    ,mCurrentParent(&rootmenu)
	,mShowAllOptions(false) // default
	{
	/** rootmenu is a global variable declared in menu.c L:15 */
	}

vector<Entry> Navigator::getChildren(Entry &parent)
{
    struct menu* child = NULL;
    vector<Entry> entries;
    bool get_entry;

    // loop through all the children of the parent menu struct
    for (child = parent.mWrappedMenu->list; child != NULL; child = child->next)
    {
    	// check if the current children should be added to the container
    	get_entry = mShowAllOptions ? menu_has_prompt(child)
    								: menu_is_visible(child);
        if(get_entry)
        	entries.push_back(Entry(child));

        /* check if this entry is used as a condition to display other entries;
         * if so, add them to the container, ignore otherwise
         */
        if(child->sym == NULL || child->list == NULL || !menu_has_prompt(child))
        	continue;
        if( !sym_is_choice(child->sym) && !(child->prompt->type == P_MENU) )
        {
        	Entry child_entry(child);
        	vector<Entry> children(this->getChildren(child_entry));
        	entries.insert(entries.end(), children.begin(), children.end());
        }

    }
    // move current parent pointer to the new parent
    mCurrentParent = parent.mWrappedMenu;
    return entries;
}

vector<Entry> Navigator::getRootChildren()
{
    Entry root_entry(&mRootMenu);
    return this->getChildren(root_entry);
}

vector<Entry> Navigator::getParentSiblings()
{
	/* The parent siblings are all the children parent's parent, i.e the
	 * children of the grandparent of the any current selected entry */
	struct menu* grand_menu = menu_get_parent_menu(mCurrentParent->parent);
    Entry grandparent(grand_menu);
    return this->getChildren(grandparent);
}

vector<Entry> Navigator::refresh()
{
	Entry entry(mCurrentParent);
    return this->getChildren(entry);
}

Entry Navigator::getParent() const
{
	return Entry(mCurrentParent);
}

vector<Entry> Navigator::toggleShowAll()
{
	mShowAllOptions = !mShowAllOptions;
	return this->refresh();
}

string Navigator::searchOption(string option_name) const
{
	// array of all possible symbols that match the search
	struct symbol **sym_arr;
	// growable string structure to store the symbols information
	struct gstr result;
	// stl string instance to deep copy the gstr result info.
	string sym_list;

	// strip the prefix if necessary
	if(strncasecmp(option_name.c_str(), CONFIG_, strlen(CONFIG_)) == 0)
		option_name = option_name.substr(strlen(CONFIG_));

	// search for the requested regular expression
	sym_arr = sym_re_search(option_name.c_str());
	// stored all their information into the growable string struct
	result = get_relations_str(sym_arr, NULL);
	// deep copy the info inside the growable string struct
	sym_list= str_get(&result);

	// free any allocated memory used previouslly allocated during search
	free(sym_arr);
	str_free(&result);

	return sym_list;
}

bool Navigator::isInRootMenu() const
{
	if(mCurrentParent == &mRootMenu)
		return true;
	return false;
}

