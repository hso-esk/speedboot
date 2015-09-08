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

## Main Makefile
EXENAME = sbconf

## Setup the tools
CC = gcc
CXX = g++
LD = g++

## Reset compiler and linker flags
CFLAGS =
DBGFLAGS = -g3
OPTFLAGS = -O0

LDFLAGS =
LIBSDIR =
LIBS =

## Configure directories
ROOT_DIR:= $(subst /toolchain/$(TOOLCHAIN),,$(shell echo -n $(CURDIR)))
export ROOT_DIR

PARSER_PATH = $(ROOT_DIR)/libs/parser
export PARSER_PATH

LXDIALOG_PATH = $(ROOT_DIR)/libs/lxdialog
export LXDIALOG_PATH

CONTROLLER_PATH	= $(ROOT_DIR)/controller
export CONTROLLER_PATH

MODEL_PATH = $(ROOT_DIR)/model
export MODEL_PATH

FRONTEND_PATH = $(ROOT_DIR)/frontends
export	FRONTEND_PATH

EXEPATH = $(ROOT_DIR)/../build
EXE = $(EXEPATH)/$(EXENAME)

MAPFILE = $(EXEPATH)/$(EXENAME).map
LDFLAGS = -Wl,-Map,$(MAPFILE)

## This makefile will assemble the parser
include $(PARSER_PATH)/parser.mk

## This makefile will assemble lxdialog
include $(LXDIALOG_PATH)/lxdialog.mk

## This makefile will assemble the controller
include $(CONTROLLER_PATH)/controller.mk

## This makefile will assemble the model
include $(MODEL_PATH)/model.mk

## This makefile will assemble the frontend
include $(FRONTEND_PATH)/frontend.mk

## add root dir to include and main file to sources
INCLUDES +=	-I"$(ROOT_DIR)"
CPPSRC += $(ROOT_DIR)/main.cpp

## Generate list of objects which should be generated in order 
## to link target executive file
COBJ = $(CSRC:.c=.o)
CPPOBJ += $(CPPSRC:.cpp=.o)

# Reset the default goal.
.DEFAULT_GOAL :=

all : dir $(PARSER_TARGETS) compile $(EXE)

##************* CREATE DIRECTORY***********************##
dir:
	@mkdir -p $(EXEPATH)

##************* COMPILE SOURCES ***********************##
compile: ${COBJ} ${CPPOBJ}
%.o : %.c
		@echo "Compile: " $<
		@$(CC) -MMD -MP -c $(CFLAGS) $(DBGFLAGS) $(OPTFLAGS) $(INCLUDES) $< -o $@
%.o : %.cpp
		@echo "Compile: " $<
		@$(CXX) -MMD -MP -c $(CFLAGS) $(DBGFLAGS) $(OPTFLAGS) $(INCLUDES) $< -o $@

	
##************* LINK EXECUTABLE ***********************##	
$(EXE): compile
		@echo "Linking: " $@ 
		@$(LD) $(LDFLAGS) $(DBGFLAGS) ${COBJ} ${CPPOBJ} $(LIBSDIR) $(LIBS) -o $@
		
##***************** CLEAN *****************************##
clean: $(CLEANTARGETS)
	@find ../ -name '*.o' -delete
	@find ../ -name '*.lo' -delete
	@find ../ -name '*.lst' -delete
	@find ../ -name '*.map' -delete
	@find ../ -name '*.srec' -delete


.PHONY: all compile link clean $(TARGETS) $(CLEANTARGETS)








