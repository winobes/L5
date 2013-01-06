#include "common_def.c"

#ifndef SHUTDOWN_H
#define SHUTDOWN_H

void shutdown_game(GameState *gs) {

	#ifdef DEBUG
	printf("in shutdown\n");
	#endif

	if (gs->timer) {
		#ifdef DEBUG
		printf("destroying timer\n");
		#endif
		al_destroy_timer(gs->timer);
		gs->timer = NULL;
	}

	if (gs->display) {
		#ifdef DEBUG
		printf("destroying display\n");
		#endif
		al_destroy_display(gs->display);
		gs->display = NULL;
	}

	if (gs->event_queue) {
		#ifdef DEBUG
		printf("destroying event queue\n");
		#endif
		al_destroy_event_queue(gs->event_queue);
		gs->event_queue = NULL;
	}

}

#endif // SHUTDOWN_H
