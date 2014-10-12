#ifndef CORE_H 
#define CORE_H 

#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600
#define BPS 60

typedef struct core_components {
        ALLEGRO_TIMER *timer;
        ALLEGRO_EVENT_QUEUE *queue;
        ALLEGRO_DISPLAY *display;
} core_components;

void init_allegro(core_components *core);
void game_loop(core_components *core);
void game_shutdown(core_components *core);

#endif /* CORE_H */
