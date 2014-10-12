#ifndef CORE_H 
#define CORE_H 

#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600
#define BPS 60

typedef struct engine_core {
        ALLEGRO_TIMER *timer;
        ALLEGRO_EVENT_QUEUE *queue;
        ALLEGRO_DISPLAY *display;
} engine_core;

void init_allegro(engine_core *core);
void game_loop(engine_core *core);
void game_shutdown(engine_core *core);

#endif /* CORE_H */
