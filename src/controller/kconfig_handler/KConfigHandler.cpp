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
 * \file    KConfigHandler.cpp
 * \brief   KConfigHandler class implementation
 */

/*============================================================================*/
/*                                INCLUDES                                    */
/*============================================================================*/

#include "controller/kconfig_handler/KConfigHandler.hpp"
#include <string>
#include <stdlib.h> // gentenv()
#include <unistd.h> //chdir() getcwd()
#include "libs/parser/2.6.39/lkc.h"

using namespace std;

/*============================================================================*/
/*		                          CLASS METHODS		                          */
/*============================================================================*/


KConfigHandler::KConfigHandler(string &filename)
    :mRootMenu(rootmenu)
	,mKconfigFilepath(filename)
{
	/** rootmenu is a global variable declared in menu.c L:15 */
	char* cwd = getcwd(NULL, 0);
	if(cwd != NULL)
		mUserConfig = cwd + string("/") + conf_get_configname();
	else
		mUserConfig = conf_get_configname();
}

string KConfigHandler::getConfigPath() const
{
	return mUserConfig;
}

void KConfigHandler::parse() const
{
    //Call to Kconfig parser. File: *.conf.y L:505
    conf_parse(mKconfigFilepath.c_str());
}

bool KConfigHandler::load(string config_filepath)
{
	int result = conf_read(config_filepath.c_str());
	/* NOTE: mconf.c uses if(!result) apparently
	 *  !Error != OK
	 *  I don't know the reason of this behavior
	 */
	switch(result)
	{
	case OK_:
		if(mUserConfig != config_filepath)
		{
			// update .config filepath
			mUserConfig = config_filepath;
			// configuration has changed
			sym_set_change_count(1);
		}
		sym_set_change_count(0);
		return true;
	case ERROR:	// fall through
	default: // Error
		return false;
	}
}

bool KConfigHandler::load()
{
	return load(mUserConfig);
}

bool KConfigHandler::write(string filepath)
{
	int result = conf_write(filepath.c_str());
	/* NOTE: mconf.c uses if(!result) apparently
	 *  !Error != OK
	 *  I don't know the reason of this behavior
	 */
	switch(result)
	{
	case OK_:
		// update .config filepath
		mUserConfig = filepath;
		return true;
	case ERROR:
	default: // ERROR
		return false;
	}
}

bool KConfigHandler::write()
{
	return write(mUserConfig);
}

bool KConfigHandler::hasChanged() const
{
	return conf_get_changed();
}
