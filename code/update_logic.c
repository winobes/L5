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
				keys[KEYA] = true;
				break;
			case ALLEGRO_KEY_W:
				keys[KEYW] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[KEYS] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[KEYD] = true;
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
				keys[KEYA] = false;
				break;
			case ALLEGRO_KEY_W:
				keys[KEYW] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[KEYS] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[KEYD] = false;
				break;
		}
	} else if(event->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		*exit_game = true;
	}
}


void update_logic(ALLEGRO_EVENT *event, bool *keys, GameState *gs)
{

	int i, j, k;

    bool check_again = true;

	float penetration_scalar;
	float penetration_vector[2];

	if(event->type == ALLEGRO_EVENT_TIMER) {

        // updating player input & motion

        for ( i = 0; i < gs->player->nmaneuvers; i++) {

            //passing key input to maneuvers
            if (gs->player->man[i].state == 0) {
            //turn the maneuver off if it has reached the end of a cycle. Reset the maneuver state when it is turned off.
               gs->player->man[i].on = false;
               gs->player->man[i].state = 1;
            }
            if (keys[gs->player->man[i].key]) {
            // if the key is pressed, turn the maneuver on
                gs->player->man[i].on = true;
            }
        }


        for (i = 0; i < gs->player->nmaneuvers; i++) {
            gs->player->man[i].has_run = false;
        }


//performing the maneuver functions 
        do { 
            for (i = 0; i < gs->player->nmaneuvers; i++) {
            if (gs->player->man[i].on && !gs->player->man[i].has_run) {
                gs->player->man_func[i](&gs->player->pos, &gs->player->mot, gs->player->man, i);
                gs->player->man[i].has_run = true;
            }
            }
            check_again = false;
            for (i = 0; i < gs->player->nmaneuvers; i++) {
                if (gs->player->man[i].on && !gs->player->man[i].has_run) {
            //if there are maneuvers that were turned on in the previous for loop (by other maneuvers), but haven't been run, they will trigger another loop
                    check_again = true;
                }
            }
        } while (check_again);
        

		// wrap player orientation to the range [0,2*PI]
		if (gs->player->pos.cd > 2*PI) {
			gs->player->pos.cd -= 2*PI;
		} else if (gs->player->pos.cd < 0) {
			gs->player->pos.cd += 2*PI;
		}

		//updating player position based on dx and dy
		gs->player->pos.cx += gs->player->mot.dx;
		gs->player->pos.cy += gs->player->mot.dy;

		//recalculating the player vertices
		calculate_verts_ship(&gs->player->ext, gs->player->pos.cx, gs->player->pos.cy, gs->player->pos.cd);





		//updating NPC AI & motion

		for (i = 0; i < gs->nnpcs; i++) {

          for ( j = 0; j < gs->npc[i].nmaneuvers; j++) {

            if (gs->npc[i].man[j].state == 0) {
            //turn the maneuver off if it has reached the end of a cycle. Reset the maneuver state.
               gs->npc[i].man[j].on = false;
               gs->npc[i].man[j].state = 1;
                }
            }

            // ai functions have the power to turn maneuvers on (like keys for the player)
			switch (gs->npc[i].ai) {
			case 0:
				break;
			case 1:
				ai1(&gs->npc[i], gs->player->ext, gs->current_room);
				break;
			}


            //performing the active maneuver functions
            for (j = 0; j < gs->npc[i].nmaneuvers; j++) {
                if (gs->npc[i].man[j].on) {    
                    gs->npc[i].man_func[j](&gs->npc[i].pos, &gs->npc[i].mot, gs->npc[i].man, j);
                }
            }

		    // wrap npc orientation to the range [0,2*PI]
		    if (gs->npc[i].pos.cd > 2*PI) {
			    gs->npc[i].pos.cd -= 2*PI;
		    } else if (gs->npc[i].pos.cd < 0) {
			    gs->npc[i].pos.cd += 2*PI;
		    }

			//updating NPC position based on dx and dy
			gs->npc[i].pos.cx += gs->npc[i].mot.dx;
			gs->npc[i].pos.cy += gs->npc[i].mot.dy;

			//recalculating the NPC vertices
			calculate_verts_ship(&gs->npc[i].ext, gs->npc[i].pos.cx, gs->npc[i].pos.cy, gs->npc[i].pos.cd);
		}


		//check for player collisions with walls
		gs->player->hit_wall = -1;
		for (i = 0; i < gs->room[gs->current_room]->nwalls; i++) {
			if (gs->room[gs->current_room]->wall[i]->exists) {

				if (collide(gs->player->ext, gs->room[gs->current_room]->wall[i]->ext, penetration_vector, &penetration_scalar)) {

					gs->player->hit_wall = i;
				
					if (gs->room[gs->current_room]->wall[i]->solid) {
						gs->player->pos.cx += penetration_vector[0] * penetration_scalar;
						gs->player->pos.cy += penetration_vector[1] * penetration_scalar;
				
						reflect(&gs->player->mot.dx, &gs->player->mot.dy, penetration_vector);
					}
				}
			}
		}

		//check for player collisions with NPCs
		for (i = 0; i < gs->nnpcs; i++) {
			if (gs->npc[i].exists && gs->npc[i].room == gs->current_room) {
				if (collide(gs->player->ext, gs->npc[i].ext, penetration_vector, &penetration_scalar)) {
					if (gs->npc[i].solid) {
						//separating by the projection vector so that they are no longer colliding
						gs->player->pos.cx += penetration_vector[0] * penetration_scalar/2;
						gs->player->pos.cy += penetration_vector[1] * penetration_scalar/2;

						gs->npc[i].pos.cx += -penetration_vector[0] * penetration_scalar/2;
						gs->npc[i].pos.cy += -penetration_vector[1] * penetration_scalar/2;
						bounce(gs->player->bouncy,
								gs->npc[i].bouncy,
								.9,
								gs->player->pos.cx,
								gs->player->pos.cy,
								gs->npc[i].pos.cx,
								gs->npc[i].pos.cy,
								&gs->player->mot.dx,
								&gs->player->mot.dy,
								&gs->npc[i].mot.dx,
								&gs->npc[i].mot.dy);
						calculate_speed(gs->player->mot.dx, gs->player->mot.dy, &gs->player->mot.spd);
						calculate_speed(gs->npc[i].mot.dx, gs->npc[i].mot.dy, &gs->npc[i].mot.spd);
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
							gs->npc[i].pos.cx += penetration_vector[0] * penetration_scalar;
							gs->npc[i].pos.cy += penetration_vector[1] * penetration_scalar;
				
							reflect(&gs->npc[i].mot.dx, &gs->npc[i].mot.dy, penetration_vector);
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
			gs->player->weapon.d[gs->player->weapon.current] = gs->player->pos.cd;
		
			gs->player->weapon.x[gs->player->weapon.current] = gs->player->pos.cx + 0;
			gs->player->weapon.y[gs->player->weapon.current] = gs->player->pos.cy + 0;
		
			gs->player->weapon.dx[gs->player->weapon.current] = gs->player->mot.dx + 3 * cos(gs->player->pos.cd - PI/2);
			gs->player->weapon.dy[gs->player->weapon.current] = gs->player->mot.dy + 3 * sin(gs->player->pos.cd - PI/2);
			
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

        //updating player animation flags redux
        for (i = 0; i < gs->player->nanimatics; i++) {
            gs->player->ani[i].flag = false;
        }
        for (i = 0; i < gs->player->nmaneuvers; i++) {
        if (gs->player->man[i].on) {
        for (j = 0; j < gs->player->man[i].nanimatics; j++) {
            gs->player->ani[gs->player->man[i].animatic[j]].flag = true;
        }
        }
        }

// performing player animations

        for (i = 0; i < gs->player->nanimatics; i++) {
            gs->player->ani[i].has_run = false;
        }
        check_again = true;
        do { 
            for (i = 0; i < gs->player->nanimatics; i++) {
            if ((gs->player->ani[i].flag || gs->player->ani[i].is_running) && !gs->player->ani[i].has_run) {

                gs->player->ani_func[i](gs->player->ani, i);
                gs->player->ani[i].has_run = true;
            }
            }
            check_again = false;
            for (i = 0; i < gs->player->nanimatics; i++) {
                if (gs->player->ani[i].flag && !gs->player->ani[i].has_run) {
            //if there are animatics that were turned on in the previous for loop (by other animatics), but haven't been run, they will trigger another loop
                    check_again = true;
                }
            }
        } while (check_again);
     


/* let's get player straight first...
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
*/

		for (i = 0; i < gs->nnpcs; i++) {


            // updating NPC animation flags
            for (j = 0; j < gs->npc[i].nanimatics; j++) {
                gs->npc[i].ani[j].flag = false;
            }
            for (j = 0; j < gs->npc[i].nmaneuvers; j++) {
            if (gs->npc[i].man[j].on) {
            for (k = 0; k < gs->npc[i].man[j].nanimatics; k++) {
                gs->npc[i].ani[gs->npc[i].man[j].animatic[k]].flag = true;
            }
            }
            }
// performing NPC animations

            for (j = 0; j < gs->npc[i].nanimatics; j++) {
                gs->npc[i].ani[j].has_run = false;
            }
            check_again = true;
            do { 
                for (j = 0; j < gs->npc[i].nanimatics; j++) {
                if ((gs->npc[i].ani[j].flag || gs->npc[i].ani[j].is_running) && !gs->npc[i].ani[j].has_run) {

                    gs->npc[i].ani_func[j](gs->npc[i].ani, j);
                    gs->npc[i].ani[j].has_run = true;
                }
                }
                check_again = false;
                for (j = 0; j < gs->npc[i].nanimatics; j++) {
                    if (gs->npc[i].ani[j].flag && !gs->npc[i].ani[j].has_run) {
                //if there are animatics that were turned on in the previous for loop (by other animatics), but haven't been run, they will trigger another loop
                        check_again = true;
                    }
                }
            } while (check_again);

        }


// updating parallax background varriables
		for (i = 0; i < gs->room[gs->current_room]->nbackgrounds; i++) {
			if (gs->room[gs->current_room]->background[i].is_tiled == true) {
				update_background(&gs->room[gs->current_room]->background[i],
									gs->player->pos.cx,
									gs->player->pos.cy,
									gs->room[gs->current_room]->w,
									gs->room[gs->current_room]->h);
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
