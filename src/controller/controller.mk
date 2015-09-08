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
## 							NAVIGATOR 
##***************************************************************************##

NAVIGATOR_CPPSRC = $(wildcard $(CONTROLLER_PATH)/navigator/*.cpp)
NAVIGATOR_INCLUDE = -I"$(CONTROLLER_PATH)/navigator"
NAVIGATOR_VPATH = $(CONTROLLER_PATH)/navigator:
						
##***************************************************************************##
## 							KCONFIGPARSER HANDLER 
##***************************************************************************##						
						
KCONFIGPARSERHANDLER_CPPSRC = $(wildcard $(CONTROLLER_PATH)/kconfig_handler/*.cpp)
KCONFIGPARSERHANDLER_INCLUDE = -I"$(CONTROLLER_PATH)/kconfig_handler"
KCONFIGPARSERHANDLER_VPATH = $(CONTROLLER_PATH)/kconfig_handler:

	
				
##***************************************************************************##
## 							GENERAL MACRO FOR EXPORT 
##***************************************************************************##
INCLUDES += $(NAVIGATOR_INCLUDE) \
 $(KCONFIGPARSERHANDLER_INCLUDE)
				
CPPSRC += $(NAVIGATOR_CPPSRC)	\
 $(KCONFIGPARSERHANDLER_CPPSRC)
				
				
VPATH+=	$(NAVIGATOR_VPATH)		\
 $(KCONFIGPARSERHANDLER_VPATH)
