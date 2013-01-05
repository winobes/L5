#include "player.c"
#include "init_rooms.c"
#include "init_npcs.c"

int game_loop() {

	bool exit_game = false;
	bool redraw = true;

	//penetration variables are used by collision detection and response functions
	float penetration_scalar;
	float penetration_vector[2];

	// now in init_rooms.c
	//int nrooms = 2;
	//int k;

	int nnpcs = 2;

	int i;
	int j;
	
	ALLEGRO_FONT *font10 = al_load_font("fonts/Roboto-Black.ttf", 10,0);

	Player *player = init_player(); // TODO free player
	Room **room = init_rooms();  // TODO free rooms and walls etc.
	NPC *npc = init_npcs();  // TODO free npc

	ALLEGRO_EVENT event;
	al_start_timer(timer);

	while(!exit_game) {

		al_wait_for_event(event_queue, &event);

		#include "get_input.c"

	/*	if (change_room != -1) {
	//		previous_room = current_room;//used to destroy the bitmaps in the previous room
			current_room = change_room;
			change_room = -1;
			#include "change_room.c"
		}*/

	#include "update_logic.c"
	#include "room_specific_logic.c"

		#include "update_graphics.c"

	}

	#include "destroy_bitmaps.c"

	return 0;
}
