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


    npc[0].nmaneuvers = 5;
    npc[0].man = malloc(npc[0].nmaneuvers * sizeof (Maneuver)); 

    
   

npc[0].man_func = malloc(npc[0].nmaneuvers * sizeof (void (*)(Position*, Motion*))); 

    //registering maneuver functions
    npc[0].man_func[0] = &thrust_forward;
    npc[0].man_func[1] = &thrust_backward;
    npc[0].man_func[2] = &rotate_right;
    npc[0].man_func[3] = &rotate_left;
    npc[0].man_func[4] = &slow_to_stop;


    for (i = 0; i < npc[0].nmaneuvers; i++) {
        npc[0].man[i].on = false;
        npc[0].man[i].state = 1;
    }

    npc[0].man[0].nanimatics = 1;
    npc[0].man[1].nanimatics = 0;
    npc[0].man[2].nanimatics = 0;
    npc[0].man[3].nanimatics = 1;
    npc[0].man[4].nanimatics = 0;

    for (i = 0; i < npc[0].nmaneuvers; i++) {
        npc[0].man[i].animatic = malloc(npc[0].man[i].nanimatics * sizeof (int));
    }

    // specifying the animatcs
    npc[0].man[0].animatic[0] = 1;
    npc[0].man[3].animatic[0] = 2;



	npc[0].nanimatics = 3;
	npc[0].ani = malloc(npc[0].nanimatics * sizeof(Animatic));

	npc[0].aniflags = malloc(npc[0].nanimatics * sizeof(bool)); 
	for (i = 0; i < npc[0].nanimatics; i++) {
		npc[0].aniflags[i] = false;
	}


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


    npc[1].nmaneuvers = 5;
    npc[1].man = malloc(npc[1].nmaneuvers * sizeof (Maneuver)); 


    npc[1].man_func = malloc(npc[1].nmaneuvers * sizeof (void (*)(Position*, Motion*)));

    //registering maneuver functions
    npc[1].man_func[0] = &thrust_forward;
    npc[1].man_func[1] = &thrust_backward;
    npc[1].man_func[2] = &rotate_right;
    npc[1].man_func[3] = &rotate_left;
    npc[1].man_func[4] = &slow_to_stop;

    for (i = 0; i < npc[1].nmaneuvers; i++) {
        npc[1].man[i].on = false;
        npc[1].man[i].state = 1;
    }

    npc[1].man[0].nanimatics = 1;
    npc[1].man[1].nanimatics = 0;
    npc[1].man[2].nanimatics = 0;
    npc[1].man[3].nanimatics = 1;
    npc[1].man[4].nanimatics = 0;

    for (i = 0; i < npc[1].nmaneuvers; i++) {
        npc[1].man[i].animatic = malloc(npc[1].man[i].nanimatics * sizeof (int));
    }

    // specifying the animatcs
    npc[1].man[0].animatic[0] = 1;
    npc[1].man[3].animatic[0] = 2;


	npc[1].nanimatics = 3;
	npc[1].ani = malloc(npc[1].nanimatics * sizeof(Animatic));

	npc[1].aniflags = malloc(npc[1].nanimatics * sizeof(bool)); 
	for (i = 1; i < npc[1].nanimatics; i++) {
		npc[1].aniflags[i] = false;
	}

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
