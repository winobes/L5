#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stddef.h>

#ifndef COMMON_DEF_H
#define COMMON_DEF_H

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
	float *dis;
	float *ang; //d and a describe the location of each vert with respect to some point (usually the subject's centerpoint)
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

typedef struct {
	// current x, current y, direction
	float cx, cy, cd;
} Position;

typedef struct {
	// change in x and y motion per game frame (velocity)
	float dx, dy;
	// magnitude of overall velocity
	float spd;
	// change in orientation per game frame, CCW positive
	float dd;
	// acceleration in x or y direction per frame, constant
	float ddxy;
} Motion;

typedef struct {
	bool exists, solid;
	float health;
	Position pos;
	float bouncy;  // bounce elasticity
	int room, ai, gfx_w, gfx_h;
	struct Extension ext; //used for collision testing. Vertices are calculated based on cx, cy, h, w, d.
	Motion mot;
	int nanimatics;
	ALLEGRO_BITMAP *sprite, *spritesheet;
	struct Animatic *ani;
	bool *keys;
} NPC;

typedef struct {
	float health;
	bool exists, solid, hot;
	// the wall's location is fully and independenly described by verts.
	// w and h are good for initializing.
	// d is used for drawing the sprite appropriately.
	float w, h, d; 
	struct Extension ext;
	ALLEGRO_BITMAP *sprite;
} Wall;

struct Background {
	float parallax_rate;
	bool is_tiled;
	int x1, x2, y1, y2;
	ALLEGRO_BITMAP *background_image;
};

typedef struct {
	int h, w;
	Wall **wall;
	int nwalls;
	bool active;
	int nbackgrounds;
	struct Background *background;
} Room;

typedef struct {
	bool exist, flying;
	float health;
	Position pos; 
	float bouncy;
	struct Extension ext; 
	//used for collision testing. Vertices are calculated based on cx, cy, h, w, d.
	Motion mot;
	ALLEGRO_BITMAP *sprite, *spritesheet;
	//ultimately gets drawn to the display
	//spritesheet is used for animatics
	int gfx_w, gfx_h, nanimatics;
	bool *aniflags;
	struct Animatic *ani;
	int hit_wall;
	int nweapons;
	struct Weapon weapon;
} Player;

typedef struct {
	//int nplayers; // = 1
	Player *player;
	int nnpcs;
	NPC *npc;
	int nrooms;
	Room **room;
	int current_room;
	ALLEGRO_FONT *font10;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_DISPLAY* display;
	float player_forward_speed;
	float player_turn_speed;
	float player_warp_speed;
	float player_side_speed;
	float npc_turn_speed;
	float npc_forward_speed;
	float npc_side_speed;
	bool s_held;
} GameState;

int NKEYS = 9;
enum KEYS{RIGHT, DOWN, LEFT, UP, LCTRL, KEYA, KEYW, KEYS, KEYD};
enum SHAPE{RECTANGLE, OCTAGON};

const int width = 800;
const int height = 600;

const int FPS = 60;

const float PI = ALLEGRO_PI;

#endif // COMMON_DEF_H
