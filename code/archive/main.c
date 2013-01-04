#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>

struct Animatic {
	ALLEGRO_BITMAP *sprite;
	float source_x;
	float source_y;
	int width;
	int height;
	ALLEGRO_COLOR tint;
	float pivot_x;
	float pivot_y;
	//float angle;
	float destination_x;
	float destination_y;
	int scale_x;
	int scale_y;
	int key;
	bool is_running;
	bool draw;
	int timer;
	int nframes;
	int frame_rate; //60ths of a second between frames
	//float pivot_speed; //rotations per second
};

struct Subject {
	float x;
	float y;
	int width;
	int height;
	float dx;
	float dy;
	float health;
	float direction;
	float rotation;
	float acceleration;
	bool wall;
	bool enemy;
	ALLEGRO_BITMAP *sprite;
	ALLEGRO_BITMAP *spritesheet;
	int weapon;
	int reload_timer;
	int reload_time;
	bool exist;
	int nanimatics;
	struct Animatic *animatic;
};		
	
struct Room {
	ALLEGRO_BITMAP *background;
	ALLEGRO_BITMAP *background_buffer;
	int height;
	int width;
	struct Subject *subject;
	int nsubjects;
	bool initialized;
};

enum KEYS{RIGHT, DOWN, LEFT, UP, LCTRL};

const int width = 640;
const int height = 480;

const int FPS = 60;

bool keys [5] = {false, false, false, false, false};

ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* display;

#include "init.c"
#include "collide.c"
#include "animatic1.c"
#include "game_loop.c"
#include "shutdown.c"

int main (int argc, char* argv[]) {

	init();

	game_loop();

	shutdown();

	return 0;


}

