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


##
# Example: make BUILDSYSTEM=buildroot BSPATH=../buildroot

##
# Common variables needed for build and execution
SBBTPATH=$(CURDIR)
SBBTSRCPATH=$(SBBTPATH)/src
SBBTBINPATH=$(SBBTPATH)/build
SBBTEXE=$(SBBTBINPATH)/sbconf
BSCONFIGS=$(SBBTPATH)/buildconfigs

## a valid buildsystem must be defined
ifndef BUILDSYSTEM
$(error No buildsystem defined [BUILDSYSTEM=???]. Supported values:	\
	buildroot, buildrootdebug)
else
ifeq ($(BUILDSYSTEM), buildroot)
BSCONFIGPATH=$(BSCONFIGS)/buildroot
else ifeq ($(BUILDSYSTEM), buildrootdebug)
BSCONFIGPATH=$(BSCONFIGS)/buildroot_debug
else
$(error $(BUILDSYSTEM) is not a valid buildsystem. Supported values:	\
	buildroot)
endif

ifndef BSPATH
$(error No path to buildsystem defined [BSPATH=???].)
endif
endif

##
# Export variables for further usage
export BSCONFIGPATH
export SBBTPATH
export SBBTSRCPATH
export SBBTBINPATH
export SBBTEXE

##
# Inlcude the buildsystem specific makefile
include $(BSCONFIGPATH)/bs.mk

