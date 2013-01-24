#include "common_def.c"

#ifndef UPDATE_GRAPHICS_H
#define UPDATE_GRAPHICS_H

void do_graphics_update(GameState *gs, bool *redraw)
{
	if(*redraw && al_is_event_queue_empty(gs->event_queue)) {
				
		*redraw = false;

		al_clear_to_color(al_map_rgb(10,10,10));

		//for drawing things that move independently of the gs->player

		int i, j;
		//drawing the background tiles to the screen (there are maximum of four tiles for each layer)


		for (i = 0; i < gs->room[gs->current_room]->nbackgrounds; i++) {
			if (gs->room[gs->current_room]->background[i].is_tiled == true) {
				al_draw_bitmap(gs->room[gs->current_room]->background[i].background_image,
					-gs->room[gs->current_room]->background[i].parallax_rate*(gs->player->pos.cx-gs->room[0]->w/2) + gs->room[gs->current_room]->background[i].x1*width,
					-gs->room[gs->current_room]->background[i].parallax_rate*(gs->player->pos.cy-gs->room[0]->h/2) + gs->room[gs->current_room]->background[i].y1*height,
					0);

				al_draw_bitmap(gs->room[gs->current_room]->background[i].background_image,
					-gs->room[gs->current_room]->background[i].parallax_rate*(gs->player->pos.cx-gs->room[0]->w/2) + gs->room[gs->current_room]->background[i].x2*width,
					-gs->room[gs->current_room]->background[i].parallax_rate*(gs->player->pos.cy-gs->room[0]->h/2) + gs->room[gs->current_room]->background[i].y2*height,
					0);

				al_draw_bitmap(gs->room[gs->current_room]->background[i].background_image,
					-gs->room[gs->current_room]->background[i].parallax_rate*(gs->player->pos.cx-gs->room[0]->w/2) + gs->room[gs->current_room]->background[i].x1*width,
					-gs->room[gs->current_room]->background[i].parallax_rate*(gs->player->pos.cy-gs->room[0]->h/2) + gs->room[gs->current_room]->background[i].y2*height,
					0);

				al_draw_bitmap(gs->room[gs->current_room]->background[i].background_image,
					-gs->room[gs->current_room]->background[i].parallax_rate*(gs->player->pos.cx-gs->room[0]->w/2) + gs->room[gs->current_room]->background[i].x2*width,
					-gs->room[gs->current_room]->background[i].parallax_rate*(gs->player->pos.cy-gs->room[0]->h/2) + gs->room[gs->current_room]->background[i].y1*height,
					0);

			}
			
			else {
				al_draw_bitmap(gs->room[gs->current_room]->background[i].background_image,
					gs->room[gs->current_room]->background[i].x1 - gs->room[gs->current_room]->background[i].parallax_rate*(gs->player->pos.cx-gs->room[0]->w/2),
					gs->room[gs->current_room]->background[i].y1 - gs->room[gs->current_room]->background[i].parallax_rate*(gs->player->pos.cy-gs->room[0]->h/2),
					0);
			}

		}

			

		for (i = 0; i < gs->nnpcs; i++) {
			if (gs->npc[i].room == gs->current_room && gs->npc[i].exists) {
				al_set_target_bitmap(gs->npc[i].sprite);
				al_clear_to_color(al_map_rgba(0,0,0,0));
				//drawing the NPC animatics to its spritesheet
				for (j = 0; j < gs->npc[i].nanimatics; j++) {
					if (gs->npc[i].ani[j].draw) {
						al_draw_tinted_scaled_rotated_bitmap_region(
							gs->npc[i].spritesheet,
							gs->npc[i].ani[j].source_x,
							gs->npc[i].ani[j].source_y,
							gs->npc[i].ani[j].w,
							gs->npc[i].ani[j].h,
							gs->npc[i].ani[j].tint,
							gs->npc[i].ani[j].pivot_x,
							gs->npc[i].ani[j].pivot_y,
							gs->npc[i].ani[j].destination_x,
							gs->npc[i].ani[j].destination_y,
							gs->npc[i].ani[j].scale_x,
							gs->npc[i].ani[j].scale_y,
							0,0);
					}
				}
				al_set_target_backbuffer(gs->display);
				//drawing the gs->npc[i] to the display
				al_draw_scaled_rotated_bitmap(
					gs->npc[i].sprite,
					gs->npc[i].gfx_w/2, gs->npc[i].gfx_h/2, //center x,y
					gs->npc[i].pos.cx - (gs->player->pos.cx - width/2), 
					gs->npc[i].pos.cy - (gs->player->pos.cy - height/2), // destination of point center x,y
					1, 1, //x scale, y scale
					gs->npc[i].pos.cd, // angle		
					0 //flags
				);
			}
		}
		//drawing the walls in the current room
		for (i = 0; i < gs->room[gs->current_room]->nwalls; i++) {
			//all of the walls in the current room
			// TODO check line break does not affect logic
			if (gs->room[gs->current_room]->wall[i]->exists &&
				gs->room[gs->current_room]->wall[i]->ext.vert[0][0] - gs->player->pos.cx < width/2 +
					gs->room[gs->current_room]->wall[i]->h + gs->room[gs->current_room]->wall[i]->w &&
				gs->room[gs->current_room]->wall[i]->ext.vert[0][1] - gs->player->pos.cy < height/2 +
					gs->room[gs->current_room]->wall[i]->w + gs->room[gs->current_room]->wall[i]->h) {
				//only draw if it exists and is close enough to the gs->player that it might possibly be in view of the screen
				al_draw_scaled_rotated_bitmap(
					gs->room[gs->current_room]->wall[i]->sprite,
					0, //center x,y
					0,
					gs->room[gs->current_room]->wall[i]->ext.vert[0][0] - (gs->player->pos.cx - width/2),
					gs->room[gs->current_room]->wall[i]->ext.vert[0][1] - (gs->player->pos.cy - height/2), //destination of point center x,y
					1, 1, //x scale, y scale
					gs->room[gs->current_room]->wall[i]->d, // angle		
					0 //flags
				);
			}
		}



		for (i = 0; i < gs->player->weapon.nactive; i++) {
			if (gs->player->weapon.exists[i]) {
				al_draw_tinted_scaled_rotated_bitmap_region(
						gs->player->weapon.spritesheet,
						gs->player->weapon.source_x[i],
						0,
						gs->player->weapon.w,
						gs->player->weapon.h,
						al_map_rgba_f(1,1,1,1),
						gs->player->weapon.w/2,
						gs->player->weapon.h/2,
						gs->player->weapon.x[i] - (gs->player->pos.cx - width/2),
						gs->player->weapon.y[i] - (gs->player->pos.cy - height/2),
						1,
						1,
						0,0);
			}
		}


		//drawing animatics to the gs->player's sprite
		al_set_target_bitmap(gs->player->sprite);
		al_clear_to_color(al_map_rgba(0,0,0,0));

		for (i = 0; i < gs->player->nanimatics; i++) {
			if (gs->player->ani[i].draw) {
				al_draw_tinted_scaled_rotated_bitmap_region(
						gs->player->spritesheet,
						gs->player->ani[i].source_x,
						gs->player->ani[i].source_y,
						gs->player->ani[i].w,
						gs->player->ani[i].h,
						gs->player->ani[i].tint,
						gs->player->ani[i].pivot_x,
						gs->player->ani[i].pivot_y,
						gs->player->ani[i].destination_x,
						gs->player->ani[i].destination_y,
						gs->player->ani[i].scale_x,
						gs->player->ani[i].scale_y,
						0,0);
			}
		}
		
		al_set_target_backbuffer(gs->display);

		//drawing the player to the display
		al_draw_scaled_rotated_bitmap(
			gs->player->sprite,
			gs->player->gfx_w/2, gs->player->gfx_h/2, //center x,y
			width/2, height/2, // destination of point center x,y
			1, 1, //x scale, y scale
			gs->player->pos.cd, // angle		
			0 //flags
		);

		//words on sreen for troubleshooting, etc.
		al_draw_textf(gs->font10, al_map_rgb(83, 207, 46), width, 4*12, ALLEGRO_ALIGN_RIGHT,"y = %f", gs->player->pos.cy);
		al_draw_textf(gs->font10, al_map_rgb(83, 207, 46), width, 5*12, ALLEGRO_ALIGN_RIGHT,"x = %f", gs->player->pos.cx);
	al_draw_textf(gs->font10, al_map_rgb(83, 207, 46), width, 7*12, ALLEGRO_ALIGN_RIGHT,"npc[0].health = %f", gs->npc[0].health);
al_draw_textf(gs->font10, al_map_rgb(83, 207, 46), width, 8*12, ALLEGRO_ALIGN_RIGHT,"npc[1].health = %f", gs->npc[1].health);

al_draw_textf(gs->font10, al_map_rgb(83, 207, 46), width, 10*12, ALLEGRO_ALIGN_RIGHT,"player->ani[1].timer = %i", gs->player->ani[1].timer);
al_draw_textf(gs->font10, al_map_rgb(83, 207, 46), width, 11*12, ALLEGRO_ALIGN_RIGHT,"player->ani[1].source_x = %f", gs->player->ani[1].source_x);
if (gs->player->ani[6].is_running) {
al_draw_textf(gs->font10, al_map_rgb(83, 207, 46), width, 12*12, ALLEGRO_ALIGN_RIGHT,"is_running");
}
 if (gs->player->ani[6].flag) {
al_draw_textf(gs->font10, al_map_rgb(83, 207, 46), width, 13*12, ALLEGRO_ALIGN_RIGHT,"flag");
}   
 
////debugging the player ext
	/*	for (j = 0; j < gs->player->ext.nverts; j++) {
			al_draw_pixel(gs->player->ext.vert[j][0]-(gs->player->pos.cx - width/2), gs->player->ext.vert[j][1]-(gs->player->pos.cy - height/2), al_map_rgb(83,207,46));
		}
	*/	

		al_flip_display();
	}
}

#endif // UPDATE_GRAPHICS_H
