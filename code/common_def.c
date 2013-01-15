#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stddef.h>

#ifndef COMMON_DEF_H
#define COMMON_DEF_H

typedef struct {
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
} Animatic;

typedef struct {
	float **vert;
	float *x, *y; //x and y describe the location of each vert with respect to some point (usually the subject's centerpoint)
	int nverts;
} Extension;

typedef struct {
	int current, nactive, key, nframes, frame_rate;
	ALLEGRO_BITMAP *spritesheet;
	int w, h, origin_x, origin_y, movement_type, reload_time, reload_timer; //origin of the bullet in distance from the center
	float damage;
	Extension ext;
	ALLEGRO_BITMAP **sprite;
	float *dx, *dy, *d, *x, *y, *source_x;
	int *timer;
	bool *exists;
} Weapon;	

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
    //
	float forward_speed;
	float turn_speed;
	float warp_speed;
	float side_speed;
} Motion;

typedef struct {
	bool exists, solid;
	float health;
	Position pos;
	float bouncy;  // bounce elasticity
	int room, ai, gfx_w, gfx_h;
	Extension ext;
	Motion mot;
	int nanimatics;
	ALLEGRO_BITMAP *sprite, *spritesheet;
	Animatic *ani;
	bool *keys;
} NPC;

typedef struct {
	float health;
	bool exists, solid, hot;
	// the wall's location is fully and independenly described by verts.
	// w and h are good for initializing.
	// d is used for drawing the sprite appropriately.
	float w, h, d; 
	Extension ext;
	ALLEGRO_BITMAP *sprite;
} Wall;

typedef struct {
	float parallax_rate;
	bool is_tiled;
	int x1, x2, y1, y2;
	ALLEGRO_BITMAP *background_image;
} Background;

typedef struct {
	int h, w;
	Wall **wall;
	int nwalls;
	bool active;
	int nbackgrounds;
	Background *background;
} Room;


typedef struct {
    bool on;
    int state;
} Maneuver;

typedef struct {
	bool exist, flying;
	float health;
	Position pos; 
	float bouncy;
	Extension ext; 
	Motion mot;
	ALLEGRO_BITMAP *sprite, *spritesheet;
	//ultimately gets drawn to the display
	//spritesheet is used for animatics
	int gfx_w, gfx_h, nanimatics;
	bool *aniflags;
	Animatic *ani;
	int hit_wall;
	int nweapons;
	Weapon weapon;
    int nmaneuvers;
    Maneuver *man;
    void (**man_func) (Position*, Motion*, Maneuver*, int);

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
	bool s_held;
} GameState;

int NKEYS = 9;
enum KEYS{UP, DOWN, LEFT, RIGHT, LCTRL, KEYA, KEYW, KEYS, KEYD};

const int width = 800;
const int height = 600;

const int FPS = 60;

const float PI = ALLEGRO_PI;

#endif // COMMON_DEF_H
