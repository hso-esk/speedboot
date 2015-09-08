
##***************************************************************************##
## 									PARSER 
##***************************************************************************##
PARSER_CSRC =  $(PARSER_SRC_PATH)/zconf.c
PARSER_INCLUDE = -I"$(PARSER_SRC_PATH)"
PARSER_VPATH = $(PARSER_SRC_PATH):
PARSER_CFLAGS = -DROOTMENU=\"Rootmenu\" -DPATH_MAX=255
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
	@gperf -t --output-file $(PARSER_SRC_PATH)/zconf.hash.c -a -C -E -g -k 1,3,$$ -p -t $(PARSER_SRC_PATH)/zconf.gperf
	@flex -L -P zconf  -o$(PARSER_SRC_PATH)/zconf.lex.c $(PARSER_SRC_PATH)/zconf.l
	@bison -y -t -l -p zconf $(PARSER_SRC_PATH)/zconf.y -o $(PARSER_SRC_PATH)/zconf.c
	
parser_clean:
	@rm -f $(PARSER_SRC_PATH)/zconf.c  $(PARSER_SRC_PATH)/zconf.lex.c $(PARSER_SRC_PATH)/zconf.hash.c
