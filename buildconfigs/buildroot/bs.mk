# SpeedBoot, a boot time optimization tool
#
# Copyright (c) 2015,
# Hochschule Offenburg, University of Applied Sciences
# Laboratory Embedded Systems and Communications Electronics.
#    
#
# This file is part of SpeedBoot.
# 
# SpeedBoot is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
# 
# SpeedBoot is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with SpeedBoot.  If not, see <http://www.gnu.org/licenses/>.
#
# This work is licensed under the terms of the GNU GPL, version 2. For the full
# license text please refer to the COPYING file in the top-level directory.

SB_CONFIG_IN="$(SBBTPATH)/Config.in"
BR_SB_CONFIG_IN="$(BSPATH)/SB_Config.in"
BR_CONFIG_IN="$(BSPATH)/Config.in"

SB_MAKEFILE="$(BSCONFIGPATH)/Makefile"
BR_SB_MAKEFILE="$(BSPATH)/SB_Makefile"

CONFIG_=
export CONFIG_

all:
	@echo Running Makefile for Buildroot Buildsystem
	@if ! [ -d "$(BSPATH)" ]; then echo "$(BSPATH) does not exist"; exit; fi
	@cp "$(SB_MAKEFILE)" "$(BR_SB_MAKEFILE)"
	@cp "$(BR_CONFIG_IN)" "$(BR_SB_CONFIG_IN)"
	@echo "source $(SB_CONFIG_IN)" >> "$(BR_SB_CONFIG_IN)"
	@make -C "$(BSPATH)" -f "$(BR_SB_MAKEFILE)" sbconfig
	@rm "$(BR_SB_MAKEFILE)"
	@rm "$(BR_SB_CONFIG_IN)"
