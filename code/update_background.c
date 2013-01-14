void update_background(Background *background, float x, float y, int w, int h) {

	float parallax_counter = x;
	bool parallax_switch = false;

	background->x1 = 0;
	background->x2 = -1;	
	background->y1 = -1;
	background->y2 = 0;

	while (parallax_counter > w/2) {
		
		parallax_counter -= width/background->parallax_rate;

		if (parallax_switch) {
			background->x1 += 2;
			parallax_switch = false;
		}

		else {
			background->x2 += 2;
			parallax_switch = true;
		}

	}

	while (parallax_counter < w/2 - width/background->parallax_rate) {
		
		parallax_counter += width/background->parallax_rate;

		if(parallax_switch) {
			background->x2 -= 2;
			parallax_switch = false;
		}

		else {
			background->x1 -= 2;
			parallax_switch = true;
		}

	}


	parallax_counter = y;
	parallax_switch = false;

	while (parallax_counter > h/2) {
		
		parallax_counter -= height/background->parallax_rate;

		if (parallax_switch) {
			background->y2 += 2;
			parallax_switch = false;
		}

		else {
			background->y1 += 2;
			parallax_switch = true;
		}

	}

	while (parallax_counter < h/2 - height/background->parallax_rate) {
		
		parallax_counter += height/background->parallax_rate;

		if(parallax_switch) {
			background->y1 -= 2;
			parallax_switch = false;
		}

		else {
			background->y2 -= 2;
			parallax_switch = true;
		}

	}


	

}
