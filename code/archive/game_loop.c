int game_loop() {

	bool exit_game = false;
	bool redraw = true;
	
	int nrooms = 2;
	int change_room = 0;
	int current_room = -1;
	int previous_room = -1;


	int current_p_missile = 0;
	int player_can_collide = true;

	int i;
	int j;
	int k;

	ALLEGRO_FONT *font10 = al_load_font("fonts/Roboto-Black.ttf", 10,0);


	struct Subject player;
	player.health = 100;
	player.x = 0;
	player.y = 0;
	player.width = 15;
	player.height = 15;
	player.dx = 0;
	player.dy = 0;
	player.direction = 0;
	player.rotation = .03;
	player.acceleration = .03;
	player.sprite = al_create_bitmap(15, 15);
	player.weapon = 1;
	player.reload_time = 10;
	player.reload_timer = 0;
	player.nanimatics = 3;
	
	player.spritesheet = al_load_bitmap("gfx/firefly_spritesheet.png");

	player.animatic = malloc(player.nanimatics * sizeof(struct Animatic));

	player.animatic[0].source_x = 0;
	player.animatic[0].source_y = 0;
	player.animatic[0].width = 15;
	player.animatic[0].height = 15;
	player.animatic[0].pivot_x = 8;
	player.animatic[0].pivot_y = 8;
	player.animatic[0].destination_x = 8;
	player.animatic[0].destination_y = 8;
	player.animatic[0].scale_x = 1;
	player.animatic[0].scale_y = 1;
	player.animatic[0].is_running = false;
	player.animatic[0].draw = true;
	player.animatic[0].key = -1;
	player.animatic[0].tint = al_map_rgba_f(1,1,1,1);


	player.animatic[1].source_x = 0;
	player.animatic[1].source_y = 15;
	player.animatic[1].width = 15;
	player.animatic[1].height = 15;
	player.animatic[1].pivot_x = 8;
	player.animatic[1].pivot_y = 8;
	player.animatic[1].destination_x = 8;
	player.animatic[1].destination_y = 8;
	player.animatic[1].scale_x = 1;
	player.animatic[1].scale_y = 1;
	player.animatic[1].is_running = false;
	player.animatic[1].draw = false;
	player.animatic[1].nframes = 4;
	player.animatic[1].frame_rate = 15;
	player.animatic[1].key = UP;
	player.animatic[1].tint = al_map_rgba_f(1,1,1,1);

	player.animatic[2].source_x = 0;
	player.animatic[2].source_y = 30;
	player.animatic[2].width = 15;
	player.animatic[2].height = 15;
	player.animatic[2].pivot_x = 8;
	player.animatic[2].pivot_y = 8;
	player.animatic[2].destination_x = 8;
	player.animatic[2].destination_y = 8;
	player.animatic[2].scale_x = 1;
	player.animatic[2].scale_y = 1;
	player.animatic[2].is_running = false;
	player.animatic[2].draw = false;
	player.animatic[2].nframes = 4;
	player.animatic[2].frame_rate = 15;
	player.animatic[2].key = DOWN;
	player.animatic[2].tint = al_map_rgba_f(1,1,1,1);



	struct Room room[nrooms];
	for (i = 0; i < nrooms; i++) {
		room[i].initialized = false;
	}
	
	struct Subject p_missile[100];
	for (i = 0; i < 100; i++) {
		p_missile[i].exist = false;
	}


	ALLEGRO_EVENT event;
	al_start_timer(timer);

	while(!exit_game) {

		al_wait_for_event(event_queue, &event);

		#include "get_input.c"

		if (change_room != -1) {
			previous_room = current_room;
			current_room = change_room;
			change_room = -1;
			#include "change_room.c"
		}

		#include "update_logic.c"
		#include "room_specific_logic.c"

		#include "update_graphics.c"

	}

	#include "destroy_bitmaps.c"

	return 0;

}


