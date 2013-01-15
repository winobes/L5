#include "common_def.c"

#ifndef NPC_H
#define NPC_H

NPC *init_npcs(GameState *gs)
{
	int i;

	NPC *npc = malloc(gs->nnpcs * sizeof(NPC));

	npc[0].solid = true;
	npc[0].exists = true;
	npc[0].health = 10;
	npc[0].pos.cx = 0;
	npc[0].pos.cy = 0;
	npc[0].pos.cd = PI/2;
	npc[0].bouncy = 100;
	npc[0].gfx_w = 15;
	npc[0].gfx_h = 15;
	npc[0].room = 0;
	npc[0].ai = 1;
	npc[0].mot.dx = 0;
	npc[0].mot.dy = -1;
	npc[0].mot.dd = .05;
	npc[0].mot.turn_speed = .5;
	npc[0].mot.forward_speed = .05;
	npc[0].mot.side_speed = 0;
    npc[0].mot.warp_speed = 0;

	npc[0].sprite = al_create_bitmap(npc[0].gfx_w, npc[0].gfx_h);
	npc[0].spritesheet = al_load_bitmap("gfx/firefly_spritesheet.png");
	npc[0].nanimatics = 3;

	npc[0].keys = malloc(5 * sizeof(bool));

	for(i = 0; i < 5; i++) {
		npc[0].keys[i] = false;
	}

	npc[0].ext.nverts = 4;

	npc[0].ext.vert = malloc(npc[0].ext.nverts * sizeof(float*));
	for (i = 0; i < npc[0].ext.nverts; i++) {
		npc[0].ext.vert[i] = malloc(2 * sizeof(npc[0].ext.vert[i]));
	}

	npc[0].ext.x = malloc(npc[0].ext.nverts * sizeof(float));
	npc[0].ext.y = malloc(npc[0].ext.nverts * sizeof(float));

	npc[0].ext.x[0] = -7.5; 
    npc[0].ext.y[0] = -7.5;
	npc[0].ext.x[1] = 7.5; 
    npc[0].ext.y[1] = -7.5;
	npc[0].ext.x[2] = 7.5; 
    npc[0].ext.y[2] = 7.5;
	npc[0].ext.x[3] = -7.5; 
    npc[0].ext.y[3] = 7.5;

	npc[0].nanimatics = 3;
	npc[0].ani = malloc(npc[0].nanimatics * sizeof(Animatic));

	npc[0].ani[0].source_x = 0;
	npc[0].ani[0].source_y = 0;
	npc[0].ani[0].w = 15;
	npc[0].ani[0].h = 15;
	npc[0].ani[0].pivot_x = 8;
	npc[0].ani[0].pivot_y = 8;
	npc[0].ani[0].destination_x = 8;
	npc[0].ani[0].destination_y = 8;
	npc[0].ani[0].scale_x = 1;
	npc[0].ani[0].scale_y = 1;
	npc[0].ani[0].is_running = false;
	npc[0].ani[0].draw = true;
	npc[0].ani[0].type = 0;
	npc[0].ani[0].flag = -1;
	npc[0].ani[0].tint = al_map_rgba_f(1,1,1,1);

	npc[0].ani[1].source_x = 0;
	npc[0].ani[1].source_y = 15;
	npc[0].ani[1].w = 15;
	npc[0].ani[1].h = 15;
	npc[0].ani[1].pivot_x = 8;
	npc[0].ani[1].pivot_y = 8;
	npc[0].ani[1].destination_x = 8;
	npc[0].ani[1].destination_y = 8;
	npc[0].ani[1].scale_x = 1;
	npc[0].ani[1].scale_y = 1;
	npc[0].ani[1].is_running = false;
	npc[0].ani[1].draw = false;
	npc[0].ani[1].nframes = 4;
	npc[0].ani[1].frame_rate = 15;
	npc[0].ani[1].flag = UP;
	npc[0].ani[1].type = 1;
	npc[0].ani[1].tint = al_map_rgba_f(1,1,1,1);

	npc[0].ani[2].source_x = 0;
	npc[0].ani[2].source_y = 30;
	npc[0].ani[2].w = 15;
	npc[0].ani[2].h = 15;
	npc[0].ani[2].pivot_x = 8;
	npc[0].ani[2].pivot_y = 8;
	npc[0].ani[2].destination_x = 8;
	npc[0].ani[2].destination_y = 8;
	npc[0].ani[2].scale_x = 1;
	npc[0].ani[2].scale_y = 1;
	npc[0].ani[2].is_running = false;
	npc[0].ani[2].draw = false;
	npc[0].ani[2].nframes = 4;
	npc[0].ani[2].frame_rate = 15;
	npc[0].ani[2].flag = DOWN;
	npc[0].ani[2].type = 1;
	npc[0].ani[2].tint = al_map_rgba_f(1,1,1,1);

	npc[1].solid = true;
	npc[1].exists = true;
	npc[1].health = 10;
	npc[1].pos.cx = 10;
	npc[1].pos.cy = 10;
	npc[1].pos.cd = PI/2;
	npc[1].bouncy = 100;
	npc[1].gfx_w = 15;
	npc[1].gfx_h = 15;
	npc[1].room = 0;
	npc[1].ai = 1;
	npc[1].mot.dx = 0;
	npc[1].mot.dy = -1;
	npc[1].mot.dd = .05;
	npc[1].mot.turn_speed = .5;
	npc[1].mot.forward_speed = .05;
	npc[1].mot.side_speed = 0;
    npc[1].mot.warp_speed = 0;
	npc[1].sprite = al_create_bitmap(npc[1].gfx_w, npc[1].gfx_h);
	npc[1].spritesheet = al_load_bitmap("gfx/firefly_spritesheet.png");
	npc[1].nanimatics = 3;

	npc[1].keys = malloc(5 * sizeof(bool));

	for(i = 0; i < 5; i++) {
		npc[1].keys[i] = false;
	}

	npc[1].ext.nverts = 4;

	npc[1].ext.vert = malloc(npc[1].ext.nverts * sizeof(float*));
	for (i = 0; i < npc[1].ext.nverts; i++) {
		npc[1].ext.vert[i] = malloc(2 * sizeof(npc[1].ext.vert[i]));
	}

	npc[1].ext.x = malloc(npc[1].ext.nverts * sizeof(float));
	npc[1].ext.y = malloc(npc[1].ext.nverts * sizeof(float));

	npc[1].ext.x[0] = -7.5; 
    npc[1].ext.y[0] = -7.5;
	npc[1].ext.x[1] = 7.5; 
    npc[1].ext.y[1] = -7.5;
	npc[1].ext.x[2] = 7.5; 
    npc[1].ext.y[2] = 7.5;
	npc[1].ext.x[3] = -7.5; 
    npc[1].ext.y[3] = 7.5;

	npc[1].nanimatics = 3;
	npc[1].ani = malloc(npc[1].nanimatics * sizeof(Animatic));

	npc[1].ani[0].source_x = 0;
	npc[1].ani[0].source_y = 0;
	npc[1].ani[0].w = 15;
	npc[1].ani[0].h = 15;
	npc[1].ani[0].pivot_x = 8;
	npc[1].ani[0].pivot_y = 8;
	npc[1].ani[0].destination_x = 8;
	npc[1].ani[0].destination_y = 8;
	npc[1].ani[0].scale_x = 1;
	npc[1].ani[0].scale_y = 1;
	npc[1].ani[0].is_running = false;
	npc[1].ani[0].draw = true;
	npc[1].ani[0].type = 0;
	npc[1].ani[0].flag = -1;
	npc[1].ani[0].tint = al_map_rgba_f(1,1,1,1);

	npc[1].ani[1].source_x = 0;
	npc[1].ani[1].source_y = 15;
	npc[1].ani[1].w = 15;
	npc[1].ani[1].h = 15;
	npc[1].ani[1].pivot_x = 8;
	npc[1].ani[1].pivot_y = 8;
	npc[1].ani[1].destination_x = 8;
	npc[1].ani[1].destination_y = 8;
	npc[1].ani[1].scale_x = 1;
	npc[1].ani[1].scale_y = 1;
	npc[1].ani[1].is_running = false;
	npc[1].ani[1].draw = false;
	npc[1].ani[1].nframes = 4;
	npc[1].ani[1].frame_rate = 15;
	npc[1].ani[1].flag = UP;
	npc[1].ani[1].type = 1;
	npc[1].ani[1].tint = al_map_rgba_f(1,1,1,1);

	npc[1].ani[2].source_x = 0;
	npc[1].ani[2].source_y = 30;
	npc[1].ani[2].w = 15;
	npc[1].ani[2].h = 15;
	npc[1].ani[2].pivot_x = 8;
	npc[1].ani[2].pivot_y = 8;
	npc[1].ani[2].destination_x = 8;
	npc[1].ani[2].destination_y = 8;
	npc[1].ani[2].scale_x = 1;
	npc[1].ani[2].scale_y = 1;
	npc[1].ani[2].is_running = false;
	npc[1].ani[2].draw = false;
	npc[1].ani[2].nframes = 4;
	npc[1].ani[2].frame_rate = 15;
	npc[1].ani[2].flag = DOWN;
	npc[1].ani[2].type = 1;
	npc[1].ani[2].tint = al_map_rgba_f(1,1,1,1);

	return npc;
}

#endif // NPC_H
