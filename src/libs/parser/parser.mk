##***************************************************************************##
## 									FRONTEND 
##***************************************************************************##

ifndef PARSER
$(warning No PARSER defined [PARSER=???]. Supported values:	\
	2.6.39	\
	3.17	\
)
$(warning Using default PARSER [PARSER=2.6.39])
PARSER=2.6.39
endif

ifeq ($(PARSER), 2.6.39)
PARSER_SRC_PATH = $(PARSER_PATH)/2.6.39
export PARSER_SRC_PATH
endif

ifeq ($(PARSER), 3.17)
PARSER_SRC_PATH = $(PARSER_PATH)/3.17
export PARSER_SRC_PATH
endif

include $(PARSER_SRC_PATH)/parser.mk

