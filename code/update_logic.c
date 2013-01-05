
else if(event.type == ALLEGRO_EVENT_TIMER) {


	//updating player direction
	if (keys[RIGHT]) {
		player->d += .5*player->dd*ALLEGRO_PI;
		
		if(!keys[UP]) {
			player->dx += .25*player->ddxy * cos(player->d - ALLEGRO_PI/2);
			player->dy += .25*player->ddxy * sin(player->d - ALLEGRO_PI/2);
		}

/*		if(!keys[LEFT]) {
			player->cx += (-cos(player->d) - -cos(player->d - .5*player->dd*ALLEGRO_PI)) * player->w;
			player->cy += (-sin(player->d) - -sin(player->d - .5*player->dd*ALLEGRO_PI)) * player->w;

		}*/
	}

	if (keys[LEFT]) {
		player->d -= .5*player->dd*ALLEGRO_PI;
		
		if(!keys[UP]) {
			player->dx += .25*player->ddxy * cos(player->d - ALLEGRO_PI/2);
			player->dy += .25*player->ddxy * sin(player->d - ALLEGRO_PI/2);
		}
	
/*		if(!keys[RIGHT]) {
			player->cx += (-cos(player->d) - -cos(player->d - .5*player->dd*ALLEGRO_PI)) * player->w;
			player->cy += (-sin(player->d) - -sin(player->d - .5*player->dd*ALLEGRO_PI)) * player->w;
		}*/

	}


	if (player->d > 2*ALLEGRO_PI) {
		player->d -= 2*ALLEGRO_PI;
	}

	else if (player->d < 0) {
		player->d += 2*ALLEGRO_PI;
	}

	//updating player dy and dx based on acceleration & direction
	if (keys[UP]) {
		player->dx += player->ddxy * cos(player->d - ALLEGRO_PI/2);
		player->dy += player->ddxy * sin(player->d - ALLEGRO_PI/2);
	}
	//moving backwords...
	if (keys[DOWN]) {
		player->dx -= player->ddxy * cos(player->d - ALLEGRO_PI/2);
		player->dy -= player->ddxy * sin(player->d - ALLEGRO_PI/2);
	}

	//updating player position based on dx and dy
	player->cx += player->dx;
	player->cy += player->dy;

	//recalculating the player vertices
	calculate_verts_ship(player->shape, &player->ext, player->cx, player->cy, player->w, player->h, player->d);



	//updating NPC AI & Input
	for (i = 0; i < nnpcs; i++) {
		switch (npc[i].ai) {
			case 0:
				break;
			case 1:
				ai1(&npc[i], player);

				break;
		}



		//updating NPC direction
		if (npc[i].keys[RIGHT]) {
			npc[i].d += .5*npc[i].dd*ALLEGRO_PI;
		}

		if (npc[i].keys[LEFT]) {
			npc[i].d -= .5*npc[i].dd*ALLEGRO_PI;
		}

		if (npc[i].d > 2*ALLEGRO_PI) {
			npc[i].d -= 2*ALLEGRO_PI;
		}

		if (npc[i].d < 0) {
			npc[i].d += 2*ALLEGRO_PI;
		}

		//updating NPC dy and dx based on acceleration & direction
		if (npc[i].keys[UP]) {
			npc[i].dx += npc[i].ddxy * cos(npc[i].d - ALLEGRO_PI/2);
			npc[i].dy += npc[i].ddxy * sin(npc[i].d - ALLEGRO_PI/2);
		}
		//moving backwords...
		if (npc[i].keys[DOWN]) {
			npc[i].dx -= npc[i].ddxy * cos(npc[i].d - ALLEGRO_PI/2);
			npc[i].dy -= npc[i].ddxy * sin(npc[i].d - ALLEGRO_PI/2);
		}

		calculate_speed(npc[i].dx, npc[i].dy, &npc[i].s);

		//updating NPC position based on dx and dy
		npc[i].cx += npc[i].dx;
		npc[i].cy += npc[i].dy;

		//recalculating the NPC vertices
		calculate_verts_ship(npc[i].shape, &npc[i].ext, npc[i].cx, npc[i].cy, npc[i].w, npc[i].h, npc[i].d);

	}





	//check for player collisions with walls


	player->hit_wall = -1;
	for (i = 0; i < room[current_room]->nwalls; i++) {
		if (room[current_room]->wall[i]->exists) {

			if (collide(player->ext, room[current_room]->wall[i]->ext, penetration_vector, &penetration_scalar)) {

				player->hit_wall = i;
			
				if (room[current_room]->wall[i]->solid) {
					player->cx += penetration_vector[0] * penetration_scalar;
					player->cy += penetration_vector[1] * penetration_scalar;
			
					reflect(&player->dx, &player->dy, penetration_vector);

				}

			}

			
		}
	}

	//check for player collisions with NPCs



	for (i = 0; i < nnpcs; i++) {
		if (npc[i].exists && npc[i].room == current_room) {

			if (collide(player->ext, npc[i].ext, penetration_vector, &penetration_scalar)) {


			
				if (npc[i].solid) {

					//separating by the projection vector so that they are no longer colliding
					player->cx += penetration_vector[0] * penetration_scalar/2;
					player->cy += penetration_vector[1] * penetration_scalar/2;
			
					npc[i].cx += -penetration_vector[0] * penetration_scalar/2;
					npc[i].cy += -penetration_vector[1] * penetration_scalar/2;

					bounce(player->m, npc[i].m, .9, player->cx, player->cy, npc[i].cx, npc[i].cy, &player->dx, &player->dy, &npc[i].dx, &npc[i].dy);
						
					calculate_speed(player->dx, player->dy, &player->s);
					calculate_speed(npc[i].dx, npc[i].dy, &npc[i].s);
					

				}

			}

			
		}
	}








	//check for NPC collisions with walls


	for (i = 0; i < nnpcs; i++) {
		for (j = 0; j < room[npc[i].room]->nwalls; j++) {
			if (room[npc[i].room]->wall[j]->exists) {

				if (collide(npc[i].ext, room[npc[i].room]->wall[j]->ext, penetration_vector, &penetration_scalar)) {
			
					if (room[npc[i].room]->wall[j]->solid) {
						npc[i].cx += penetration_vector[0] * penetration_scalar;
						npc[i].cy += penetration_vector[1] * penetration_scalar;
			
						reflect(&npc[i].dx, &npc[i].dy, penetration_vector);

					}

				}

			
			}
		}
	}

	//updating player bullett position

	if(player->weapon.reload_timer < player->weapon.reload_time) {
		player->weapon.reload_timer++;
	}

	if (keys[player->weapon.key] && player->weapon.reload_timer == player->weapon.reload_time) {
	
		player->weapon.reload_timer = 0;

		player->weapon.exists[player->weapon.current] = true;

		player->weapon.d[player->weapon.current] = player->d;

		player->weapon.x[player->weapon.current] = player->cx + 0;
		player->weapon.y[player->weapon.current] = player->cy + 0;
		
		player->weapon.dx[player->weapon.current] = player->dx + 3 * cos(player->d - ALLEGRO_PI/2);
		player->weapon.dy[player->weapon.current] = player->dy + 3 * sin(player->d - ALLEGRO_PI/2);
		


		player->weapon.current ++;
		if (player->weapon.current == player->weapon.nactive) {
			player->weapon.current = 0;
		}
	}
		

//checking for bullet collision with NPCs & walls
for (j = 0; j < player->weapon.nactive; j++) {
	
	if(player->weapon.exists[j]) {

		player->weapon.ext.vert[0][0] = player->weapon.x[j];
		player->weapon.ext.vert[0][1] = player->weapon.y[j];

		for (i = 0; i < room[current_room]->nwalls; i++) {
			if(room[current_room]->wall[i]->exists) {
				if(collide(player->weapon.ext, room[current_room]->wall[i]->ext, penetration_vector, &penetration_scalar)) {
					player->weapon.exists[j] = false;
					room[current_room]->wall[i]->health -= player->weapon.damage;
				}
			}
		}


		for (i = 0; i < nnpcs; i++) {
			if (npc[i].exists && npc[i].room == current_room) {

				if (collide(player->weapon.ext, npc[i].ext, penetration_vector, &penetration_scalar)) {

					player->weapon.exists[j] = false;
					npc[i].health -= player->weapon.damage;
				

				}	
			}
		}
	}
}









	for (i = 0; i < player->weapon.nactive; i++) {
		if(player->weapon.exists[i]) {
			player->weapon.x[i] += player->weapon.dx[i];
			player->weapon.y[i] += player->weapon.dy[i];
		}
	}

	//updating player animation flags

	player->aniflags[1] = true;

	if (keys[UP]) {
		player->aniflags[2] = true;
		player->aniflags[3] = true;
		player->aniflags[4] = true;
	}

	if (keys[RIGHT]) {
		player->aniflags[3] = true;
	}
	
	if (keys[LEFT]) {
		player->aniflags[4] = true;
	}

	if (keys[DOWN]) {
		player->aniflags[5] = true;
		player->aniflags[6] = true;
	}


	//updating player animation variables
	for (i = 0; i < player->nanimatics; i++) {
		switch (player->ani[i].type) {
			case 0:
				break;
			case 1:
				animatic1(&player->ani[i], player->aniflags);
				break;
		}
	}


	for (i = 0; i < player->nanimatics; i++) {
		player->aniflags[i] = false;
	}



	//updating player weapon animation variables
	for (i = 0; i < player->weapon.nactive; i++) {
		if (player->weapon.exists[i]) {
			player->weapon.timer[i] ++;
			if (player->weapon.timer[i] == player->weapon.frame_rate) {
				player->weapon.timer[i] = 0;
				if(player->weapon.source_x[i] == player->weapon.w * (player->weapon.nframes - 1)) {
					player->weapon.source_x[i] = 0;
				}	
				else {
					player->weapon.source_x[i] += player->weapon.w;
				}
			}
		}
	}			
	

	//updating NPC animation variables
	for (i = 0; i < nnpcs; i++) {
		for (j = 0; j < npc[i].nanimatics; j++) {
			switch (npc[i].ani[j].type) {
				case 0:
					break;
				case 1:
					animatic1(&npc[i].ani[j], npc[i].keys);
					break;
			}
		}
	}

	for (i = 0; i < room[current_room]->nbackgrounds; i++) {
		update_background(&room[current_room]->background[i], player->cx, player->cy, room[current_room]->w, room[current_room]->h);
	}
	
	redraw = true;

}
