slp.tab.c slp.tab.h: slp.y
	bison -d slp.y

lex.yy.c: slp.l slp.tab.h
	flex slp.l

slp: lex.yy.c slp.tab.c slp.tab.h
	g++ node.h slp.tab.c lex.yy.c -o slp -ll

.PHONE: clean
clean:
	rm -f slp.tab.c slp.tab.h lex.yy.c slp

