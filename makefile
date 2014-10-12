objects = main.o core.o log.o error.o

game : $(objects)
	gcc -Wall -o "L5 Arena" $(objects) `pkg-config --libs allegro_main-5.0 allegro_dialog-5.0` 

main.o : main.c core.h 
	gcc -Wall -c -o main.o main.c

core.o : core.c core.h
	gcc -Wall `pkg-config --cflags allegro_main-5.0` -c -o core.o core.c

log.o : log.c log.h
	gcc -Wall -c -o log.o log.c `pkg-config --cflags`

error.o : error.c error.h
	gcc -Wall -c -o error.o error.c

.PHONY : clean
clean : 
	rm -f $(objects) *.log "L5 Arena"
