slp.tab.c slp.tab.h: slp.y
	bison -d slp.y

lex.yy.c: slp.l slp.tab.h
	flex slp.l

slp: lex.yy.c slp.tab.c slp.tab.h table.h table.cc node.h node.cc codegen.h codegen.cc functiontable.h functiontable.cc
	g++ table.cc functiontable.cc node.cc codegen.cc slp.tab.c lex.yy.c -o slp -ll

.PHONE: clean
clean:
	rm -f *.o slp.tab.c slp.tab.h lex.yy.c slp

