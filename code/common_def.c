#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stddef.h>

#ifndef COMMON_DEF_H
#define COMMON_DEF_H

typedef struct {
	float **vert;
	float *x, *y; //x and y describe the location of each vert with respect to some point (usually the subject's centerpoint)
	int nverts;
} Extension;

typedef struct {
	// current x, current y, direction
	float cx, cy, cd;
    int room;
} Position;

typedef struct {
	// change in x and y motion per game frame (velocity)
	float dx, dy;
	// magnitude of overall velocity
	float spd;
	// change in orientation per game frame, CCW positive
	float dd;
	// acceleration in x or y direction per frame, constant
	float forward_speed;
	float turn_speed;
	float warp_speed;
	float side_speed;
    float movement_angle;
} Motion;

typedef struct {
    bool on;
    bool has_run; //ensures that Maneuvers turned on by other Maneuvers start in the same loop that they are turned on.
    int state; //keeps track of where we were in the maneuver function. 1 is the beginning of a loop, 0 is the end.
    int *animatic; //array of indexes of animations linked to this maneuver
    int nanimatics; //number of animations this maneuver triggers
    int key; //consider changing this to an array for key-combo moves
} Maneuver;

typedef struct {
	int source_x, source_y, destination_x, destination_y;
	int frame, w, h, scale_x, scale_y, state;
	ALLEGRO_COLOR tint;
	float pivot_x, pivot_y;
	//float angle;
	bool flag, is_running, draw;
    bool has_run;
	int timer, nframes, frame_rate; //60ths of a second between frames
	//float pivot_speed; //rotations per second
} Animatic;

typedef struct {
    Position pos;
    Motion mot;
    Extension ext;
    ALLEGRO_BITMAP *spritesheet, *sprite;
    int gfx_w, gfx_h;
    int nanimatics;
    Animatic *ani;
    void (**ani_func) (Animatic*, int);
    int nmaneuvers;
    Maneuver *man;
    void (**man_func) (Position*, Motion*, Maneuver*, int);
    bool exist;
    int damage;
} Bullet;

typedef struct {
    int reload_time, timer;
    int key;
    bool fire;
    float initial_velocity;
    Bullet bullet_temp; //copied to a member of the bullet array when the weapon fires
} Weapon;

typedef struct {
	bool exist, solid;
	float health;
	Position pos;
	float bouncy;  // bounce elasticity
	int ai, gfx_w, gfx_h;
	Extension ext;
	Motion mot;
	int nanimatics;
    void (**ani_func) (Animatic*, int);
	ALLEGRO_BITMAP *sprite, *spritesheet;
	Animatic *ani; 
    int nmaneuvers;
    Maneuver *man;
    void (**man_func) (Position*, Motion*, Maneuver*, int);
    int nweapons;
    Weapon *weapon;
} NPC;

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
    void (**ani_func) (Animatic*, int);
	Animatic *ani;
	int hit_wall;
	int nweapons;
	Weapon *weapon;
    int nmaneuvers;
    Maneuver *man;
    void (**man_func) (Position*, Motion*, Maneuver*, int);
} Player;

typedef struct {
	float health;
	bool exist, solid, hot;
	// w and h are good for initializing.
	// d is used for drawing the sprite appropriately.
	float w, h, d; 
	Extension ext;
    // wall does not need a position struct since it does not move and is a part of the room in which it exists
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
    Bullet *player_bullet;
    int current_pb;
    int n_player_bullets;
    Bullet *npc_bullet;
    int current_nb;
    int n_npc_bullets;
} GameState;

int NKEYS = 10;
enum KEYS{UP, DOWN, LEFT, RIGHT, LCTRL, LSHIFT, KEYA, KEYW, KEYS, KEYD};

const int width = 800;
const int height = 600;

const int FPS = 60;

const float PI = ALLEGRO_PI;

#endif // COMMON_DEF_H
