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

##***************************************************************************##
## 									MODEL-ENTRY 
##***************************************************************************##

ENTRY_CPPSRC = $(wildcard $(MODEL_PATH)/entry/*.cpp)
ENTRY_INCLUDE = -I"$(MODEL_PATH)/entry"
ENTRY_VPATH = $(MODEL_PATH)/entry:


##***************************************************************************##
## 									MODEL-SYMBOL 
##***************************************************************************##

KCONFIG_OPTION_CPPSRC = $(wildcard $(MODEL_PATH)/kconfig_option/*.cpp)
KCONFIG_OPTION_INCLUDE = -I"$(MODEL_PATH)/kconfig_option"
KCONFIG_OPTION_VPATH = $(MODEL_PATH)/kconfig_option:
		
				
##***************************************************************************##
## 							GENERAL MACRO FOR EXPORT 
##***************************************************************************##
INCLUDES += $(ENTRY_INCLUDE) $(KCONFIG_OPTION_INCLUDE)
CPPSRC += $(ENTRY_CPPSRC) $(KCONFIG_OPTION_CPPSRC)
VPATH+=	$(ENTRY_VPATH) $(KCONFIG_OPTION_VPATH)
