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
	int parallax_x1, parallax_x2, parallax_y1, parallax_y2;
	ALLEGRO_BITMAP *background_image;
};

enum KEYS{RIGHT, DOWN, LEFT, UP, LCTRL};

const int width = 800;
const int height = 600;

const int FPS = 60;

int current_room = 0;

bool keys [5] = {false, false, false, false, false};

#endif // COMMON_DEF_H
