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

# Make sure to copy this file to buildroot directory
include Makefile
SB_CONFIG_IN=SB_Config.in

.PHONY: sbconfig $(SBBTEXE)
sbconfig: $(SBBTEXE)
	make -C $(SBBTSRCPATH)
	@$(COMMON_CONFIG_ENV) $< $(SB_CONFIG_IN)

