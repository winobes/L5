#include "common_def.c"

#ifndef ROOMS_H
#define ROOMS_H

typedef struct {
	int h, w;
	Wall **wall;
	int nwalls;
	bool active;
	int nbackgrounds;
	struct Background *background;
} Room;



Room **init_rooms()
{
	int nrooms = 2;
	int i, j, k;

	Room **room = malloc(nrooms * sizeof(Room*));
	for (i = 0; i < nrooms; i++) {
		room[i] = malloc(sizeof(Room));
	}
    
	room[0]->nwalls = 20;
	room[1]->nwalls = 14;

	room[0]->w = 5000/5;
	room[0]->h = 5000/5;

	room[1]->w = 1700/5;
	room[1]->h = 3400/5;

	for (i = 0; i < nrooms; i++) {
		room[i]->active = false;
		
		room[i]->wall = malloc(room[i]->nwalls * sizeof(Wall*));
		for (j = 0; j < room[i]->nwalls; j++) {
			room[i]->wall[j] = malloc(sizeof(Wall));
		}

		for (j = 0; j < room[i]->nwalls; j++) {
			room[i]->wall[j]->exists = true;
			room[i]->wall[j]->ext.nverts = 4;
			room[i]->wall[j]->ext.vert = malloc(room[i]->wall[j]->ext.nverts * sizeof(float*));
			for (k = 0; k < room[i]->wall[j]->ext.nverts; k++) {
				room[i]->wall[j]->ext.vert[k] = malloc(2 * sizeof(room[i]->wall[j]->ext.vert[i]));
			}
		}

	}

	for (i = 0; i < 12; i++) {
		room[0]->wall[i]->h = 800/5;
		room[0]->wall[i]->w = 100/5;
		room[0]->wall[i]->sprite = al_load_bitmap("gfx/little1.png");
		room[0]->wall[i]->exists = true;
		room[0]->wall[i]->solid = true;
	}

	for (i = 12; i < 18; i++) {
		room[0]->wall[i]->h = 200/5;
		room[0]->wall[i]->w = 200/5;
		room[0]->wall[i]->sprite = al_load_bitmap("gfx/little0.png"); 
		room[0]->wall[i]->exists = true;
		room[0]->wall[i]->solid = true;
	}

	for (i = 18; i < 20; i++) {
		room[0]->wall[i]->h = 20;
		room[0]->wall[i]->w = 20;
		room[0]->wall[i]->sprite = al_load_bitmap("gfx/little2.png");
		room[0]->wall[i]->exists = true;
		room[0]->wall[i]->solid = true;
	}

	room[0]->wall[0]->ext.vert[0][0] = 600/5;
	room[0]->wall[0]->ext.vert[0][1] = 900/5;
	room[0]->wall[0]->d = 3*ALLEGRO_PI/2;

	room[0]->wall[1]->ext.vert[0][0] = 1400/5;
	room[0]->wall[1]->ext.vert[0][1] = 800/5;
	room[0]->wall[1]->d = 0;

	room[0]->wall[2]->ext.vert[0][0] = 1600/5;
	room[0]->wall[2]->ext.vert[0][1] = 1500/5;
	room[0]->wall[2]->d = 0;

	room[0]->wall[3]->ext.vert[0][0] = 2800/5;
	room[0]->wall[3]->ext.vert[0][1] = 1100/5;
	room[0]->wall[3]->d = ALLEGRO_PI/4;

	room[0]->wall[4]->ext.vert[0][0] = 2600/5;
	room[0]->wall[4]->ext.vert[0][1] = 1550/5;
	room[0]->wall[4]->d = 3*ALLEGRO_PI/2;

	room[0]->wall[5]->ext.vert[0][0] = 3400/5;
	room[0]->wall[5]->ext.vert[0][1] = 1450/5;
	room[0]->wall[5]->d = 0;

	room[0]->wall[6]->ext.vert[0][0] = 4450/5;
	room[0]->wall[6]->ext.vert[0][1] = 600/5;
	room[0]->wall[6]->d = 0;

	room[0]->wall[7]->ext.vert[0][0] = 4450/5; 
	room[0]->wall[7]->ext.vert[0][1] = 1400/5;
	room[0]->wall[7]->d = 0;

	room[0]->wall[8]->ext.vert[0][0] = 4450/5; 
	room[0]->wall[8]->ext.vert[0][1] = 2200/5;
	room[0]->wall[8]->d = 0;

	room[0]->wall[9]->ext.vert[0][0] = 4450/5;
	room[0]->wall[9]->ext.vert[0][1] = 3000/5;
	room[0]->wall[9]->d = 0;

	room[0]->wall[10]->ext.vert[0][0] = 1300/5;
	room[0]->wall[10]->ext.vert[0][1] = 2500/5;
	room[0]->wall[10]->d = ALLEGRO_PI/4;

	room[0]->wall[11]->ext.vert[0][0] = 500/5;
	room[0]->wall[11]->ext.vert[0][1] = 4450/5;
	room[0]->wall[11]->d = 3*ALLEGRO_PI/2;

	room[0]->wall[12]->ext.vert[0][0] = 400/5;
	room[0]->wall[12]->ext.vert[0][1] = 400/5;
	room[0]->wall[12]->d = 0;

	room[0]->wall[13]->ext.vert[0][0] = 2400/5;
	room[0]->wall[13]->ext.vert[0][1] = 400/5;
	room[0]->wall[13]->d = 0;

	room[0]->wall[14]->ext.vert[0][0] = 1500/5; 
	room[0]->wall[14]->ext.vert[0][1] = 1400/5;
	room[0]->wall[14]->d = 0;

	room[0]->wall[15]->ext.vert[0][0] = 1400/5; 
	room[0]->wall[15]->ext.vert[0][1] = 3400/5;
	room[0]->wall[15]->d = 0;

	room[0]->wall[16]->ext.vert[0][0] = 2400/5;
	room[0]->wall[16]->ext.vert[0][1] = 2900/5;
	room[0]->wall[16]->d = 0;

	room[0]->wall[17]->ext.vert[0][0] = 3900; 
	room[0]->wall[17]->ext.vert[0][1] = 3900;
	room[0]->wall[17]->d = 0;

	room[0]->wall[18]->ext.vert[0][0] = 1500/5;
	room[0]->wall[18]->ext.vert[0][1] = 500/5;
	room[0]->wall[18]->d = ALLEGRO_PI/4;
	room[0]->wall[18]->solid = false;

	room[0]->wall[19]->ext.vert[0][0] = 2500/5;
	room[0]->wall[19]->ext.vert[0][1] = 4500/5;
	room[0]->wall[19]->d = ALLEGRO_PI/4;
	room[0]->wall[19]->solid = false;

	for (i = 0; i < 12; i++) {
		room[1]->wall[i]->h = 800/5;
		room[1]->wall[i]->w = 100/5;
		room[1]->wall[i]->sprite = al_load_bitmap("gfx/little1.png");
		room[1]->wall[i]->exists = true;
		room[1]->wall[i]->solid = true;
	}

	for (i = 12; i < 14; i++) {
		room[1]->wall[i]->h = 20;
		room[1]->wall[i]->w = 20;
		room[1]->wall[i]->sprite = al_load_bitmap("gfx/little2.png");
		room[1]->wall[i]->exists = true;
		room[1]->wall[i]->solid = true;
	}

		room[1]->wall[0]->ext.vert[0][0] = 100/5;
		room[1]->wall[0]->ext.vert[0][1] = 100/5;
		room[1]->wall[0]->d = 3*ALLEGRO_PI/2;

		room[1]->wall[1]->ext.vert[0][0] = 900/5;
		room[1]->wall[1]->ext.vert[0][1] = 100/5;
		room[1]->wall[1]->d = 3*ALLEGRO_PI/2;
		
		room[1]->wall[2]->ext.vert[0][0] = 1600/5;
		room[1]->wall[2]->ext.vert[0][1] = 100/5;
		room[1]->wall[2]->d = 0;
		
		room[1]->wall[3]->ext.vert[0][0] = 1600/5;
		room[1]->wall[3]->ext.vert[0][1] = 900/5;
		room[1]->wall[3]->d = 0;
		
		room[1]->wall[4]->ext.vert[0][0] = 1600/5;
		room[1]->wall[4]->ext.vert[0][1] = 1700/5;
		room[1]->wall[4]->d = 0;
		
		room[1]->wall[5]->ext.vert[0][0] = 1600/5;
		room[1]->wall[5]->ext.vert[0][1] = 2500/5;
		room[1]->wall[5]->d = 0;
		
		room[1]->wall[6]->ext.vert[0][0] = 800/5;
		room[1]->wall[6]->ext.vert[0][1] = 3300/5;
		room[1]->wall[6]->d = 3*ALLEGRO_PI/2;
		
		room[1]->wall[7]->ext.vert[0][0] = 0;
		room[1]->wall[7]->ext.vert[0][1] = 3300/5;
		room[1]->wall[7]->d = 3*ALLEGRO_PI/2;
		
		room[1]->wall[8]->ext.vert[0][0] = 0;
		room[1]->wall[8]->ext.vert[0][1] = 2400/5;
		room[1]->wall[8]->d = 0;
		
		room[1]->wall[9]->ext.vert[0][0] = 0;
		room[1]->wall[9]->ext.vert[0][1] = 1600/5;
		room[1]->wall[9]->d = 0;

		room[1]->wall[10]->ext.vert[0][0] = 0;
		room[1]->wall[10]->ext.vert[0][1] = 800/5;
		room[1]->wall[10]->d = 0;
		
		room[1]->wall[11]->ext.vert[0][0] = 0;
		room[1]->wall[11]->ext.vert[0][1] = 0;
		room[1]->wall[11]->d = 0;
		
		room[1]->wall[12]->ext.vert[0][0] = 400/5;
		room[1]->wall[12]->ext.vert[0][1] = 400/5;
		room[1]->wall[12]->d = ALLEGRO_PI/4;
		room[1]->wall[12]->solid = false;
		
		room[1]->wall[13]->ext.vert[0][0] = 1300/5;
		room[1]->wall[13]->ext.vert[0][1] = 2900/5;
		room[1]->wall[13]->d = ALLEGRO_PI/4;
		room[1]->wall[13]->solid = false;
		
	for (i = 0; i < nrooms; i++) {
		for (j = 0; j < room[i]->nwalls; j++) {
			calculate_verts_wall(&room[i]->wall[j]->ext, room[i]->wall[j]->w, room[i]->wall[j]->h, room[i]->wall[j]->d);
		}
	}

	return room;

}

#endif // ROOMS_H
