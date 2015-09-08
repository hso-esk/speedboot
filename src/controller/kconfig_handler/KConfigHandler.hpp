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
 * \file    KConfigHandler.hpp
 * \brief   KConfigHandler class declaration
 */


#ifndef CONTROLLER_KCONFIG_HANDLER_HPP_
#define CONTROLLER_KCONFIG_HANDLER_HPP_

/*============================================================================*/
/*                                INCLUDES                                    */
/*============================================================================*/

#include <string>

/*============================================================================*/
/*		                    CLASS PROTOTYPES 				                  */
/*============================================================================*/

/**
 * \brief	Wrapper of the functions necessary to manage write, read, parse and
 *			status checks of the configurations files used to create images or
 *			embedded systems.
 */
class KConfigHandler
{
private:
	/**	\brief 	Reference to the root menu of the KConfig tree. */
	struct menu &mRootMenu;

	/**	\brief 	Path to the KConfig configuration file where to start parsing */
	const std::string mKconfigFilepath;

	/**	\brief 	Path to the currently used configuration file,
	 * 			i.e. the .config file*/
	std::string mUserConfig;

public:

    /**
     * \brief 	Constructor of the KConfigHandler class, only explicit
     * 			invocation is allowed.
     *
   	 * \param filename	name of the KConfig configuration file to parse
   	 */
	explicit KConfigHandler(std::string &filename);


    /**
     * \brief 	get the path to the current configuration file (.config)
     *
   	 * \return string containing the path to the current .config file
   	 */
	std::string getConfigPath() const;


	/**
     * \brief 	parse the KConfig configuration file passed at the constructor.
     * 			The program terminates if any KConfig entry is incorrectly
     * 			written.
   	 */
	void parse() const;


    /**
     * \brief 	write the current configuration to the specified
     * 			config_filepath.
     *
   	 * \param 	config_filepath	is the complete path where to save the
   	 * 			configuration
   	 * \return	true if the configuration was successfully written.
   	 * 			false otherwise.
   	 */
	bool write(std::string config_filepath);


    /**
     * \brief 	write the current configuration to the last specified
     * 			config filepath.
     *
   	 * \return	true if the configuration was successfully written.
   	 * 			false otherwise.
   	 */
	bool write();


	/**
     * \brief 	load the configuration from the specified config_filepath
     *
     * \param	config_filepath from which to load the configuration
   	 * \return	true if the configuration was successfully loaded.
   	 * 			false otherwise.
   	 */
	bool load(std::string config_filepath);


    /**
     * \brief 	load the configuration from the last specified config
     * 			filepath.
     *
   	 * \return	true if the configuration was successfully read.
   	 * 			false otherwise.
   	 */
	bool load();


    /**
     * \brief 	Check if the configuration has changed since the last call to
     * 			load().
     *
   	 * \return	true if there are unsaved changes.
   	 * 			false otherwise.
   	 */
	bool hasChanged() const;

private:
	/**	\brief 	Return value of the conf_read() and conf_write() signaling
	 * 			no problems. */
	static const int OK_ = 0;

	/**	\brief 	Return value of the conf_read() and conf_write() signaling
	 * 			error on the operation. */
	static const int ERROR = 1;
};
#endif /* CONTROLLER_KCONFIG_HANDLER_HPP_ */
