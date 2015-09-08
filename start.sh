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


# the local path to the buildroot system
BSPATH=""

# the name of the buildsystem
BUILDSYSTEM=


#if [ $BUILDSYSTEM -eq "" ]
if [ -z "$BUILDSYSTEM" ]
then
  echo ""
  echo "assuming the buildsystem is \"Buildroot\" "
  echo ""
  BUILDSYSTEM=buildroot
fi

#if [ $BSPATH  -eq "" ]
if [ -z "$BSPATH" ]
then
  echo ""
  echo "please give the path to the local buildroot folder"
  echo ""
  exit
fi
 
make BUILDSYSTEM=$BUILDSYSTEM BSPATH=$BSPATH

