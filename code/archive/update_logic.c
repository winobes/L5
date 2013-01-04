
else if(event.type == ALLEGRO_EVENT_TIMER) {


	//updating player direction
	if (keys[RIGHT]) {
		player.direction += .5*player.rotation*ALLEGRO_PI;
	}

	if (keys[LEFT]) {
		player.direction -= .5*player.rotation*ALLEGRO_PI;
	}

	//updating player dy and dx based on acceleration & direction
	if (keys[UP]) {
		player.dx += player.acceleration * cos(player.direction - ALLEGRO_PI/2);
		player.dy += player.acceleration * sin(player.direction - ALLEGRO_PI/2);
	}
	//moving backwords...
	if (keys[DOWN]) {
		player.dx -= player.acceleration * cos(player.direction - ALLEGRO_PI/2);
		player.dy -= player.acceleration * sin(player.direction - ALLEGRO_PI/2);
	}

	//updating player position based on dx and dy
	player.x += player.dx;
	player.y += player.dy;

	//check for player collisions
	j = 0;

	for (i = 0; i < room[current_room].nsubjects; i++) {
		if (room[current_room].subject[i].wall && room[current_room].subject[i].exist) {

			if (player_can_collide) {
				j = collide(player, room[current_room].subject[i]);
			}

			switch (j) {
			case 1:
				player.dy = -player.dy;
				player.dx = player.dx * 9/10;
				break;
			case 2:
				player.dx = -player.dx;
				player.dy = player.dy * 9/10;
				break;
			case 3:
				player.dy = -player.dy;
				player.dx = player.dx * 9/10;
				break;
			case 4:
				player.dx = -player.dx;
				player.dy = player.dy * 9/10;
				break;
			case 5:
				player.dx = -player.dx;
				player.dy = -player.dy;
				break;
			case 6:
				player.dx = -player.dx;
				player.dy = -player.dy;
				break;
			case 7:
				player.dx = -player.dx;
				player.dy = -player.dy;
				break;
			case 8:
				player.dx = -player.dx;
				player.dy = -player.dy;
				break;
			}
			
		}
	
		if (j != 0) { //if there is a collision, don't test for more collisions. This should stop going through walls by toutching two at once and similar problems.
			break;
		}
	}

	//updating player animation variables
	animatic1(&player.animatic[1]);
	animatic1(&player.animatic[2]);



	//if the Left control is pressed, attempt to fire player weapon
	if (player.reload_timer < player.reload_time) {
		player.reload_timer++;
	}


	if (keys[LCTRL] && player.reload_timer >= player.reload_time) {
		player.reload_timer = 0;

		if (player.weapon == 1) {
			p_missile[current_p_missile].exist = true;
			p_missile[current_p_missile].sprite = al_load_bitmap("gfx/bullet1.png");
			p_missile[current_p_missile].width = 5;
			p_missile[current_p_missile].height = 5;
			p_missile[current_p_missile].health = 20;

			p_missile[current_p_missile].x = player.x + player.width/2 -2.5;
			p_missile[current_p_missile].y = player.y + player.height/2 -2.5;
			p_missile[current_p_missile].dx = player.dx + 2 *cos(player.direction - ALLEGRO_PI/2);
			p_missile[current_p_missile].dy = player.dy + 2 *sin(player.direction - ALLEGRO_PI/2);


		}

		current_p_missile++;
		if (current_p_missile >= 100) {
			current_p_missile = 0;
		}
		
	}


	

//updating player-fired missiles based on their characterisitics
	for (i = 0; i < 100; i++) {
		if(p_missile[i].exist) {

			//checking for collisions
			for (j = 0; j < room[current_room].nsubjects; j++) {
				//k = collide(p_missile[i], room[current_room].subject[j]);
				if (collide(p_missile[i], room[current_room].subject[j]) != 0) {
					// if it is a wall or an enemy, the collision results in the missile disappearing
					if (room[current_room].subject[j].enemy || room[current_room].subject[j].wall) {
						p_missile[i].exist = false;
					}

					//if it is an enemy, do damage (missile damage is stored in struct health)
					if (room[current_room].subject[j].enemy) {
						room[current_room].subject[j].health -= p_missile[i].health;
					}
				}
			}
			
			//moving the missiles
			if (player.weapon == 1) {
				p_missile[i].x += p_missile[i].dx;			
				p_missile[i].y += p_missile[i].dy;		
			}



		}
	}


	for (i = 0; i < room[current_room].nsubjects; i++) {
		if (room[current_room].subject[i].enemy && room[current_room].subject[i].health <= 0) {
			room[current_room].subject[i].exist = false;
		}
	}
		

	
	redraw = true;

}
