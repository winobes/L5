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


void copy_bullet (Bullet source, Bullet* dest) {
/*a "deep copy" of one bullet struct to another. Used to initialize fired bullets from the template in the Weapon struct*/
    int i, j;    

    dest->pos.cx = source.pos.cx;
    dest->pos.cy = source.pos.cy;
    dest->pos.cd = source.pos.cd;
 
    dest->mot.dx = source.mot.dx;
    dest->mot.dy = source.mot.dy;
    dest->mot.spd = source.mot.spd;
    dest->mot.dd = source.mot.dd;
    dest->mot.forward_speed = source.mot.forward_speed;
    dest->mot.turn_speed = source.mot.turn_speed;
    dest->mot.side_speed = source.mot.side_speed;

    dest->ext.nverts = source.ext.nverts;
    dest->ext.vert = malloc(dest->ext.nverts * sizeof (float*));//TODO FREE
    dest->ext.x = malloc(dest->ext.nverts * sizeof (float));//TODO FREE
    dest->ext.y = malloc(dest->ext.nverts * sizeof (float));//TODO FREE
    for (i = 0; i < dest->ext.nverts; i++) {
        dest->ext.vert[i] = malloc(2 * sizeof(float));//TODO FREE
        dest->ext.x[i] = source.ext.x[i];
        dest->ext.y[i] = source.ext.y[i];
    }

    calculate_verts(&dest->ext, dest->pos.cx, dest->pos.cy, dest->pos.cd);


    dest->gfx_w = source.gfx_w;
    dest->gfx_h = source.gfx_h;

    dest->spritesheet = al_clone_bitmap(source.spritesheet);
    dest->sprite = al_create_bitmap(dest->gfx_w, dest->gfx_h);

    dest->nanimatics = source.nanimatics;
    dest->ani = malloc(dest->nanimatics * sizeof(Animatic)); //TODO FREE
    dest->ani_func = malloc(dest->nanimatics * sizeof (void (*)(Animatic*, int))); //TODO FREE
    for (i = 0; i < dest->nanimatics; i++) {
        dest->ani[i].source_x = source.ani[i].source_x;
        dest->ani[i].source_y = source.ani[i].source_y;
        dest->ani[i].destination_x = source.ani[i].destination_x;
        dest->ani[i].destination_y = source.ani[i].destination_y;
        dest->ani[i].frame = source.ani[i].frame;
        dest->ani[i].w = source.ani[i].w;
        dest->ani[i].h = source.ani[i].h;
        dest->ani[i].scale_x = source.ani[i].scale_x;
        dest->ani[i].scale_y = source.ani[i].scale_y;
        dest->ani[i].state = source.ani[i].state;
        dest->ani[i].tint = source.ani[i].tint;
        dest->ani[i].pivot_x = source.ani[i].pivot_x;
        dest->ani[i].pivot_y = source.ani[i].pivot_y;
        dest->ani[i].flag = source.ani[i].flag;
        dest->ani[i].is_running = source.ani[i].is_running;
        dest->ani[i].has_run = source.ani[i].has_run;
        dest->ani[i].timer = source.ani[i].timer;
        dest->ani[i].nframes = source.ani[i].nframes;
        dest->ani[i].frame_rate = source.ani[i].frame_rate;
        dest->ani_func[i] = source.ani_func[i];
    }

    dest->nmaneuvers = source.nmaneuvers;
    dest->man = malloc(dest->nmaneuvers * sizeof (Maneuver)); //TODO FREE
    dest->man_func = malloc(dest->nmaneuvers * sizeof (void (*) (Position*, Motion*, Maneuver*, int)));//TODO FREE
    for (i = 0; i < dest->nmaneuvers; i++) {
        dest->man[i].on = source.man[i].on;
        dest->man[i].has_run = source.man[i].has_run;
        dest->man[i].state = source.man[i].state;
        dest->man[i].key = source.man[i].key;
        dest->man[i].nanimatics = source.man[i].nanimatics;
        dest->man[i].animatic = malloc(dest->man[i].nanimatics * sizeof (int)); //TODO FREE
        for (j = 0; j < dest->man[i].nanimatics; j++) {
            dest->man[i].animatic[j] = source.man[i].animatic[j];
        }
    }

    dest->exist = true;
    dest->damage = source.damage;

return;
}

void run_active_maneuvers (Maneuver *man, void (**man_func) (Position*, Motion*, Maneuver*, int), int nmaneuvers, Position *pos, Motion *mot) {

    int i;
    bool check_again = true;

    for (i = 0; i < nmaneuvers; i++) {
        man[i].has_run = false;
    }


//performing the maneuver functions 
    do { 
        for (i = 0; i < nmaneuvers; i++) {
        if (man[i].on && !man[i].has_run) {
            man_func[i](pos, mot, man, i);
            man[i].has_run = true;
        }
        }
        check_again = false;
        for (i = 0; i < nmaneuvers; i++) {
            if (man[i].on && !man[i].has_run) {
        //if there are maneuvers that were turned on in the previous for loop (by other maneuvers), but haven't been run, they will trigger another loop
                check_again = true;
            }
        }
    } while (check_again);

    return;
}

void update_position(Position* pos, Motion mot) {

	// wrap orientation to the range [0,2*PI]
	if (pos->cd > 2*PI) {
		pos->cd -= 2*PI;
	} else if (pos->cd < 0) {
		pos->cd += 2*PI;
	}

	//updating player position based on dx and dy
	pos->cx += mot.dx;
	pos->cy += mot.dy;

    return;
}


void run_animatics (Animatic* ani, void (**ani_func) (Animatic*, int), int nanimatics, Maneuver *man, int nmaneuvers) {


    bool check_again = true;
    int i, k;

    // updating  animation flags
    for (i = 0; i < nanimatics; i++) {
        ani[i].flag = false;
    }
    for (i = 0; i < nmaneuvers; i++) {
    if (man[i].on) {
    for (k = 0; k < man[i].nanimatics; k++) {
        ani[man[i].animatic[k]].flag = true;
    }
    }
    }

    // performing animations
    for (i = 0; i < nanimatics; i++) {
        ani[i].has_run = false;
    }
    check_again = true;
    do { 
        for (i = 0; i < nanimatics; i++) {
        if ((ani[i].flag || ani[i].is_running) && !ani[i].has_run) {

            ani_func[i](ani, i);
            ani[i].has_run = true;
        }
        }
        check_again = false;
        for (i = 0; i < nanimatics; i++) {
            if (ani[i].flag && !ani[i].has_run) {
        //if there are animatics that were turned on in the previous for loop (by other animatics), but haven't been run, they will trigger another loop
                check_again = true;
            }
        }
    } while (check_again);

    return;
}

void update_logic(ALLEGRO_EVENT *event, bool *keys, GameState *gs)
{

	int i, j;
    float temp;

    //bool check_again = true;

	float penetration_scalar;
	float penetration_vector[2];

	if(event->type == ALLEGRO_EVENT_TIMER) {

   
    //Updating player logic 
        //turning player maneuvers on and off
        for ( i = 0; i < gs->player->nmaneuvers; i++) {
            //passing key input to maneuvers
            if (gs->player->man[i].state == 0) {
            //turn the maneuver off if it has reached the end of a cycle. Reset the maneuver state when it is turned off.
               gs->player->man[i].on = false;
               gs->player->man[i].state = 1;
            }
            //get input from keys if it is player-controled
            if (keys != NULL) {
            if (keys[gs->player->man[i].key]) {
            // if the key is pressed, turn the maneuver on
                gs->player->man[i].on = true;
            }
            }
        }

        run_active_maneuvers(gs->player->man, gs->player->man_func, gs->player->nmaneuvers, &(gs->player->pos), &(gs->player->mot));

        update_position(&(gs->player->pos), gs->player->mot);

		//recalculating the player vertices
		calculate_verts(&gs->player->ext, gs->player->pos.cx, gs->player->pos.cy, gs->player->pos.cd);



        //updating NPC logic
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
            run_active_maneuvers(gs->npc[i].man, gs->npc[i].man_func, gs->npc[i].nmaneuvers, &(gs->npc[i].pos), &(gs->npc[i].mot));

            update_position(&gs->npc[i].pos, gs->npc[i].mot);

			//recalculating the NPC vertices
			calculate_verts(&gs->npc[i].ext, gs->npc[i].pos.cx, gs->npc[i].pos.cy, gs->npc[i].pos.cd);
		}
           
                
    //updating player bullets
        //creating new bullets when the weapon fires
        for (i = 0; i < gs->player->nweapons; i++) {

            if (gs->player->weapon[i].timer > 0) {
                gs->player->weapon[i].timer--;
            }
        
            if (keys[gs->player->weapon[i].key]) {
                gs->player->weapon[i].fire = true; //pressing the key pulls the triger
            }  else { 
                gs->player->weapon[i].fire = false;
            }

            if (gs->player->weapon[i].fire && (gs->player->weapon[i].timer <= 0)) { //if the triger is pulled and the reload time is complete, the weapon fires
                gs->player->weapon[i].timer = gs->player->weapon[i].reload_time;
                copy_bullet(gs->player->weapon[i].bullet_temp, &(gs->player_bullet[gs->current_pb]));
                gs->player_bullet[gs->current_pb].room = gs->current_room; 
                temp = gs->player_bullet[gs->current_pb].pos.cx;
                gs->player_bullet[gs->current_pb].pos.cx = (gs->player_bullet[gs->current_pb].pos.cx * cos(gs->player->pos.cd) - gs->player_bullet[gs->current_pb].pos.cy * sin(gs->player->pos.cd)) + gs->player->pos.cx;
                gs->player_bullet[gs->current_pb].pos.cy = (temp * sin(gs->player->pos.cd) + gs->player_bullet[gs->current_pb].pos.cy * cos(gs->player->pos.cd)) + gs->player->pos.cy;
                gs->player_bullet[gs->current_pb].mot.dx += gs->player->mot.dx + gs->player->weapon[i].initial_velocity * cos(gs->player->pos.cd- PI/2);
                gs->player_bullet[gs->current_pb].mot.dy += gs->player->mot.dy + gs->player->weapon[i].initial_velocity * sin(gs->player->pos.cd- PI/2);

                gs->player_bullet[gs->current_pb].exist = true;

                if (gs->current_pb < gs->n_player_bullets) { 
                    gs->current_pb++;
                } 
                if (gs->current_pb >= gs->n_player_bullets) {
                    gs->current_pb = 0;
                }
               
            }
        }
        
        for (i = 0; i < gs->n_player_bullets; i++) {
        if (gs->player_bullet[i].exist) {
            run_active_maneuvers(gs->player_bullet[i].man, gs->player_bullet[i].man_func, gs->player_bullet[i].nmaneuvers, &(gs->player_bullet[i].pos), &(gs->player_bullet[i].mot));

            update_position(&gs->player_bullet[i].pos, gs->player_bullet[i].mot);

			    //recalculating the bullet vertices
		    calculate_verts(&gs->player_bullet[i].ext, gs->player_bullet[i].pos.cx, gs->player_bullet[i].pos.cy, gs->player_bullet[i].pos.cd);
	    }
        }

   
	    //check for player collisions with walls
	    gs->player->hit_wall = -1;
	    for (i = 0; i < gs->room[gs->current_room]->nwalls; i++) {
		    if (gs->room[gs->current_room]->wall[i]->exist) {

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
		if (gs->npc[i].exist && gs->npc[i].room == gs->current_room) {
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
		if (gs->room[gs->npc[i].room]->wall[j]->exist) {
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


//bullet collisions with npcs
        for ( i = 0; i < gs->n_player_bullets; i++) {
        for (j = 0; j < gs->nnpcs; j++) {
        if (gs->player_bullet[i].exist && gs->npc[j].exist && gs->player_bullet[i].room == gs->npc[j].room) {
        if (collide(gs->player_bullet[i].ext, gs->npc[j].ext, penetration_vector, &penetration_scalar)) {
            gs->player_bullet[i].exist = false;
        }
        }
        }
        }
//bullet collisions with walls
        for ( i = 0; i < gs->n_player_bullets; i++) {
        for (j = 0; j < gs->room[gs->current_room]->nwalls; j++) {
        if (gs->player_bullet[i].exist && gs->room[gs->current_room]->wall[i]->exist) {
        if (collide(gs->player_bullet[i].ext, gs->room[gs->current_room]->wall[j]->ext, penetration_vector, &penetration_scalar)) {
            gs->player_bullet[i].exist = false;
        }
        }
        }
        }

/*
        //check for Player Bullet collisions with NPCs
        for (i = 0; i < gs->n_player_bullets; i++) {
        if (gs->player_bullet[i].exist) {
        for (j = 0; j < gs->nnpcs; j++) {
        if (gs->npc[j].exist) {
        if (gs->player_bullet[i].room == gs->npc[j].room) {
            if (collide(gs->player_bullet[i].ext, gs->npc[j].ext, penetration_vector, &penetration_scalar)) {
                gs->npc[j].health -= gs->player_bullet[i].damage;
                gs->player_bullet[i].exist = false;
            }
        }
        }
        }
        }
        }*/   

    //updating player animatics
        run_animatics(gs->player->ani, gs->player->ani_func, gs->player->nanimatics, gs->player->man, gs->player->nmaneuvers);

    //updating NPC animatics
		for (i = 0; i < gs->nnpcs; i++) {
            run_animatics(gs->npc[i].ani, gs->npc[i].ani_func, gs->npc[i].nanimatics, gs->npc[i].man, gs->npc[i].nmaneuvers);
        }

    //updating bullet animatics
        for (i = 0; i < gs->n_player_bullets; i++) {
        if (gs->player_bullet[i].exist == true) {
            run_animatics(gs->player_bullet[i].ani, gs->player_bullet[i].ani_func, gs->player_bullet[i].nanimatics, gs->player_bullet[i].man, gs->player_bullet[i].nmaneuvers);
        }
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
