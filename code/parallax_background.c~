if (current_room == 0) {

	parallax1_x1 = 0;
	parallax1_x2 = -1;
	parallax1_y1 = -1;
	parallax1_y2 = 0;

	parallax_counter = player.cx;
	parallax_switch = false;

	//if (parallax_counter > room[0].w/2) {
		while (parallax_counter > room[0].w/2) {
			parallax_counter -= width/parallax1_rate;
		
			if(parallax_switch) {
				parallax1_x1 += 2;
				parallax_switch = false;
			}

			else  {
				parallax1_x2 += 2;
				parallax_switch = true;
			}
		}
	//}


	//else if (parallax_counter < room[0].w/2 - width/parallax1_rate) {
		while (parallax_counter < room[0].w/2 - width/parallax1_rate) {
			parallax_counter += width/parallax1_rate;
		
			if(parallax_switch) {
				parallax1_x2 -= 2;
				parallax_switch = false;
			}

			else  {
				parallax1_x1 -= 2;
				parallax_switch = true;
			}
		}
//	}

	parallax_counter = player.cy;
	parallax_switch = false;

	//if (parallax_counter > room[0].h/2) {
		while (parallax_counter > room[0].h/2) {
			parallax_counter -= height/parallax1_rate;
		
			if(parallax_switch) {
				parallax1_y2 += 2;
				parallax_switch = false;
			}

			else {
				parallax1_y1 += 2;
				parallax_switch = true;
			}
		}
//	}

//	else if (parallax_counter < room[0].h/2 - height/parallax1_rate) {
		while (parallax_counter < room[0].h/2 - height/parallax1_rate) {
			parallax_counter += height/parallax1_rate;
		
			if(parallax_switch) {
				parallax1_y1 -= 2;
				parallax_switch = false;
			}

			else {
				parallax1_y2 -= 2;
				parallax_switch = true;
			}
		}
//	}


/*

	al_draw_bitmap(background1, -parallax1_rate*(player.cx-room[0].w/2) + parallax1_x1*width, -parallax1_rate*(player.cy-room[0].h/2) + parallax1_y1*height , 0);

	al_draw_bitmap(background1, -parallax1_rate*(player.cx-room[0].w/2) + parallax1_x2*width, -parallax1_rate*(player.cy-room[0].h/2) + parallax1_y2*height , 0);

	al_draw_bitmap(background1, -parallax1_rate*(player.cx-room[0].w/2) + parallax1_x1*width, -parallax1_rate*(player.cy-room[0].h/2) + parallax1_y2*height , 0);

	al_draw_bitmap(background1, -parallax1_rate*(player.cx-room[0].w/2) + parallax1_x2*width, -parallax1_rate*(player.cy-room[0].h/2) + parallax1_y1*height , 0);




	al_draw_bitmap(background2, -parallax2_rate*(player.cx-room[0].w/2) + 0*width, -parallax2_rate*(player.cy-room[0].h/2) + 0*height , 0);
*/


	parallax3_x1 = 0;
	parallax3_x2 = -1;
	parallax3_y1 = -1;
	parallax3_y2 = 0;

	parallax_counter = player.cx;
	parallax_switch = false;

	if (parallax_counter > room[0].w/2) {
		while (parallax_counter > room[0].w/2) {
			parallax_counter -= width/parallax3_rate;
		
			if(parallax_switch) {
				parallax3_x1 += 2;
				parallax_switch = false;
			}

			else if(!parallax_switch) {
				parallax3_x2 += 2;
				parallax_switch = true;
			}
		}
	}


	else if (parallax_counter < room[0].w/2 - width/parallax3_rate) {
		while (parallax_counter < room[0].w/2 - width/parallax3_rate) {
			parallax_counter += width/parallax3_rate;
		
			if(parallax_switch) {
				parallax3_x2 -= 2;
				parallax_switch = false;
			}

			else if(!parallax_switch) {
				parallax3_x1 -= 2;
				parallax_switch = true;
			}
		}
	}

	parallax_counter = player.cy;
	parallax_switch = false;

	if (parallax_counter > room[0].h/2) {
		while (parallax_counter > room[0].h/2) {
			parallax_counter -= height/parallax3_rate;
		
			if(parallax_switch) {
				parallax3_y2 += 2;
				parallax_switch = false;
			}

			else if(!parallax_switch) {
				parallax3_y1 += 2;
				parallax_switch = true;
			}
		}
	}

	else if (parallax_counter < room[0].h/2 - height/parallax3_rate) {
		while (parallax_counter < room[0].h/2 - height/parallax3_rate) {
			parallax_counter += height/parallax3_rate;
		
			if(parallax_switch) {
				parallax3_y1 -= 2;
				parallax_switch = false;
			}

			else if(!parallax_switch) {
				parallax3_y2 -= 2;
				parallax_switch = true;
			}
		}
	}


/*

	al_draw_bitmap(background3, -parallax3_rate*(player.cx-room[0].w/2) + parallax3_x1*width, -parallax3_rate*(player.cy-room[0].h/2) + parallax3_y1*height , 0);

	al_draw_bitmap(background3, -parallax3_rate*(player.cx-room[0].w/2) + parallax3_x2*width, -parallax3_rate*(player.cy-room[0].h/2) + parallax3_y2*height , 0);

	al_draw_bitmap(background3, -parallax3_rate*(player.cx-room[0].w/2) + parallax3_x1*width, -parallax3_rate*(player.cy-room[0].h/2) + parallax3_y2*height , 0);

	al_draw_bitmap(background3, -parallax3_rate*(player.cx-room[0].w/2) + parallax3_x2*width, -parallax3_rate*(player.cy-room[0].h/2) + parallax3_y1*height , 0);
*/
}
