#
# SpeedBoot, a boot time optimization tool
#
# Copyright (c) 2015,
# Hochschule Offenburg, University of Applied Sciences
# Laboratory Embedded Systems and Communications Electronics.
#    
#
# This work is licensed under the terms of the GNU GPL, version 2.  See
# the COPYING file in the top-level directory.
#

##***************************************************************************##
## 									NCURSES 
##***************************************************************************##

NCURSES_CPPSRC = $(wildcard $(NCURSES_PATH)/BasicUI.cpp)
NCURSES_INCLUDE = -I"$(NCURSES_PATH)"
NCURSES_VPATH =	$(NCURSES_PATH):
NCURSES_LIBS = -lcurses


	
				
##***************************************************************************##
## 							GENERAL MACRO FOR EXPORT 
##***************************************************************************##
INCLUDES += $(NCURSES_INCLUDE)
CPPSRC += $(NCURSES_CPPSRC)
VPATH += $(NCURSES_VPATH)
LIBS += $(NCURSES_LIBS)
