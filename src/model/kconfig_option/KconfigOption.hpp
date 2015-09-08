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
 * \file    KconfigOption.hpp
 * \brief   KconfigOption class declaration
 */

#ifndef MODEL_KCONFIGOPTION_HPP_
#define MODEL_KCONFIGOPTION_HPP_

/*============================================================================*/
/*                                INCLUDES                                    */
/*============================================================================*/

#include <string>


/*============================================================================*/
/*		                    CLASS PROTOTYPE 				                  */
/*============================================================================*/

/**
 * \brief Wrapper of the struct symbol found at parser->expr.h L: 80
 * The KconfigOption class is used to wrap 'Kconfig option' elements of the Kconfig
 * language
 */
class KconfigOption
{
private:


	/** \brief 	Pointer to the symbol struct that this KconfigOption instance wraps.
	 *			No modification of the pointer is allowed.
	 */
    struct symbol *const mWrappedSymbol;


    /**
     * \brief  	get the value of size or time that this Kconfig option has
     *
     * \param get_time 	true if the requested value is time.
     * 					false if the requested value is size.
     * \return  float	with the time or size value or 0 if the value doesn't exist
     *		 			or is not applicable
     */
    float getInfoValue(bool get_time) const;

public:
    /**
     * \brief 	Constructor of the KconfigOption class, only explicit invocation is
     * 			allowed.
   	 * \param new_symbol	pointer to symbol struct to be wrapped.
   	 * \warning NULL pointer is not supported as a argument.
   	 */
    explicit KconfigOption(struct symbol *new_symbol);


    /**
     * \brief  	Toggle the value of this Kconfig option.
     * 			Toggling is only possible for tristate and boolean Kconfig options
     *
     * \return  true if the value of the Kconfig option was toggled
     * 			false if this instance doesn't wrap a tristate or boolean
     * 			, or if the value can't be changed
     */
    void toggleTristate();


    /**
     * \brief  	set the value of this Kconfig option.
     * 			This setValue method is valid for all Kconfig options
     *
     * \param  	new_value	string containing the new value to be stored
     * \return  true if the value was successfully changed
     * 			false if the value was not changed
     */
    bool setValue(std::string new_value);


    /**
     * \brief  	set the value of this Kconfig option.
     * 			This setValue method is only valid for Kconfig boolean and tristate
     *
     * \param  	new_value	character containing the new value as follows:
     * 			\ref YES	to enable the option
     * 			\ref NO 	to disable the option
     * 			\ref MOD	to make the option a module
     * \return  true if the value was successfully changed
     * 			false if this is not a boolean or tristate, or if the
     * 			value was not changed
     */
    bool setValue(char new_value);


    /**
     * \brief  	set the value of this Kconfig option.
     * 			This setValue method is only valid for Kconfig Choices
     *
     * \param  	new_value	KconfigOption instance to set the choice value to
     * \return  true if the value was successfully changed
     * 			false if this is not a choice or if the value can't be changed
     */
    bool setValue(KconfigOption& new_value);


    /**
     * \brief  	Check if this Kconfig option value can be overwriten
     *
     * \return  true if this is a hex, string or int Kconfig option
     * 			false otherwise
     */
    bool isRewritable() const;


    /**
     * \brief  	Check if this Kconfig option is of Integer type
     *
     * \return  true if the this is a Kconfig option integer type
     * 			false otherwise
     */
    bool isInteger() const;


    /**
     * \brief  	Check if this KConfig option is of String type
     *
     * \return  true if this is a Kconfig option string type
     * 			false otherwise
     */
    bool isString() const;


    /**
     * \brief  	Check if this KConfig option is of hexadecimal type
     *
     * \return  true if this is a Kconfig option hexadecimal type
     * 			false otherwise
     */
    bool isHexadecimal() const;


    /**
     * \brief  	Check if this KConfig option value is 'yes'
     *
     * \return  true if this Kconfig option is enabled
     * 			false otherwise
     */
    bool isEnable() const;


    /**
     * \brief  	get the prompt of this Kconfig option
     *
     * \return  string	with the prompt of the Kconfig option or the name of
     * 			the Kconfig option
     */
    std::string getPrompt();


    /**
     * \brief  	calculate and wrap the value of this Kconfig option
     *
     * \return  string	with the value of this Kconfig option wrapped according
     * 			to the type of Kconfig option being wrapped.
     */
    std::string wrapValue(bool& visible) const;


    /**
     * \brief  	get the value of this Kconfig option and convert it to a string
     *
     * \return  string 	with the converted value to a string
     */
    std::string valueToString() const;


    /**
     * \brief  	get the time that this Kconfig option adds to the total
     * 			booting time
     *
     * \return  float	with the time value or 0 if the value doesn't exist
     * 			or is not applicable
     */
    float getBootingTime() const;


    /**
     * \brief  	get the size that this Kconfig option adds to the total
     * 			size
     *
     * \return  float	with the size value or 0 if the value doesn't exist
     * 			or is not applicable
     */
    float getSize() const;

// CONSTANTS
    /** \brief  Kconfig option enabled */
    static const char YES = '*';
    /** \brief  Kconfig option disabled */
    static const char NO = ' ';
    /** \brief  Kconfig option as module */
    static const char MOD = 'm';
};

#endif /* #ifndef MODEL_KCONFIGOPTION_HPP_ */
