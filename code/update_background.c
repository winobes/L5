void update_background(struct Background *background, float x, float y, int w, int h) {

	float parallax_counter = x;
	bool parallax_switch = false;

	background->parallax_x1 = 0;
	background->parallax_x2 = -1;	
	background->parallax_y1 = -1;
	background->parallax_y2 = 0;

	while (parallax_counter > w/2) {
		
		parallax_counter -= width/background->parallax_rate;

		if (parallax_switch) {
			background->parallax_x1 += 2;
			parallax_switch = false;
		}

		else {
			background->parallax_x2 += 2;
			parallax_switch = true;
		}

	}

	while (parallax_counter < w/2 - width/background->parallax_rate) {
		
		parallax_counter += width/background->parallax_rate;

		if(parallax_switch) {
			background->parallax_x2 -= 2;
			parallax_switch = false;
		}

		else {
			background->parallax_x1 -= 2;
			parallax_switch = true;
		}

	}


	parallax_counter = y;
	parallax_switch = false;

	while (parallax_counter > h/2) {
		
		parallax_counter -= height/background->parallax_rate;

		if (parallax_switch) {
			background->parallax_y2 += 2;
			parallax_switch = false;
		}

		else {
			background->parallax_y1 += 2;
			parallax_switch = true;
		}

	}

	while (parallax_counter < h/2 - height/background->parallax_rate) {
		
		parallax_counter += height/background->parallax_rate;

		if(parallax_switch) {
			background->parallax_y1 -= 2;
			parallax_switch = false;
		}

		else {
			background->parallax_y2 -= 2;
			parallax_switch = true;
		}

	}


	

}
