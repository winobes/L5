all: code/main.c
	gcc -Wall -o a code/main.c -lm `pkg-config --cflags --libs allegro-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0`
