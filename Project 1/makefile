ABook : userinterface.c userinterface.h database.c database.h record.h
	gcc -o ABook userinterface.c database.c

userinterface.o : userinterface.c userinterface.h database.h record.h
	gcc -c -ansi -Wall userinterface.c
	
database.o : database.c database.h record.h
	gcc -c -ansi -Wall database.c

clean : 
	rm -f ABook
	rm -f *.o
	
cleanall:
	rm -f save.txt
	rm -f ABook
	rm -f *.o