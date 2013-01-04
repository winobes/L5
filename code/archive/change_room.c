if (current_room == 0) {
	
	if (!room[0].initialized) {	

		room[0].width = 2000;
		room[0].height = 1500;

		room[0].background_buffer = al_create_bitmap(room[0].width, room[0].height);
		room[0].background = al_create_bitmap (room[0].width, room[0].height);

		al_set_target_bitmap(room[0].background);
		//if we need to tile the background, do it here.
	
		al_set_target_backbuffer(display);



		room[0].nsubjects = 7;
		room[0].subject = malloc(room[0].nsubjects * sizeof(struct Subject));

		for (i = 0; i < room[0].nsubjects; i++) {
			room[0].subject[i].wall = false;
			room[0].subject[i].enemy = false; 
			room[0].subject[i].exist = true;
		}

		//initializing walls
		room[0].subject[0].x = 800;
		room[0].subject[0].y = 710;
		room[0].subject[0].width = 980;
		room[0].subject[0].height = 20;
		room[0].subject[0].sprite = al_load_bitmap("gfx/wall0.png");
		room[0].subject[0].wall = true;

	
		room[0].subject[1].x = 800;
		room[0].subject[1].y = 250;
		room[0].subject[1].width = 20;
		room[0].subject[1].height = 480;
		room[0].subject[1].sprite = al_load_bitmap("gfx/wall1.png");
		room[0].subject[1].wall = true;

		room[0].subject[2].x = 730;
		room[0].subject[2].y = 810;
		room[0].subject[2].width = 980;
		room[0].subject[2].height = 20;
		room[0].subject[2].sprite = al_load_bitmap("gfx/wall0.png");
		room[0].subject[2].wall = true;

		room[0].subject[3].x = 730;
		room[0].subject[3].y = 370;
		room[0].subject[3].width = 20;
		room[0].subject[3].height = 480;
		room[0].subject[3].sprite = al_load_bitmap("gfx/wall1.png");
		room[0].subject[3].wall = true;

		room[0].subject[4].x = 200;
		room[0].subject[4].y = 250;
		room[0].subject[4].width = 600;
		room[0].subject[4].height = 100;
		room[0].subject[4].sprite = al_load_bitmap("gfx/wall3.png");
		room[0].subject[4].wall = true;
	

		room[0].subject[5].x = 750;
		room[0].subject[5].y = 320;
		room[0].subject[5].width = 40;
		room[0].subject[5].height = 30;
		room[0].subject[5].sprite = al_load_bitmap("gfx/hole1.png");
		room[0].subject[5].wall = true;

		room[0].subject[6].x = 200;
		room[0].subject[6].y = 250;
		room[0].subject[6].width = 20;
		room[0].subject[6].height = 100;
		room[0].subject[6].sprite = al_load_bitmap("gfx/hole2.png");
		room[0].subject[6].wall = false;
		room[0].subject[6].exist = false;

		player.x = 765;
		player.y = 385;

		room [0].initialized = true;

	}
}







if (current_room == 1) {

	if (!room[1].initialized) {

		//al_destroy_bitmap(room[previous_room].background);
		//al_destroy_bitmap(room[previous_room].background_buffer);

		for (i = 0; i < room[previous_room].nsubjects; i++) {
		//	al_destroy_bitmap(room[previous_room].subject[i].sprite);

		}

		room[1].width = 620;
		room[1].height = 120;

		ALLEGRO_BITMAP *background1 = al_load_bitmap("gfx/crate_floor1.png");
		ALLEGRO_BITMAP *background2 = al_load_bitmap("gfx/crate_floor2.png");
		ALLEGRO_BITMAP *background3 = al_load_bitmap("gfx/crate_floor3.png");
	
		room[1].background_buffer = al_create_bitmap(room[1].width, room[1].height);
		room[1].background = al_create_bitmap (room[1].width, room[1].height);

		al_set_target_bitmap(room[1].background);
		//if we need to tile the background, do it here.
		for (i = 0; i < 4; i++) {
			if (i == 0) {k = 0;}
			if (i == 1) {k = 1;}
			if (i == 2) {k = 0;}
			if (i == 3) {k = 1;}
			for (j = 0; j < 24; j++) {
				if (k == 0) {
					k = 1;
					al_draw_bitmap(background1, 10+j*25, 10+i*25 ,0);
				}
				else if (k == 1) {
					k = 2;
					al_draw_bitmap(background3, 10+j*25, 10+i*25,0);
				}
				else {
					k = 0;
					al_draw_bitmap(background2, 10+j*25,10+i*25 ,0);
				}
			
			}
		}
		al_set_target_backbuffer(display);
		al_destroy_bitmap(background1);
		al_destroy_bitmap(background2);
		al_destroy_bitmap(background3);

		room[1].nsubjects = 4 ;
		room[1].subject = malloc(room[1].nsubjects * sizeof(struct Subject));

		for (i = 0; i < room[1].nsubjects; i++) {
			room[1].subject[i].wall = false;
			room[1].subject[i].enemy = false;
			room[1].subject[i].exist = true;
 
		}


		room[1].subject[0].x = 0;
		room[1].subject[0].y = 0;
		room[1].subject[0].width = 620;
		room[1].subject[0].height = 10;
		room[1].subject[0].sprite = al_load_bitmap("gfx/wall4.png");
		room[1].subject[0].wall = true;

		room[1].subject[1].x = 610;
		room[1].subject[1].y = 10;
		room[1].subject[1].width = 10;
		room[1].subject[1].height = 100;
		room[1].subject[1].sprite = al_load_bitmap("gfx/wall5.png");
		room[1].subject[1].wall = true;

		room[1].subject[2].x = 0;
		room[1].subject[2].y = 110;
		room[1].subject[2].width = 620;
		room[1].subject[2].height = 10;
		room[1].subject[2].sprite = al_load_bitmap("gfx/wall4.png");
		room[1].subject[2].wall = true;

		room[1].subject[3].x = 0;
		room[1].subject[3].y = 10;
		room[1].subject[3].width = 10;
		room[1].subject[3].height = 100;
		room[1].subject[3].sprite = al_load_bitmap("gfx/wall5.png");
		room[1].subject[3].wall = true;
		room[1].subject[3].enemy = true;
		room[1].subject[3].health = 100;
		
		room[1].initialized = true;
	
	}

}



	
