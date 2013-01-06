#include "common_def.c"

#ifndef SHUTDOWN_H
#define SHUTDOWN_H

void shutdown() {

	if (timer) {
		al_destroy_timer(timer);
	}
 
	if (display) {
		al_destroy_display(display);
	}
 
	if (event_queue) {
		al_destroy_event_queue(event_queue);
	}

}

#endif // SHUTDOWN_H
