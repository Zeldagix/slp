slp.tab.c slp.tab.h: slp.y
	bison -d slp.y

lex.yy.c: slp.l slp.tab.h
	flex slp.l

slp: lex.yy.c slp.tab.c slp.tab.h table.h table.cc node.h node.cc
	g++ table.cc node.cc slp.tab.c lex.yy.c -o slp -ll

.PHONE: clean
clean:
	rm -f *.o slp.tab.c slp.tab.h lex.yy.c slp

