#include "common_def.c"

#ifndef UPDATE_LOGIC_H
#define UPDATE_LOGIC_H


// return effects of receiving input pass by reference to calling game loop function
void get_input(ALLEGRO_EVENT *event, bool *keys, bool *exit_game)
{
	if(event->type == ALLEGRO_EVENT_KEY_DOWN) {
		switch(event->keyboard.keycode) {
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_LCTRL:
				keys[LCTRL] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = true;
				break;
			case ALLEGRO_KEY_W:
				keys[W] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = true;
				break;
		}
	} else if (event->type == ALLEGRO_EVENT_KEY_UP) {
		switch(event->keyboard.keycode) {
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_LCTRL:
				keys[LCTRL] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = false;
				break;
			case ALLEGRO_KEY_W:
				keys[W] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = false;
				break;
		}
	} else if(event->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		*exit_game = true;
	}
}

void update_logic(ALLEGRO_EVENT *event, bool *keys, GameState *gs)
{
	float penetration_scalar;
	float penetration_vector[2];

	if(event->type == ALLEGRO_EVENT_TIMER) {

		//updating player direction
		if (keys[RIGHT]) {
			gs->player->d += gs->player_turn_speed * gs->player->dd*ALLEGRO_PI;
			
			if(!keys[UP]) {
				gs->player->dx += gs->player_forward_speed * gs->player->ddxy * cos(gs->player->d - ALLEGRO_PI/2);
				gs->player->dy += gs->player_forward_speed * gs->player->ddxy * sin(gs->player->d - ALLEGRO_PI/2);
			}

			/*	if(!keys[LEFT]) {
				gs->player->cx += (-cos(gs->player->d) - -cos(gs->player->d - .5*gs->player->dd*ALLEGRO_PI)) * gs->player->w;
				gs->player->cy += (-sin(gs->player->d) - -sin(gs->player->d - .5*gs->player->dd*ALLEGRO_PI)) * gs->player->w;

			}*/
		}

		if (keys[LEFT]) {
			gs->player->d -= gs->player_turn_speed * gs->player->dd*ALLEGRO_PI;
			
			if(!keys[UP]) {
				gs->player->dx += gs->player_forward_speed * gs->player->ddxy * cos(gs->player->d - ALLEGRO_PI/2);
				gs->player->dy += gs->player_forward_speed * gs->player->ddxy * sin(gs->player->d - ALLEGRO_PI/2);
			}
		
			/*	if(!keys[RIGHT]) {
				gs->player->cx += (-cos(gs->player->d) - -cos(gs->player->d - .5*gs->player->dd*ALLEGRO_PI)) * gs->player->w;
				gs->player->cy += (-sin(gs->player->d) - -sin(gs->player->d - .5*gs->player->dd*ALLEGRO_PI)) * gs->player->w;
			}*/
		}

		// wrap orientation to the range [0,2*PI]
		if (gs->player->d > 2*ALLEGRO_PI) {
			gs->player->d -= 2*ALLEGRO_PI;
		} else if (gs->player->d < 0) {
			gs->player->d += 2*ALLEGRO_PI;
		}

		// add thrust sideways left relative to forward vector of player ship direction
		if (keys[A]) {
			gs->player->dx += gs->player_side_speed * gs->player->ddxy * cos(gs->player->d - ALLEGRO_PI);
			gs->player->dy += gs->player_side_speed * gs->player->ddxy * sin(gs->player->d - ALLEGRO_PI);		
		}

		// player thrust forward full speed
		if (keys[W]) {
			gs->player->dx += gs->player->ddxy * 5 * cos(gs->player->d - ALLEGRO_PI/2);
			gs->player->dy += gs->player->ddxy * 5 * sin(gs->player->d - ALLEGRO_PI/2);
		}

		// add thrust sideways right relative to forward vector of player ship direction
		if (keys[D]) {
			gs->player->dx += gs->player_side_speed * gs->player->ddxy * cos(gs->player->d);
			gs->player->dy += gs->player_side_speed * gs->player->ddxy * sin(gs->player->d);		
		}

		//updating player dy and dx based on acceleration & direction
		if (keys[UP]) {
			gs->player->dx += gs->player->ddxy * cos(gs->player->d - ALLEGRO_PI/2);
			gs->player->dy += gs->player->ddxy * sin(gs->player->d - ALLEGRO_PI/2);
		}
		//moving backwords...
		if (keys[DOWN]) {
			gs->player->dx -= gs->player->ddxy * cos(gs->player->d - ALLEGRO_PI/2);
			gs->player->dy -= gs->player->ddxy * sin(gs->player->d - ALLEGRO_PI/2);
		}

		//updating gs->player position based on dx and dy
		gs->player->cx += gs->player->dx;
		gs->player->cy += gs->player->dy;

		//recalculating the gs->player vertices
		calculate_verts_ship(gs->player->shape, &gs->player->ext, gs->player->cx, gs->player->cy, gs->player->w, gs->player->h, gs->player->d);

		//updating NPC AI & Input
		int i, j;
		for (i = 0; i < gs->nnpcs; i++) {
			switch (gs->npc[i].ai) {
				case 0:
					break;
				case 1:
					ai1(gs, i);
					break;
			}

			//updating NPC direction
			if (gs->npc[i].keys[RIGHT]) {
				gs->npc[i].d += .5*gs->npc[i].dd*ALLEGRO_PI;
			}

			if (gs->npc[i].keys[LEFT]) {
				gs->npc[i].d -= .5*gs->npc[i].dd*ALLEGRO_PI;
			}

			if (gs->npc[i].d > 2*ALLEGRO_PI) {
				gs->npc[i].d -= 2*ALLEGRO_PI;
			}

			if (gs->npc[i].d < 0) {
				gs->npc[i].d += 2*ALLEGRO_PI;
			}

			//updating NPC dy and dx based on acceleration & direction
			if (gs->npc[i].keys[UP]) {
				gs->npc[i].dx += gs->npc[i].ddxy * cos(gs->npc[i].d - ALLEGRO_PI/2);
				gs->npc[i].dy += gs->npc[i].ddxy * sin(gs->npc[i].d - ALLEGRO_PI/2);
			}
			//moving backwords...
			if (gs->npc[i].keys[DOWN]) {
				gs->npc[i].dx -= gs->npc[i].ddxy * cos(gs->npc[i].d - ALLEGRO_PI/2);
				gs->npc[i].dy -= gs->npc[i].ddxy * sin(gs->npc[i].d - ALLEGRO_PI/2);
			}

			calculate_speed(gs->npc[i].dx, gs->npc[i].dy, &gs->npc[i].s);

			//updating NPC position based on dx and dy
			gs->npc[i].cx += gs->npc[i].dx;
			gs->npc[i].cy += gs->npc[i].dy;

			//recalculating the NPC vertices
			calculate_verts_ship(gs->npc[i].shape, &gs->npc[i].ext, gs->npc[i].cx, gs->npc[i].cy, gs->npc[i].w, gs->npc[i].h, gs->npc[i].d);
		}

		//check for player collisions with walls

		gs->player->hit_wall = -1;
		for (i = 0; i < gs->room[gs->current_room]->nwalls; i++) {
			if (gs->room[gs->current_room]->wall[i]->exists) {

				if (collide(gs->player->ext, gs->room[gs->current_room]->wall[i]->ext, penetration_vector, &penetration_scalar)) {

					gs->player->hit_wall = i;
				
					if (gs->room[gs->current_room]->wall[i]->solid) {
						gs->player->cx += penetration_vector[0] * penetration_scalar;
						gs->player->cy += penetration_vector[1] * penetration_scalar;
				
						reflect(&gs->player->dx, &gs->player->dy, penetration_vector);
					}
				}
			}
		}

		//check for gs->player collisions with NPCs

		for (i = 0; i < gs->nnpcs; i++) {
			if (gs->npc[i].exists && gs->npc[i].room == gs->current_room) {
				if (collide(gs->player->ext, gs->npc[i].ext, penetration_vector, &penetration_scalar)) {
					if (gs->npc[i].solid) {
						//separating by the projection vector so that they are no longer colliding
						gs->player->cx += penetration_vector[0] * penetration_scalar/2;
						gs->player->cy += penetration_vector[1] * penetration_scalar/2;
				
						gs->npc[i].cx += -penetration_vector[0] * penetration_scalar/2;
						gs->npc[i].cy += -penetration_vector[1] * penetration_scalar/2;

						bounce(gs->player->m, gs->npc[i].m, .9, gs->player->cx, gs->player->cy, gs->npc[i].cx, gs->npc[i].cy, &gs->player->dx, &gs->player->dy, &gs->npc[i].dx, &gs->npc[i].dy);
							
						calculate_speed(gs->player->dx, gs->player->dy, &gs->player->s);
						calculate_speed(gs->npc[i].dx, gs->npc[i].dy, &gs->npc[i].s);
					}
				}
			}
		}

		//check for NPC collisions with walls

		for (i = 0; i < gs->nnpcs; i++) {
			for (j = 0; j < gs->room[gs->npc[i].room]->nwalls; j++) {
				if (gs->room[gs->npc[i].room]->wall[j]->exists) {
					if (collide(gs->npc[i].ext, gs->room[gs->npc[i].room]->wall[j]->ext, penetration_vector, &penetration_scalar)) {
						if (gs->room[gs->npc[i].room]->wall[j]->solid) {
							gs->npc[i].cx += penetration_vector[0] * penetration_scalar;
							gs->npc[i].cy += penetration_vector[1] * penetration_scalar;
				
							reflect(&gs->npc[i].dx, &gs->npc[i].dy, penetration_vector);
						}
					}
				}
			}
		}

		//updating gs->player bullett position

		if(gs->player->weapon.reload_timer < gs->player->weapon.reload_time) {
			gs->player->weapon.reload_timer++;
		}

		if (keys[gs->player->weapon.key] && gs->player->weapon.reload_timer == gs->player->weapon.reload_time) {
			gs->player->weapon.reload_timer = 0;
			gs->player->weapon.exists[gs->player->weapon.current] = true;
			gs->player->weapon.d[gs->player->weapon.current] = gs->player->d;
		
			gs->player->weapon.x[gs->player->weapon.current] = gs->player->cx + 0;
			gs->player->weapon.y[gs->player->weapon.current] = gs->player->cy + 0;
		
			gs->player->weapon.dx[gs->player->weapon.current] = gs->player->dx + 3 * cos(gs->player->d - ALLEGRO_PI/2);
			gs->player->weapon.dy[gs->player->weapon.current] = gs->player->dy + 3 * sin(gs->player->d - ALLEGRO_PI/2);
			
			gs->player->weapon.current ++;
			if (gs->player->weapon.current == gs->player->weapon.nactive) {
				gs->player->weapon.current = 0;
			}
		}
			
		//checking for bullet collision with NPCs & walls
		for (j = 0; j < gs->player->weapon.nactive; j++) {
			if(gs->player->weapon.exists[j]) {
				gs->player->weapon.ext.vert[0][0] = gs->player->weapon.x[j];
				gs->player->weapon.ext.vert[0][1] = gs->player->weapon.y[j];

				for (i = 0; i < gs->room[gs->current_room]->nwalls; i++) {
					if(gs->room[gs->current_room]->wall[i]->exists) {
						if(collide(gs->player->weapon.ext, gs->room[gs->current_room]->wall[i]->ext, penetration_vector, &penetration_scalar)) {
							gs->player->weapon.exists[j] = false;
							gs->room[gs->current_room]->wall[i]->health -= gs->player->weapon.damage;
						}
					}
				}

				for (i = 0; i < gs->nnpcs; i++) {
					if (gs->npc[i].exists && gs->npc[i].room == gs->current_room) {
						if (collide(gs->player->weapon.ext, gs->npc[i].ext, penetration_vector, &penetration_scalar)) {

							gs->player->weapon.exists[j] = false;
							gs->npc[i].health -= gs->player->weapon.damage;
						}	
					}
					if (gs->npc[i].health <= 0) {
						gs->npc[i].exists = false;
					}
				}
			}
		}

		for (i = 0; i < gs->player->weapon.nactive; i++) {
			if(gs->player->weapon.exists[i]) {
				gs->player->weapon.x[i] += gs->player->weapon.dx[i];
				gs->player->weapon.y[i] += gs->player->weapon.dy[i];
			}
		}

		//updating player animation flags

		gs->player->aniflags[1] = true;

		if (keys[UP]) {
			gs->player->aniflags[2] = true;
			gs->player->aniflags[3] = true;
			gs->player->aniflags[4] = true;
		}

		if (keys[RIGHT]) {
			gs->player->aniflags[3] = true;
		}
		
		if (keys[LEFT]) {
			gs->player->aniflags[4] = true;
		}

		if (keys[DOWN]) {
			gs->player->aniflags[5] = true;
			gs->player->aniflags[6] = true;
		}

		//updating player animation variables
		for (i = 0; i < gs->player->nanimatics; i++) {
			switch (gs->player->ani[i].type) {
				case 0:
					break;
				case 1:
					animatic1(&gs->player->ani[i], gs->player->aniflags);
					break;
			}
		}

		for (i = 0; i < gs->player->nanimatics; i++) {
			gs->player->aniflags[i] = false;
		}

		//updating player weapon animation variables
		for (i = 0; i < gs->player->weapon.nactive; i++) {
			if (gs->player->weapon.exists[i]) {
				gs->player->weapon.timer[i] ++;
				if (gs->player->weapon.timer[i] == gs->player->weapon.frame_rate) {
					gs->player->weapon.timer[i] = 0;
					if(gs->player->weapon.source_x[i] == gs->player->weapon.w * (gs->player->weapon.nframes - 1)) {
						gs->player->weapon.source_x[i] = 0;
					}	
					else {
						gs->player->weapon.source_x[i] += gs->player->weapon.w;
					}
				}
			}
		}			
		
		//updating NPC animation variables
		for (i = 0; i < gs->nnpcs; i++) {
			for (j = 0; j < gs->npc[i].nanimatics; j++) {
				switch (gs->npc[i].ani[j].type) {
					case 0:
						break;
					case 1:
						animatic1(&gs->npc[i].ani[j], gs->npc[i].keys);
						break;
				}
			}
		}

		for (i = 0; i < gs->room[gs->current_room]->nbackgrounds; i++) {
			if (gs->room[gs->current_room]->background[i].is_tiled == true) {
				update_background(&gs->room[gs->current_room]->background[i], gs->player->cx, gs->player->cy, gs->room[gs->current_room]->w, gs->room[gs->current_room]->h);
			}
		}
	}
}


void do_update(ALLEGRO_EVENT *event, bool *keys, bool *exit_game, bool *redraw, GameState *gs)
{
	if(event->type == ALLEGRO_EVENT_KEY_DOWN ||
		event->type == ALLEGRO_EVENT_KEY_UP  ||
		event->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		get_input(event, keys, exit_game);
	} else { // event->type == ALLEGRO_EVENT_TIMER
		update_logic(event, keys, gs);
		*redraw = true;
	}

}

#endif // UPDATE_LOGIC_H
