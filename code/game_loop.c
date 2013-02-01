#include "common_def.c"
#include "player.c"
#include "init_rooms.c"
#include "init_npcs.c"
#include "init_allegro.c"
#include "update_logic.c"
#include "room_specific_logic.c"
#include "update_graphics.c"
#include "shutdown.c"

int game_loop() {

	bool exit_game = false;
	bool redraw = true;

	int i, j, k;

	GameState *gs = malloc(sizeof(GameState));

	init_allegro(gs);

	
	gs->player = init_player(); // TODO fix the weapon init
	gs->nrooms = 2;
	gs->room = init_rooms(gs);
	gs->nnpcs = 2;
	gs->npc = init_npcs(gs);  
	gs->current_room = 0;
    gs->player_bullet = malloc(100 * sizeof(Bullet)); //TODO FREE
    for(i = 0; i < 100; i++) {
        gs->player_bullet[i].exist = false;
    }
    gs->current_pb = 0;
    gs->npc_bullet = malloc(100 * sizeof(Bullet)); //TODO FREE
    gs->current_nb = 0;
	gs->font10 = al_load_font("fonts/Roboto-Black.ttf", 10,0);

	bool *keys = malloc(NKEYS * sizeof(bool));
	for (i = 0; i < NKEYS; i++) {
		keys[i] = false;
	}

	ALLEGRO_EVENT event;
	al_start_timer(gs->timer);

	// main update loop
	while(!exit_game) {
		al_wait_for_event(gs->event_queue, &event);

		// TODO check types and inputs
		do_update(&event, keys, &exit_game, &redraw, gs);

		do_room_specific_update(gs);

		do_graphics_update(gs, &redraw);
	}

	// free everything we ever did malloc // TODO make individual teardown functions

	free(keys);

	// player
	
	#ifdef DEBUG
	printf("free player\n");
	#endif

	for (j = 0; j < gs->player->ext.nverts; j++) {
		free(gs->player->ext.vert[j]);
	}
	free(gs->player->ext.vert);
	free(gs->player->ext.y);
	free(gs->player->ext.x);
    free(gs->player->man_func);
    free(gs->player->man);
	free(gs->player->ani);
    free(gs->player->ani_func);

	al_destroy_bitmap(gs->player->spritesheet);
	gs->player->spritesheet = NULL;
	al_destroy_bitmap(gs->player->sprite);
	gs->player->sprite = NULL;
	free(gs->player);
	
	#ifdef DEBUG
	printf("free rooms\n");
	#endif

	// rooms
	for (i = 0; i < gs->nrooms; i++) {
		for (j = 0; j < gs->room[i]->nwalls; j++) {
			for (k = 0; k < gs->room[i]->wall[j]->ext.nverts; k++) {
				free(gs->room[i]->wall[j]->ext.vert[k]);
			}
			free(gs->room[i]->wall[j]->ext.vert);
			al_destroy_bitmap(gs->room[i]->wall[j]->sprite);
			gs->room[i]->wall[j]->sprite = NULL;
			free(gs->room[i]->wall[j]);
		}
		for (j = 0; j < gs->room[i]->nbackgrounds; j++) {
			al_destroy_bitmap(gs->room[i]->background[j].background_image);
			gs->room[i]->background[j].background_image = NULL;
		}
		if (gs->room[i]->nbackgrounds > 0) {
			free(gs->room[i]->background);			
		}
		free(gs->room[i]->wall);
		free(gs->room[i]);
	}
	free(gs->room);
	
	#ifdef DEBUG
	printf("free npcs\n");
	#endif

	// npcs
	for (i = 0; i < gs->nnpcs; i++) {
		free(gs->npc[i].ext.x);
		free(gs->npc[i].ext.y);
		for (j = 0; j < gs->npc[i].ext.nverts; j++) {
			free(gs->npc[i].ext.vert[j]);
		}
		free(gs->npc[i].ext.vert);
		free(gs->npc[i].ani);
        free(gs->npc[i].ani_func);
        free(gs->npc[i].man_func);
        free(gs->npc[i].man);

	}
	free(gs->npc);

	#ifdef DEBUG
	printf("free game state\n");
	#endif
	
	// GameState
	al_destroy_font(gs->font10);
	gs->font10 = NULL;

	shutdown_game(gs);

	free(gs);	
	
	#ifdef DEBUG
	printf("exiting game_loop\n");
	#endif

	return 0;
}
