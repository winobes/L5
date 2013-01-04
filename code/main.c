#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>

struct Animatic {
	ALLEGRO_BITMAP *sprite;
	float source_x, source_y, destination_x, destination_y;
	int w, h, scale_x, scale_y;
	ALLEGRO_COLOR tint;
	float pivot_x, pivot_y;
//float angle;
	int flag, type;
	bool is_running, draw;
	int timer, nframes, frame_rate; //60ths of a second between frames
//float pivot_speed; //rotations per second
};

struct Extension {
	float **vert;
	int nverts;
};

struct Weapon {
	int current, nactive, key, nframes, frame_rate;
	ALLEGRO_BITMAP *spritesheet;
	int w, h, origin_x, origin_y, movement_type, reload_time, reload_timer; //origin of the bullet in distance from the center
	float damage;
	struct Extension ext;
	ALLEGRO_BITMAP **sprite;
	float *dx, *dy, *d, *x, *y, *source_x;
	int *timer;
	bool *exists;
};

struct Player {
	bool exist, flying;
	float health;
	float cx, cy, w, h, d, m;
	int shape;
	struct Extension ext; 
//used for collision testing. Vertices are calculated based on cx, cy, h, w, d.
	float dx, dy, s, dd, ddxy;
	ALLEGRO_BITMAP *sprite, *spritesheet;
 	//ultimately gets drawn to the display
	//spritesheet is used for animatics
	int gfx_w, gfx_h, nanimatics;
	bool *aniflags;
	struct Animatic *ani;
	int hit_wall;
	int nweapons;

	struct Weapon weapon;
};	

struct NPC {
	bool exists, solid;
	float health;
	float cx, cy, w, h, d, m;
	int shape, room, ai;
	struct Extension ext; //used for collision testing. Vertices are calculated based on cx, cy, h, w, d.
	float dx, dy, s, dd, ddxy;
	int nanimatics;
	ALLEGRO_BITMAP *sprite, *spritesheet;
	struct Animatic *ani;
	bool *keys;
};

struct Wall {
	float health;
	bool exists, solid, hot;
	float w, h, d; 
//the wall's location is fully and independenly described by verts. w and h are good for initializing. d is used for drawing the sprite appropriately.
	struct Extension ext;
	ALLEGRO_BITMAP *sprite;
};

struct Background {
	float parallax_rate;
	int parallax_x1, parallax_x2, parallax_y1, parallax_y2;
	ALLEGRO_BITMAP *background_image;
};
	

struct Room {
	int h, w;
	struct Wall *wall;
	int nwalls;
	bool active;
	int nbackgrounds;
	struct Background *background;
};

enum KEYS{RIGHT, DOWN, LEFT, UP, LCTRL};

const int width = 800;
const int height = 600;

const int FPS = 60;

int current_room = 0;

bool keys [5] = {false, false, false, false, false};

ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* display;

#include "init_allegro.c"
#include "dotproduct.c"
#include "projection.c"
#include "bounce.c" // bounce is used mostly for the collision of two ships (e.g. player with npc). The resulting collision assumes that the two ships are perfectly round (note however that it should only be called *after* a collision has been detected collide and the Extensions have been appropriately projected away from one another)
#include "reflect.c" //reflect actually ususes the projection vector found by collide to reflect a velocity off of a particular surface of an imobile Extension (e.g. a wall)
#include "projdot.c" // (a projected onto b) dot b
#include "calculate_speed.c"
#include "normalize.c" //converts a vector to its normal by pointer
#include "collide.c" //determines if two Extensions are intersecting using the separating axis theorem. If they are interesecting, it returns true and changes penetration_vector to the normal of the surface with the smallest penetration penetration_scalar is the depth of the penetration. Projecting the Extensions so that they are no longer colliding must be done outside of the function. This is done so that the two Extensions can share the projection in a ship on ship collision, but in ship on wall collisions only the ship is projected.
#include "calculate_verts_ship.c" //calculates vertices based on the shape flag, direction, and position. the NCP and Player types have approprate variables.
#include "calculate_verts_wall.c" // calculates the three remaining vertices based on vert[0], width, height, and direction. Assumes that the wall is rectangular. May have to add a shape flag as in the above.
#include "update_background.c"
#include "ai1.c"
#include "animatic1.c"
#include "game_loop.c"
#include "shutdown.c"

int main (int argc, char* argv[]) {

	init_allegro();

	game_loop();

	shutdown();

	return 0;


}



