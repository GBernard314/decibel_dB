WARNING_FLAGS = -Wall -std=gnu99
LIBRARYS = -lm -lncurses

decibel : function.o affichage.o
	gcc -o decibel function.o affichage.o ${LIBRARYS}

function.o : function.c function.h
	gcc ${WARNING_FLAGS} -c function.c

affichage.o: affichage.c function.h
	gcc ${WARNING_FLAGS} -c affichage.c


clean:
	rm -f *.o *~ core $(EXO)
