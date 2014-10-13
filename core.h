#ifndef CORE_H 
#define CORE_H 

#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600
#define BPS 60

typedef struct Engine_Core {
        ALLEGRO_TIMER *timer;
        ALLEGRO_EVENT_QUEUE *queue;
        ALLEGRO_DISPLAY *display;
} Engine_Core;

void init_allegro(Engine_Core *core);
void game_loop(Engine_Core *core);
void game_shutdown(Engine_Core *core);

#endif /* CORE_H */
