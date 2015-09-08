all: clean generate

generate:
	@echo "Generating parser sources "
	@gperf -t --output-file hconf.c -a -C -E -g -k 1,3,$$ -p -t hconf.gperf
	@flex -L -P zconf  -olconf.c lconf.l
	@./ylwrap yconf.y y.tab.c yconf.c y.tab.h yconf.h y.output yconf.output -- bison -y -t -l -p zconf
	
clean:
	@rm -f ./yconf.c  ./hconf.c ./lconf.c
