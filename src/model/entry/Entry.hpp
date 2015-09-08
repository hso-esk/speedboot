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
 * \file    Entry.hpp
 * \brief   Entry class declaration
 */


#ifndef MODEL_ENTRY_HPP_
#define MODEL_ENTRY_HPP_

/*============================================================================*/
/*                                INCLUDES                                    */
/*============================================================================*/

#include <string>
class KconfigOption;


/*============================================================================*/
/*		                    CLASS PROTOTYPES 				                  */
/*============================================================================*/

/**
 * \brief Wrapper of the struct menu found at parser->expr.h L: 168
 * The Entry class is used to wrap organizational elements of the Kconfig
 * language i.e. menu, menuconfig, choice and comments.
 * If an Entry wrapps a config option (not organizational element),
 * the underlying logic is delegated to the KconfigOption class.
 */
class Entry
{
/**
 * \brief Navigator friend declaration
 * \relates Navigator
 */
friend class Navigator;

private:
	/**	\brief 	Pointer to the menu struct that this Entry instance wraps. */
    struct menu* mWrappedMenu;


    /**
     * \brief  	calculates the value of the information (time or size) that
     * 			the underlying organizational element adds to the total
     * 			image size. If this instance wraps a KconfigOption, then the
     * 			logic is deferred to it.
     *
     * \param time	true if the requested value is time.
     * 				false if the requested value is size.
     *
     * \return  total value that this Entry adds to.
     * 			0 represents a non-existent or non-applicable property
     * 			definition
     */
    float calculateInfoValue(bool time) const;


    /**
     * \brief  	prints a number prefixed with a precision character specified
     * 			by the info type of the underlying property.
     *
     * \param time	true if the requested value is time.
     * 				false if the requested value is size.
     * \return  string containing the number prefixed with the precision
     * 			character of the measurement.
     */
    std::string printInfo(bool time) const;
public:
    /**
     * \brief 	Constructor of the Entry class, only explicit invocation is
     * 			allowed.
     *
   	 * \param new_menu		pointer to menu struct to be wrapped.
   	 * \warning NULL pointer is not supported as a argument.
   	 */
    explicit Entry(struct menu *new_menu);


    /**
     * \brief  	equality comparison operator overloading.
     * 			Overloading necessary to allow comparison of objects inside a container
     *
     * \param  	other	Entry reference to compare this instance with.
     * \return  true if both instances are equal.
     * 			false otherwise.
     */
    bool operator==(const Entry& other) const;


    /**
     * \brief  	Checks the visibility dependencies of the Kconfig option that it wraps.
     *
     * \return  true if the Kconfig option is currently visible.
     * 			false otherwise.
     */
    bool isVisible() const;


    /**
     * \brief  	get the prompt of the Kconfig option that it represents
     *
     * \return  string with the prompt of the menu struct.
     */
    std::string getPrompt() const;


    /**
     * \brief  	get the help text associated with the Kconfig option that this
     *  		menu represents.
     *
     * \param  	max_width	width of the window used to display the text.
     * \return  string containing the help text of the Kconfig option in case
     * 			that it was defined, or "No help available" in case that it
     * 			was not defined.
     */
    std::string getHelpText(int max_width) const;


    /**
     * \brief  	calculate the time that the underlying organizational
     * 			element adds to the booting time. If this instance wraps
     * 			a KconfigOption, then the logic is deferred to it.
     *
     * \return  total value that this Entry adds to.
     * 			0 represents a non-existent or non-applicable time
     * 			definition
     */
    float calculateBootingTime() const;


    /**
     * \brief  	calculate the size that the underlying organizational
     * 			element adds to the total image size. If this instance wraps
     * 			a KconfigOption, then the logic is deferred to it.
     *
     * \return  total value that this Entry adds to.
     * 			0 represents a non-existent or non-applicable time
     * 			definition
     */
    float calculateSize() const;


    /**
     * \brief  	prints the booting time of the underlying organizational element
     * 			according to the precision type that it has.
     *
     * \return  string containing the calculated booting time of this Entry
     * 			prefixed with the precision character of the measurement.
     */
    std::string printBootingTime() const;


    /**
     * \brief  	prints the size of the underlying organizational element
     * 			according to the precision type that it has.
     *
     * \return  string containing the calculated size of this Entry prefixed
     * 			with the precision character of the measurement.
     */
    std::string printSize() const;


    /**
     * \brief  	Checks if the underlying menu structure represents a
     * 			Kconfig menu.
     *
     * \return  true if the underlying menu structure is a Kconfig menu.
     * 			false otherwise.
     */
    bool isMenu() const;


    /**
     * \brief  	Checks if the underlying menu structure represents a
     * 			Kconfig menuconfig.
     *
     * \return  true if the underlying menu structure is a Kconfig menuconfig.
     * 			false otherwise.
     */
    bool isMenuconfig() const;


    /**
     * \brief  	Checks if the underlying menu structure represents a
     * 			Kconfig comment.
     *
     * \return  true if the underlying menu structure is a Kconfig comment.
     * 			false otherwise.
     */
    bool isComment() const;


    /**
     * \brief  	Checks if the underlying menu structure represents a
     * 			Kconfig choice.
     *
     * \return  true if the underlying menu structure is a Kconfig choice.
     * 			false otherwise.
     */
    bool isChoice() const;


    /**
     * \brief  	Checks if the underlying menu structure represents a
     * 			Kconfig option.
     *
     * \return  true if the underlying menu structure is a Kconfig option.
     * 			false otherwise.
     */
    bool isOption() const;


    /**
     * \brief  	gets the config option that this Entry contains.
     *
     * \return  KconfigOption	An instance of the KconfigOption class representing the
     * 			Kconfig option.
     */
    KconfigOption getOption() const;
};

#endif /* #ifndef MODEL_ENTRY_HPP_ */
