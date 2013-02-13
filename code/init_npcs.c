#include "common_def.c"

#ifndef NPC_H
#define NPC_H

NPC *init_npcs(GameState *gs)
{
	int i, j;

	NPC *npc = malloc(gs->nnpcs * sizeof(NPC));

	npc[0].solid = true;
	npc[0].exist = true;
	npc[0].health = 10;
	npc[0].pos.cx = 0;
	npc[0].pos.cy = 0;
	npc[0].pos.cd = PI/2;
	npc[0].pos.room = 0;
	npc[0].bouncy = 100;
	npc[0].gfx_w = 15;
	npc[0].gfx_h = 15;
	npc[0].ai = 1;
	npc[0].mot.dx = 0;
	npc[0].mot.dy = -1;
	npc[0].mot.dd = .05;
	npc[0].mot.turn_speed = .5;
	npc[0].mot.forward_speed = .05;
	npc[0].mot.side_speed = 0;
    npc[0].mot.warp_speed = 0;

	npc[0].sprite = al_create_bitmap(npc[0].gfx_w, npc[0].gfx_h);
	npc[0].spritesheet = al_load_bitmap("gfx/Skimmer1.png");
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

    
   

npc[0].man_func = malloc(npc[0].nmaneuvers * sizeof (void (*)(Position*, Motion*, Maneuver*, int))); 

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
    npc[0].man[1].nanimatics = 1;
    npc[0].man[2].nanimatics = 0;
    npc[0].man[3].nanimatics = 0;
    npc[0].man[4].nanimatics = 0;

    for (i = 0; i < npc[0].nmaneuvers; i++) {
        npc[0].man[i].animatic = malloc(npc[0].man[i].nanimatics * sizeof (int));
    }

    // specifying the animatcs
    npc[0].man[0].animatic[0] = 1;
    npc[0].man[1].animatic[0] = 2;



	npc[0].nanimatics = 3;
	npc[0].ani = malloc(npc[0].nanimatics * sizeof(Animatic));

    npc[0].ani_func = malloc(npc[1].nanimatics * sizeof (void (*)(Animatic*, int)));   

    npc[0].ani_func[0] = &default_on_static;
    npc[0].ani_func[1] = &complete_cycle;
    npc[0].ani_func[2] = &complete_cycle;

    for (i = 0; i < npc[0].nanimatics; i++) {
        npc[0].ani[i].frame = 0;
        npc[0].ani[i].state = 0;
    }

	npc[0].ani[0].timer = 0;
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
	npc[0].ani[0].is_running = true;
	npc[0].ani[0].draw = false;
	npc[0].ani[0].flag = false;
	npc[0].ani[0].tint = al_map_rgba_f(1,1,1,1);

	npc[0].ani[1].timer = 0;
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
	npc[0].ani[1].flag = false;
	npc[0].ani[1].tint = al_map_rgba_f(1,1,1,1);

	npc[0].ani[2].timer = 0;
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
	npc[0].ani[2].flag = false;
	npc[0].ani[2].tint = al_map_rgba_f(1,1,1,1);

    npc[0].nweapons = 1;

    npc[0].weapon = malloc(npc[0].nweapons * sizeof (Weapon)); //TODO FREE

    npc[0].weapon[0].bullet_temp.nmaneuvers = 0;
    npc[0].weapon[0].bullet_temp.nanimatics = 1;
    npc[0].weapon[0].bullet_temp.ext.nverts = 4;

    for (i = 0; i < npc[0].nweapons; i++) {

        npc[0].weapon[i].timer = 0;
        npc[0].weapon[i].fire = false;
        npc[0].weapon[i].bullet_temp.ani = malloc(npc[0].weapon[i].bullet_temp.nanimatics * sizeof (Animatic)); //TODO FREE
        npc[0].weapon[i].bullet_temp.ani_func = malloc(npc[0].weapon[i].bullet_temp.nanimatics * sizeof (void (*)(Animatic*, int)));
        npc[0].weapon[i].bullet_temp.man = malloc(npc[0].weapon[i].bullet_temp.nmaneuvers * sizeof (Maneuver)); //TODO FREE
        npc[0].weapon[i].bullet_temp.man_func = malloc(npc[0].weapon[i].bullet_temp.nanimatics * sizeof (void (*)(Position*, Motion*, Maneuver, int))); //TODO free
	    npc[0].weapon[i].bullet_temp.ext.vert = malloc(npc[0].weapon[i].bullet_temp.ext.nverts * sizeof(float*));
        	npc[0].weapon[i].bullet_temp.ext.x = malloc(npc[0].weapon[i].bullet_temp.ext.nverts * sizeof(float));  //TODO FREE
	        npc[0].weapon[i].bullet_temp.ext.y = malloc(npc[0].weapon[i].bullet_temp.ext.nverts * sizeof(float)); //TODO FREE

	    for (j = 0; j < npc[0].weapon[i].bullet_temp.ext.nverts; j++) {
		    npc[0].weapon[i].bullet_temp.ext.vert[j] = malloc(2 * sizeof(float)); //TODO FREE
	    }

        for (j = 0; j < npc[0].weapon[i].bullet_temp.nmaneuvers; j++) {
            npc[0].weapon[i].bullet_temp.man[j].on = false;
            npc[0].weapon[i].bullet_temp.man[j].has_run = false;
            npc[0].weapon[i].bullet_temp.man[j].state = 0;
        }

        for (j = 0; j < npc[0].weapon[i].bullet_temp.nanimatics; j++) {
            npc[0].weapon[i].bullet_temp.ani[j].source_x = 0;
            npc[0].weapon[i].bullet_temp.ani[j].frame = 0;
            npc[0].weapon[i].bullet_temp.ani[j].scale_x = 1;
            npc[0].weapon[i].bullet_temp.ani[j].scale_y = 1;
            npc[0].weapon[i].bullet_temp.ani[j].state = 0;
            npc[0].weapon[i].bullet_temp.ani[j].tint = al_map_rgba_f(1,1,1,1);
            npc[0].weapon[i].bullet_temp.ani[j].pivot_x = 0;
            npc[0].weapon[i].bullet_temp.ani[j].pivot_y = 0;
            npc[0].weapon[i].bullet_temp.ani[j].flag = false;
            npc[0].weapon[i].bullet_temp.ani[j].is_running = false;
            npc[0].weapon[i].bullet_temp.ani[j].draw = true;
            npc[0].weapon[i].bullet_temp.ani[j].has_run = true;
            npc[0].weapon[i].bullet_temp.ani[j].timer = 0;
            npc[0].weapon[i].bullet_temp.mot.dx = 0;
            npc[0].weapon[i].bullet_temp.mot.dy = 0;
            npc[0].weapon[i].bullet_temp.mot.spd = 0;
            npc[0].weapon[i].bullet_temp.mot.dd = 0;
        }           
    }

    
    npc[0].weapon[0].key = -1;
    npc[0].weapon[0].reload_time = 5;
    npc[0].weapon[0].initial_velocity = 3;
    npc[0].weapon[0].bullet_temp.spritesheet = al_load_bitmap("gfx/bullet1.png");
    npc[0].weapon[0].bullet_temp.pos.cx = 0;
    npc[0].weapon[0].bullet_temp.pos.cy = -17;
    npc[0].weapon[0].bullet_temp.pos.cd = 0;
    npc[0].weapon[0].bullet_temp.mot.forward_speed = 0;
    npc[0].weapon[0].bullet_temp.mot.turn_speed = 0;
    npc[0].weapon[0].bullet_temp.mot.warp_speed = 0;
    npc[0].weapon[0].bullet_temp.mot.side_speed = 0;
    npc[0].weapon[0].bullet_temp.gfx_w = 5;
    npc[0].weapon[0].bullet_temp.gfx_h = 5;
    npc[0].weapon[0].bullet_temp.damage = 1;
    npc[0].weapon[0].bullet_temp.ext.x[0] = -2.5;
    npc[0].weapon[0].bullet_temp.ext.y[0] = -2.5;
    npc[0].weapon[0].bullet_temp.ext.x[1] = 2.5;
    npc[0].weapon[0].bullet_temp.ext.y[1] = -2.5;
    npc[0].weapon[0].bullet_temp.ext.x[2] = 2.5;
    npc[0].weapon[0].bullet_temp.ext.y[2] = 2.5;
    npc[0].weapon[0].bullet_temp.ext.x[3] = -2.5;
    npc[0].weapon[0].bullet_temp.ext.y[3] = 2.5;

    npc[0].weapon[0].bullet_temp.ani[0].is_running = true;


    //maneuver key & animaitcs would go here.
    //man_func would go here.

    npc[0].weapon[0].bullet_temp.ani[0].w = 5;
    npc[0].weapon[0].bullet_temp.ani[0].h = 5;
    npc[0].weapon[0].bullet_temp.ani[0].nframes = 6;
    npc[0].weapon[0].bullet_temp.ani[0].frame_rate = 3;
    npc[0].weapon[0].bullet_temp.ani_func[0] = &default_on_loop;
    npc[0].weapon[0].bullet_temp.ani[0].is_running = true;
    npc[0].weapon[0].bullet_temp.ani[0].destination_x = 0;
    npc[0].weapon[0].bullet_temp.ani[0].destination_y = 0;
    npc[0].weapon[0].bullet_temp.ani[0].frame = 0;


	npc[1].solid = true;
	npc[1].exist = true;
	npc[1].health = 10;
	npc[1].pos.cx = 10;
	npc[1].pos.cy = 10;
	npc[1].pos.cd = PI/2;
	npc[1].pos.room = 0;
	npc[1].bouncy = 100;
	npc[1].gfx_w = 15;
	npc[1].gfx_h = 15;

	npc[1].ai = 1;
	npc[1].mot.dx = 0;
	npc[1].mot.dy = -1;
	npc[1].mot.dd = .05;
	npc[1].mot.turn_speed = .5;
	npc[1].mot.forward_speed = .05;
	npc[1].mot.side_speed = 0;
    npc[1].mot.warp_speed = 0;
	npc[1].sprite = al_create_bitmap(npc[1].gfx_w, npc[1].gfx_h);
	npc[1].spritesheet = al_load_bitmap("gfx/Skimmer1.png");
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


    npc[1].man_func = malloc(npc[1].nmaneuvers * sizeof (void (*)(Position*, Motion*, Maneuver*, int)));

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
    npc[1].man[1].nanimatics = 1;
    npc[1].man[2].nanimatics = 0;
    npc[1].man[3].nanimatics = 0;
    npc[1].man[4].nanimatics = 0;

    for (i = 0; i < npc[1].nmaneuvers; i++) {
        npc[1].man[i].animatic = malloc(npc[1].man[i].nanimatics * sizeof (int));
    }

    // specifying the animatcs
    npc[1].man[0].animatic[0] = 1;
    npc[1].man[1].animatic[0] = 2;


	npc[1].nanimatics = 3;
	npc[1].ani = malloc(npc[1].nanimatics * sizeof(Animatic));

    npc[1].ani_func = malloc(npc[1].nanimatics * sizeof (void (*)(Animatic*, int)));  

    npc[1].ani_func[0] = &default_on_static;
    npc[1].ani_func[1] = &complete_cycle;
    npc[1].ani_func[2] = &complete_cycle;

    for (i = 0; i < npc[1].nanimatics; i++) {
        npc[1].ani[i].frame = 0;
        npc[1].ani[i].state = 0;
    }

    npc[1].ani[0].timer = 0;
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
	npc[1].ani[0].is_running = true;
	npc[1].ani[0].draw = false;
	npc[1].ani[0].flag = false;
	npc[1].ani[0].tint = al_map_rgba_f(1,1,1,1);

    npc[1].ani[1].timer = 0;
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
	npc[1].ani[1].flag = false;
	npc[1].ani[1].tint = al_map_rgba_f(1,1,1,1);

    npc[1].ani[2].timer = 0;
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
	npc[1].ani[2].flag = false;
	npc[1].ani[2].tint = al_map_rgba_f(1,1,1,1);

    npc[1].nweapons = 0;

	return npc;
}

#endif // NPC_H
