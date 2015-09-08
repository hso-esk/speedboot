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
 * \file    Navigator.hpp
 * \brief   Navigator class declaration
 */

#ifndef CONTROLLER_NAVIGATOR_HPP_
#define CONTROLLER_NAVIGATOR_HPP_

/*============================================================================*/
/*                                INCLUDES                                    */
/*============================================================================*/

#include <vector>
#include <string>

class Entry;

/*============================================================================*/
/*		                    CLASS PROTOTYPES 				                  */
/*============================================================================*/

/**
 * \brief 	Class used to navigate through the Kconfig tree structure created
 * 			by the parser. It also allows, searching and toggling visibility
 * 			status.
 */
class Navigator
{
private:
	/**	\brief 	Reference to the root menu of the Kconfig tree structure. */
    struct menu &mRootMenu;

	/**	\brief 	Pointer to the current parent menu in the Kconfig tree.*/
    struct menu *mCurrentParent;

    /**	\brief 	boolean indicating if all entries should be shown or not.*/
    bool mShowAllOptions;
public:

    /**
     * \brief 	Constructor of the Navigator class, only explicit invocation is
     * 			allowed.
   	 */
    explicit Navigator();


    /**
     * \brief 	Get the entries that are located under the requested entry,
     * 			i.e. the children of this entry; and move the mCurrentParent
     * 			to it.
     *
   	 * \param entry		from which the children should be extracted
   	 */
    std::vector<Entry> getChildren(Entry &entry);


    /**
     * \brief 	Get the entries that are located under root menu entry,
     * 			i.e. the children of the main menu entry; and move the
     * 			mCurrentParent to it.
   	 */
    std::vector<Entry> getRootChildren();


    /**
     * \brief 	Get the all the entries that are located one level up in the
     * 			KConfig tree structure, i.e. the parent siblings; and move
     * 			the mCurrentParent to it.
   	 */
    std::vector<Entry> getParentSiblings();


    /**
     * \brief 	Get the all the entries that are located under the current
     * 			parent. This is useful if dependencies status have changed.
   	 */
    std::vector<Entry> refresh();


    /**
     * \brief 	Get the current parent entry to which the Navigator points to.
     * 			No change in the mCurrentParent is done with this operation.
   	 */
    Entry getParent() const;


    /**
     * \brief 	Search for the KconfigOption with name option_name inside the Kconfig
     * 			tree structure.
     * \param 	option_name is the name or regular expression to search for in the Kconfig
     * 			tree.
     * \return 	string with all the possible KconfigOption that match either totally
     * 		   	or partially the requested option_name.
   	 */
    std::string searchOption(std::string option_name) const;


    /**
     * \brief 	Show or hide entries based on their visibility status.
     *
     * \return 	vector with all the entries that fulfill the new visibility
     * 		   	condition.
   	 */
    std::vector<Entry> toggleShowAll();


    /**
     * \brief 	Check if the mCurrentParent is currently pointing to the root
     * 			of the KConfig tree.
     * \return 	true if the mCurrentParent points to the root menu.
     * 		   	false otherwise.
   	 */
    bool isInRootMenu() const;
};

#endif /* CONTROLLER_NAVIGATOR_HPP_ */
