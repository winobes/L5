#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>

#include "common_def.c"

#include "motion_math.c"

#include "collide.c"
#include "update_background.c"
#include "ai1.c"
#include "animatic1.c"
#include "game_loop.c"


int main (int argc, char* argv[]) {

	game_loop();

	return 0;
}
