##***************************************************************************##
## 									LXDIALOG 
##***************************************************************************##

LXDIALOG_CSRC = $(wildcard $(LXDIALOG_PATH)/*.c)
LXDIALOG_INCLUDE = -I"$(LXDIALOG_PATH)"
LXDIALOG_VPATH = $(LXDIALOG_PATH):
LXDIALOG_CFLAGS =  -DCURSES_LOC="<ncurses.h>"


	
				
##***************************************************************************##
## 							GENERAL MACRO FOR EXPORT 
##***************************************************************************##
INCLUDES += $(LXDIALOG_INCLUDE)
CSRC += $(LXDIALOG_CSRC)
VPATH += $(LXDIALOG_VPATH)
CFLAGS += $(LXDIALOG_CFLAGS)