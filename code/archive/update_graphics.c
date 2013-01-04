if(redraw && al_is_event_queue_empty(event_queue)) {
			
	redraw = false;

	al_clear_to_color(al_map_rgb(0,0,0));

	//for drawing things that move independently of the player
	al_set_target_bitmap(room[current_room].background_buffer);

	al_clear_to_color(al_map_rgb(0,0,0));

	//drawing the background to the backgorund buffer
	al_draw_bitmap(room[current_room].background, 0, 0, 0);

	//drawing player-fired missiles
	for (i = 0; i < 100; i++) {
		if (p_missile[i].exist) {
			al_draw_bitmap(p_missile[i].sprite, p_missile[i].x, p_missile[i].y, 0);
		}
	}

	//drawing the walls & enemies 
	for (i = 0; i < room[current_room].nsubjects; i++) {
		if (room[current_room].subject[i].exist) {
			al_draw_bitmap(room[current_room].subject[i].sprite, room[current_room].subject[i].x, room[current_room].subject[i].y, 0);
		}
	}

	
	al_set_target_backbuffer(display);

	//drawing visible portion of the background buffer
	al_draw_bitmap_region(room[current_room].background_buffer, player.x - width/2 + player.width/2, player.y - height/2 + player.height/2, width, height, 0,0,0);

	//drawing animatics to the player's sprite
	al_set_target_bitmap(player.sprite);
	al_clear_to_color(al_map_rgba(0,0,0,0));

	for (i = 0; i < 3; i++) {
		if (player.animatic[i].draw) {
			al_draw_tinted_scaled_rotated_bitmap_region(
                    player.spritesheet,
				    player.animatic[i].source_x,
				    player.animatic[i].source_y,
					player.animatic[i].width,
					player.animatic[i].height,
					player.animatic[i].tint,
					player.animatic[i].pivot_x,
					player.animatic[i].pivot_y,
					player.animatic[i].destination_x,
					player.animatic[i].destination_y,
					player.animatic[i].scale_x,
					player.animatic[i].scale_y,
					0,0);
			}
		}

	
	al_set_target_backbuffer(display);

	//drawing the player to the display
	al_draw_scaled_rotated_bitmap(
	    player.sprite,
		player.width/2, player.height/2, //center x,y
		width/2, height/2, // destination of point center x,y
		1, 1, //x scale, y scale
		player.direction, // angle		
	    0 //flags
	);

	//words on sreen for troubleshooting, etc.
	al_draw_textf(font10, al_map_rgb(83, 207, 46), width, 4*12, ALLEGRO_ALIGN_RIGHT,"%f", player.direction);
	al_draw_textf(font10, al_map_rgb(83, 207, 46), width, 5*12, ALLEGRO_ALIGN_RIGHT,"%f", player.y);



	al_flip_display();

}
