if(redraw && al_is_event_queue_empty(event_queue)) {
			
	redraw = false;

	al_clear_to_color(al_map_rgb(10,10,10));

	//for drawing things that move independently of the player


	
//drawing the background tiles to the screen (there are maximum of four tiles for each layer)
	for (i = 0; i < room[current_room]->nbackgrounds; i++) {

		al_draw_bitmap(room[current_room]->background[i].background_image, -room[current_room]->background[i].parallax_rate*(player->cx-room[0]->w/2) + room[current_room]->background[i].parallax_x1*width, -room[current_room]->background[i].parallax_rate*(player->cy-room[0]->h/2) + room[current_room]->background[i].parallax_y1*height , 0);

		al_draw_bitmap(room[current_room]->background[i].background_image, -room[current_room]->background[i].parallax_rate*(player->cx-room[0]->w/2) + room[current_room]->background[i].parallax_x2*width, -room[current_room]->background[i].parallax_rate*(player->cy-room[0]->h/2) + room[current_room]->background[i].parallax_y2*height , 0);

		al_draw_bitmap(room[current_room]->background[i].background_image, -room[current_room]->background[i].parallax_rate*(player->cx-room[0]->w/2) + room[current_room]->background[i].parallax_x1*width, -room[current_room]->background[i].parallax_rate*(player->cy-room[0]->h/2) + room[current_room]->background[i].parallax_y2*height , 0);

		al_draw_bitmap(room[current_room]->background[i].background_image, -room[current_room]->background[i].parallax_rate*(player->cx-room[0]->w/2) + room[current_room]->background[i].parallax_x2*width, -room[current_room]->background[i].parallax_rate*(player->cy-room[0]->h/2) + room[current_room]->background[i].parallax_y1*height , 0);

}

	

	for (i = 0; i < nnpcs; i++) {

		if (npc[i].room == current_room) {

			al_set_target_bitmap(npc[i].sprite);
			al_clear_to_color(al_map_rgba(0,0,0,0));
			//drawing the NPC animatics to its spritesheet
			for (j = 0; j < npc[i].nanimatics; j++) {
				if (npc[i].ani[j].draw) {
					al_draw_tinted_scaled_rotated_bitmap_region(
				            npc[i].spritesheet,
							npc[i].ani[j].source_x,
							npc[i].ani[j].source_y,
							npc[i].ani[j].w,
							npc[i].ani[j].h,
							npc[i].ani[j].tint,
							npc[i].ani[j].pivot_x,
							npc[i].ani[j].pivot_y,
							npc[i].ani[j].destination_x,
							npc[i].ani[j].destination_y,
							npc[i].ani[j].scale_x,
							npc[i].ani[j].scale_y,
							0,0);
					}
				}

			al_set_target_backbuffer(display);

			//drawing the npc[i] to the display
			al_draw_scaled_rotated_bitmap(
				npc[i].sprite,
				npc[i].w/2, npc[i].h/2, //center x,y
				npc[i].cx - (player->cx - width/2), 
				npc[i].cy - (player->cy - height/2), // destination of point center x,y
				1, 1, //x scale, y scale
				npc[i].d, // angle		
				0 //flags
			);
		}

	}
	
	//drawing the walls in the current room

	for (i = 0; i < room[current_room]->nwalls; i++) {
		//all of the walls in the current room
		// TODO check line break does not affect logic
		if (room[current_room]->wall[i]->exists &&
			room[current_room]->wall[i]->ext.vert[0][0] - player->cx < width/2 +
			  room[current_room]->wall[i]->h + room[current_room]->wall[i]->w &&
			room[current_room]->wall[i]->ext.vert[0][1] - player->cy < height/2 +
			  room[current_room]->wall[i]->w + room[current_room]->wall[i]->h) {
		//only draw if it exists and is close enough to the player that it might possibly be in view of the screen
			al_draw_scaled_rotated_bitmap(
				room[current_room]->wall[i]->sprite,
				0, //center x,y
				0,
				room[current_room]->wall[i]->ext.vert[0][0] - (player->cx - width/2),
				room[current_room]->wall[i]->ext.vert[0][1] - (player->cy - height/2), //destination of point center x,y
				1, 1, //x scale, y scale
				room[current_room]->wall[i]->d, // angle		
				0 //flags
			);
		}
	}



	for (i = 0; i < player->weapon.nactive; i++) {
		if (player->weapon.exists[i]) {
			al_draw_tinted_scaled_rotated_bitmap_region(
			        player->weapon.spritesheet,
					player->weapon.source_x[i],
					0,
					player->weapon.w,
					player->weapon.h,
					al_map_rgba_f(1,1,1,1),
					player->weapon.w/2,
					player->weapon.h/2,
					player->weapon.x[i] - (player->cx - width/2),
					player->weapon.y[i] - (player->cy - height/2),
					1,
					1,
					0,0);
		}
	}




for (j = 0; j < 4; j++) {
	//al_draw_pixel(room[0]->wall[1]->ext.vert[j][0], room[0]->wall[1]->ext.vert[j][1], al_map_rgb(83,207,46));
}


	//drawing animatics to the player's sprite
	al_set_target_bitmap(player->sprite);
	al_clear_to_color(al_map_rgba(0,0,0,0));


	for (i = 0; i < player->nanimatics; i++) {
		if (player->ani[i].draw) {
			al_draw_tinted_scaled_rotated_bitmap_region(
                    player->spritesheet,
				    player->ani[i].source_x,
				    player->ani[i].source_y,
					player->ani[i].w,
					player->ani[i].h,
					player->ani[i].tint,
					player->ani[i].pivot_x,
					player->ani[i].pivot_y,
					player->ani[i].destination_x,
					player->ani[i].destination_y,
					player->ani[i].scale_x,
					player->ani[i].scale_y,
					0,0);
			}
		}

	
	al_set_target_backbuffer(display);

	//drawing the player to the display
	al_draw_scaled_rotated_bitmap(
	    player->sprite,
		player->gfx_w/2, player->gfx_h/2, //center x,y
		width/2, height/2, // destination of point center x,y
		1, 1, //x scale, y scale
		player->d, // angle		
	    0 //flags
	);


	//words on sreen for troubleshooting, etc.
	al_draw_textf(font10, al_map_rgb(83, 207, 46), width, 4*12, ALLEGRO_ALIGN_RIGHT,"y = %f", player->cy);
	al_draw_textf(font10, al_map_rgb(83, 207, 46), width, 5*12, ALLEGRO_ALIGN_RIGHT,"x = %f", player->cx);

	/*al_draw_textf(font10, al_map_rgb(83, 207, 46), width, 7*12, ALLEGRO_ALIGN_RIGHT,"health2 %f", npc[1].health);

al_draw_textf(font10, al_map_rgb(83, 207, 46), width, 8*12, ALLEGRO_ALIGN_RIGHT,"speed = %f", player->s);
*/


if (player->ani[2].draw) {
	al_draw_textf(font10, al_map_rgb(83, 207, 46), width, 9*12, ALLEGRO_ALIGN_RIGHT,"draw");
}

	al_flip_display();

}
