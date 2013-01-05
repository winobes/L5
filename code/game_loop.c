#include "player.c"
#include "init_rooms.c"

int game_loop() {

//	ALLEGRO_BITMAP *parallax_m = al_load_bitmap("gfx/parallax_main.png");
	ALLEGRO_BITMAP *background1 = al_load_bitmap("gfx/parallax_sub.png");
	ALLEGRO_BITMAP *background3 = al_load_bitmap("gfx/parallax_super.png");
	ALLEGRO_BITMAP *background2 = al_load_bitmap("gfx/parallax_earth.png");

	bool exit_game = false;
	bool redraw = true;

	//penetration variables are used by collision detection and response functions
	float penetration_scalar;
	float penetration_vector[2];

	float parallax_counter;
	bool parallax_switch;

	float parallax1_rate = .05;
	int parallax1_x1;
	int parallax1_x2;
	int parallax1_y1;
	int parallax1_y2;

	float parallax2_rate = .1;

	float parallax3_rate = .2;
	int parallax3_x1;
	int parallax3_x2;
	int parallax3_y1;
	int parallax3_y2;


	// now in init_rooms.c
	//int nrooms = 2;
	//int k;

	int nnpcs = 2;

	int i;
	int j;
	
	ALLEGRO_FONT *font10 = al_load_font("fonts/Roboto-Black.ttf", 10,0);


    Player *player = init_player(); // TODO free player
    Room **room = init_rooms();  // TODO free rooms and walls etc.
	#include "init_npcs.c"


	ALLEGRO_EVENT event;
	al_start_timer(timer);

	while(!exit_game) {

		al_wait_for_event(event_queue, &event);

		#include "get_input.c"

/*		if (change_room != -1) {
//			previous_room = current_room;//used to destroy the bitmaps in the previous room
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


