objects = main.o core.o log.o error.o physics.o

game : $(objects)
	gcc -std=c99 -Wall -o "L5 Arena" $(objects) `pkg-config --libs allegro_main-5.0 allegro_dialog-5.0` -lm

main.o : main.c core.h 
	gcc -std=c99 -Wall -c -o main.o main.c

core.o : core.c core.h
	gcc -std=c99 -Wall `pkg-config --cflags allegro_main-5.0` -c -o core.o core.c

log.o : log.c log.h
	gcc -std=c99 -Wall -c -o log.o log.c `pkg-config --cflags`

error.o : error.c error.h
	gcc -std=c99 -Wall -c -o error.o error.c

physics.o : physics.c physics.h
	gcc -std=c99 -Wall -c -o physics.o physics.c

.PHONY : clean
clean : 
	rm -f $(objects) *.log "L5 Arena"
