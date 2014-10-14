cc = gcc -std=c11 -Wall
objects = main.o core.o log.o error.o physics.o game_data.o graphics.o

game : $(objects)
	$(cc) -o "L5 Arena" $(objects) `pkg-config --libs allegro_main-5.0 allegro_dialog-5.0 allegro_primitives-5.0` -lm

main.o : main.c core.h 
	$(cc) -c -o main.o main.c

core.o : core.c core.h
	$(cc) -c -o core.o core.c

log.o : log.c log.h
	$(cc) -c -o log.o log.c

error.o : error.c error.h
	$(cc) -c -o error.o error.c

physics.o : physics.c physics.h
	$(cc) -c -o physics.o physics.c

game_data.o : game_data.c game_data.h
	$(cc) -c -o game_data.o game_data.c

graphics.o : graphics.c graphics.h
	$(cc) -c -o graphics.o graphics.c

.PHONY : clean
clean : 
	rm -f $(objects) *.log "L5 Arena"
