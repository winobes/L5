#include "player.c"
#include "init_rooms.c"
#include "init_npcs.c"
#include "common_def.c"
#include "update_logic.c"
#include "room_specific_logic.c"
#include "update_graphics.c"

int game_loop() {

	bool exit_game = false;
	bool redraw = true;

	GameState *gs = malloc(sizeof(GameState));

	gs->player = init_player(); // TODO free player
	gs->nrooms = 2;
	gs->room = init_rooms(gs);  // TODO free rooms and walls etc.
	gs->nnpcs = 2;
	gs->npc = init_npcs(gs);  // TODO free npc
	gs->current_room = 0;
	gs->font10 = al_load_font("fonts/Roboto-Black.ttf", 10,0);

	bool keys[5] = {false, false, false, false, false};

	ALLEGRO_EVENT event;
	al_start_timer(timer);

	// main update loop
	while(!exit_game) {

		al_wait_for_event(event_queue, &event);

		// TODO check types and inputs
		do_update(&event, keys, &exit_game, &redraw, gs);

		do_room_specific_update(gs);

		do_graphics_update(gs, &redraw);

	}

	return 0;
}
