
if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
	switch(event.keyboard.keycode) {
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
	}
}

else if (event.type == ALLEGRO_EVENT_KEY_UP) {
	switch(event.keyboard.keycode) {
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
	}
}

else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
	exit_game = true;
}
