void abort_game(const char* message)
{
	printf("%s \n", message);
	exit(1);
}

void init_allegro(void)
{
	if (!al_init()) {
	abort_game("Failed to initialize allegro");
	}
 
	if(!al_init_image_addon()){
		abort_game("failed to initialize allegro image addon!");
	}

	if (!al_install_keyboard()) {
		abort_game("Failed to install keyboard");
	}
 
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		abort_game("Failed to create timer");
	}
 
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(width, height);
	if (!display){
		abort_game("Failed to create display");
	}
 
	event_queue = al_create_event_queue();
	if (!event_queue) {
		abort_game("Failed to create event queue");
	}

	al_init_font_addon();
	al_init_ttf_addon();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
}
