gridTester : display.o gridTester.o gridMaker.o
	gcc display.o gridTester.o gridMaker.o -o gridTester -lX11 -g

display.o : display.c display.h obstacles.h
	gcc -c display.c -g

gridTester.o : gridTester.c obstacles.h display.h
	gcc -c gridTester.c -g

gridMaker.o : gridMaker.c obstacles.h
	gcc -c gridMaker.c -g
