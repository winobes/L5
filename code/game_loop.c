#include "player.c"
#include "init_rooms.c"
#include "init_npcs.c"
#include "common_def.c"
#include "update_logic.c"

int game_loop() {

	bool exit_game = false;
	bool redraw = true;

	//penetration variables are used by collision detection and response functions
	//float penetration_scalar;
	//float penetration_vector[2];

	int i;
	int j;
	
	ALLEGRO_FONT *font10 = al_load_font("fonts/Roboto-Black.ttf", 10,0);

	GameState *gs = malloc(sizeof(GameState));

	gs->player = init_player(); // TODO free player
	gs->nrooms = 2;
	gs->room = init_rooms(gs);  // TODO free rooms and walls etc.
	gs->nnpcs = 2;
	gs->npc = init_npcs(gs);  // TODO free npc

	bool keys[5] = {false, false, false, false, false};

	ALLEGRO_EVENT event;
	al_start_timer(timer);

	// main update loop
	while(!exit_game) {

		al_wait_for_event(event_queue, &event);

		// TODO check types and inputs
		do_update(&event, keys, &exit_game, &redraw, gs);

	#include "room_specific_logic.c"

		#include "update_graphics.c"

	}

	#include "destroy_bitmaps.c"

	return 0;
}
