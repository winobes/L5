#include "common_def.c"

#ifndef INIT_ALLEGRO_GAME_STATE_H
#define INIT_ALLEGRO_GAME_STATE_H

void abort_game(const char* message)
{
	printf("%s \n", message);
	exit(1);
}

void init_allegro(GameState *gs)
{
	if (!al_init()) {
		abort_game("Failed to initialize allegro");
	}
 
	if(!al_init_image_addon()){
		abort_game("failed to initialize allegro image addon!");
	}

	if (!al_install_keyboard()) {
		abort_game("Failed to install keyboard");
	}
 
	gs->timer = al_create_timer(1.0 / FPS);
	if (!gs->timer) {
		abort_game("Failed to create timer");
	}
 
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	gs->display = al_create_display(width, height);
	if (!gs->display){
		abort_game("Failed to create display");
	}
 
	gs->event_queue = al_create_event_queue();
	if (!gs->event_queue) {
		abort_game("Failed to create event queue");
	}

	al_init_font_addon();
	al_init_ttf_addon();

	al_register_event_source(gs->event_queue, al_get_keyboard_event_source());
	al_register_event_source(gs->event_queue, al_get_timer_event_source(gs->timer));
	al_register_event_source(gs->event_queue, al_get_display_event_source(gs->display));
}

#endif // INIT_ALLEGRO_GAME_STATE_H
