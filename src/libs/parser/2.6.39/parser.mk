
##***************************************************************************##
## 									PARSER 
##***************************************************************************##
PARSER_CSRC =  $(PARSER_SRC_PATH)/yconf.c
PARSER_INCLUDE = -I"$(PARSER_SRC_PATH)"
PARSER_VPATH = $(PARSER_SRC_PATH):
PARSER_CFLAGS = -DROOTMENU=\"Rootmenu\"
PARSER_TARGETS = parser_gen
PARSER_CLEANTARGETS = parser_clean

.PRECIOUS: $(PARSER_CSRC)





##***************************************************************************##
## 							GENERAL MACRO FOR EXPORT 
##***************************************************************************##
INCLUDES +=	$(PARSER_INCLUDE)
CSRC +=	$(PARSER_CSRC)
VPATH += $(PARSER_VPATH)
CFLAGS += $(PARSER_CFLAGS)
TARGETS += $(PARSER_TARGETS)
CLEANTARGETS += $(PARSER_CLEANTARGETS)


##************* GENERATE PARSER SOURCES ***********************##

parser_gen:
	@echo "Generating parser sources "

	@gperf -t --output-file $(PARSER_SRC_PATH)/hconf.c -a -C -E -g -k 1,3,$$ -p -t $(PARSER_SRC_PATH)/hconf.gperf
	@flex -L -P zconf  -o$(PARSER_SRC_PATH)/lconf.c $(PARSER_SRC_PATH)/lconf.l
	@$(PARSER_SRC_PATH)/ylwrap $(PARSER_SRC_PATH)/yconf.y y.tab.c $(PARSER_SRC_PATH)/yconf.c y.tab.h $(PARSER_SRC_PATH)/yconf.h y.output yconf.output -- bison -y -t -l -p zconf
	
parser_clean:
	@rm -f $(PARSER_SRC_PATH)/yconf.c  $(PARSER_SRC_PATH)/hconf.c $(PARSER_SRC_PATH)/lconf.c
