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


#include <iostream>
#include <libintl.h>

#include "model/entry/Entry.hpp"
#include "controller/navigator/Navigator.hpp"
#include "controller/kconfig_handler/KConfigHandler.hpp"
#include "frontends/ncurses/BasicUI.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	if( argc < 2 )
	{
		cout << "*** Missing Configuration file parameter ***" << endl;
		return -1;
	}

	const static char* PACKAGE = "linux";
	const static char* LOCALEDIR = "/usr/share/locale";

	setlocale(LC_ALL, "");
	// Fix decimal separator as "." character rather than ","
	setlocale(LC_NUMERIC, "C");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

    string KCONFIG_IN(argv[1]);
    KConfigHandler kconfig(KCONFIG_IN);
    Navigator navigator;
	BasicUI gui(navigator, kconfig);
	if( !gui.start())
		return 1;
	else
		cout << endl << endl << "*** End of the configuration." << endl
			 << "*** Execute 'make' to start the build or try 'make help'."
			 << endl << endl;
	return 0;
}
