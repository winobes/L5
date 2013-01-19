#ifndef PLAYER_H
#define PLAYER_H


Player *init_player()
{
	Player *player = malloc(sizeof(Player));
	int i;

	player->exist = true;
	player->flying = true;
	player->health = 100;
	player->hit_wall = -1;
	player->nweapons = 1;



	player->bouncy = 500;
	player->pos.cx = 20;
	player->pos.cy = 20;
	player->pos.cd = 0;

	player->ext.nverts = 8;

	player->ext.vert = malloc(player->ext.nverts * sizeof(float*));
	for (i = 0; i < player->ext.nverts; i++) {
		player->ext.vert[i] = malloc(2 * sizeof(player->ext.vert[i]));
	}

	player->ext.x = malloc(player->ext.nverts * sizeof(float));
	player->ext.y = malloc(player->ext.nverts * sizeof(float));

    player->ext.x[0] = -5;
    player->ext.y[0] = -17;

    player->ext.x[1] = 5;
    player->ext.y[1] = -17;

    player->ext.x[2] = 16;
    player->ext.y[2] = -3;

    player->ext.x[3] = 17;
    player->ext.y[3] = 9;

    player->ext.x[4] = 9;
    player->ext.y[4] = 17;

    player->ext.x[5] = -9;
    player->ext.y[5] = 17;

    player->ext.x[6] = -17;
    player->ext.y[6] = 9;

    player->ext.x[7] = -16;
    player->ext.y[7] = -3;

	player->mot.dx = 0;
	player->mot.dy = 0;
	player->mot.dd = .03;
    player->mot.forward_speed = 0.03;
	player->mot.turn_speed = 0.5;
	player->mot.warp_speed = 5.0;
	player->mot.side_speed = 0.2;


    player->nmaneuvers = 8;
    player->man = malloc(player->nmaneuvers * sizeof (Maneuver));

    player->man_func = malloc(player->nmaneuvers * sizeof (void (*)(Position*, Motion*)));

    //registering maneuver functions
    player->man_func[0] = &thrust_forward;
    player->man_func[1] = &thrust_backward;
    player->man_func[2] = &rotate_right;
    player->man_func[3] = &rotate_left;
    // [2] and [3] should really be the rotate_*_thrust_forward functions.... for troubleshooting these are easier.
    player->man_func[4] = &thrust_forward_warpspeed;
    player->man_func[5] = &thrust_right;
    player->man_func[6] = &thrust_left;
    player->man_func[7] = &slow_to_stop;

    //registering keys to maneuvers
    player->man[0].key = UP;
    player->man[1].key = DOWN;
    player->man[2].key = RIGHT;
    player->man[3].key = LEFT;
    player->man[4].key = KEYW;
    player->man[5].key = KEYD;
    player->man[6].key = KEYA;
    player->man[7].key = KEYS;


    for (i = 0; i < player->nmaneuvers; i++) {
        player->man[i].on = false;
        player->man[i].state = 1;
    }

    // how many animatics are registered to each maneuver
    player->man[0].nanimatics = 3;
    player->man[1].nanimatics = 2;
    player->man[2].nanimatics = 1;
    player->man[3].nanimatics = 1;
    player->man[4].nanimatics = 3;
    player->man[5].nanimatics = 0;
    player->man[6].nanimatics = 0;
    player->man[7].nanimatics = 0; // stop doesn't have any animatics registered because it operates by manipulating other maneuvers.

    for (i = 0; i < player->nmaneuvers; i++) {
        player->man[i].animatic = malloc(player->man[i].nanimatics * sizeof (int));
    }

    // specifying the animatcs
    player->man[0].animatic[0] = 2;
    player->man[0].animatic[1] = 3;
    player->man[0].animatic[2] = 4;

    player->man[1].animatic[0] = 5;
    player->man[1].animatic[1] = 6;

    player->man[2].animatic[0] = 3;

    player->man[3].animatic[0] = 4;

    player->man[4].animatic[0] = 2;
    player->man[4].animatic[1] = 3;
    player->man[4].animatic[2] = 4;


	player->gfx_w = 100;
	player->gfx_h = 100;

	player->sprite = al_create_bitmap(player->gfx_w, player->gfx_h);
	player->spritesheet = al_load_bitmap("gfx/FireflySpritesheet.png");
	player->nanimatics = 7;
	player->ani = malloc(player->nanimatics * sizeof(Animatic));

	player->aniflags = malloc(player->nanimatics * sizeof(bool));
	for (i = 0; i < player->nanimatics; i++) {
		player->aniflags[i] = false;
	}

    //the main ship sprite
	player->ani[0].source_x = 0;
	player->ani[0].source_y = 0;
	player->ani[0].w = 35;
	player->ani[0].h = 35;
	player->ani[0].pivot_x = 0;
	player->ani[0].pivot_y = 0;
	player->ani[0].destination_x = 33;
	player->ani[0].destination_y = 33;
	player->ani[0].scale_x = 1;
	player->ani[0].scale_y = 1;
	player->ani[0].is_running = false;
	player->ani[0].draw = false;
	player->ani[0].type = 1;
	player->ani[0].flag = 0;
	player->ani[0].tint = al_map_rgba_f(1,1,1,1);

	player->ani[1].source_x = 0;
	player->ani[1].source_y = 35;
	player->ani[1].w = 13;
	player->ani[1].h = 10;
	player->ani[1].pivot_x = 0;
	player->ani[1].pivot_y = 0;
	player->ani[1].destination_x = 32 + 10;
	player->ani[1].destination_y = 32 + 25;
	player->ani[1].scale_x = 1;
	player->ani[1].scale_y = 1;
	player->ani[1].is_running = false;
	player->ani[1].draw = false;
	player->ani[1].nframes = 4;
	player->ani[1].frame_rate = 15;
	player->ani[1].type = 1;
	player->ani[1].flag = 1;
	player->ani[1].tint = al_map_rgba_f(1,1,1,1);

    //main forward thruster
	player->ani[2].source_x = 0;
	player->ani[2].source_y = 45;
	player->ani[2].w = 13;
	player->ani[2].h = 26;
	player->ani[2].pivot_x = 0;
	player->ani[2].pivot_y = 0;
	player->ani[2].destination_x = 32 + 10;
	player->ani[2].destination_y = 32 + 25;
	player->ani[2].scale_x = 1;
	player->ani[2].scale_y = 1;
	player->ani[2].is_running = false;
	player->ani[2].draw = false;
	player->ani[2].nframes = 1;
	player->ani[2].frame_rate = 15;
	player->ani[2].type = 1;
	player->ani[2].flag = 2;
	player->ani[2].tint = al_map_rgba_f(1,1,1,1);

    //right forward thruster
	player->ani[3].source_x = 0;
	player->ani[3].source_y = 71;
	player->ani[3].w = 8;
	player->ani[3].h = 42;
	player->ani[3].pivot_x = 0;
	player->ani[3].pivot_y = 0;
	player->ani[3].destination_x = 32 + 0;
	player->ani[3].destination_y = 32 + 9;
	player->ani[3].scale_x = 1;
	player->ani[3].scale_y = 1;
	player->ani[3].is_running = false;
	player->ani[3].draw = false;
	player->ani[3].nframes = 1;
	player->ani[3].frame_rate = 15;
	player->ani[3].type = 1;
	player->ani[3].flag = 3;
	player->ani[3].tint = al_map_rgba_f(1,1,1,1);

    //left forward thruster
	player->ani[4].source_x = 0;
	player->ani[4].source_y = 113;
	player->ani[4].w = 8;
	player->ani[4].h = 42;
	player->ani[4].pivot_x = 0;
	player->ani[4].pivot_y = 0;
	player->ani[4].destination_x = 32 + 25;
	player->ani[4].destination_y = 32 + 9;
	player->ani[4].scale_x = 1;
	player->ani[4].scale_y = 1;
	player->ani[4].is_running = false;
	player->ani[4].draw = false;
	player->ani[4].nframes = 1;
	player->ani[4].frame_rate = 15;
	player->ani[4].type = 1;
	player->ani[4].flag = 4;
	player->ani[4].tint = al_map_rgba_f(1,1,1,1);

    //right back thruster
	player->ani[5].source_x = 0;
	player->ani[5].source_y = 155;
	player->ani[5].w = 7;
	player->ani[5].h = 33;
	player->ani[5].pivot_x = 0;
	player->ani[5].pivot_y = 0;
	player->ani[5].destination_x = 32 + 2;
	player->ani[5].destination_y = 32 - 10;
	player->ani[5].scale_x = 1;
	player->ani[5].scale_y = 1;
	player->ani[5].is_running = false;
	player->ani[5].draw = false;
	player->ani[5].nframes = 4;
	player->ani[5].frame_rate = 15;
	player->ani[5].type = 1;
	player->ani[5].flag = 5;
	player->ani[5].tint = al_map_rgba_f(1,1,1,1);

    //left back thruster
	player->ani[6].source_x = 0;
	player->ani[6].source_y = 188;
	player->ani[6].w = 7;
	player->ani[6].h = 33;
	player->ani[6].pivot_x = 0;
	player->ani[6].pivot_y = 0;
	player->ani[6].destination_x = 32 + 26;
	player->ani[6].destination_y = 32 - 10;
	player->ani[6].scale_x = 1;
	player->ani[6].scale_y = 1;
	player->ani[6].is_running = false;
	player->ani[6].draw = false;
	player->ani[6].nframes = 4;
	player->ani[6].frame_rate = 15;
	player->ani[6].type = 1;
	player->ani[6].flag = 6;
	player->ani[6].tint = al_map_rgba_f(1,1,1,1);

	player->weapon.nactive = 25;
	player->weapon.key = LCTRL;
	player->weapon.spritesheet = al_load_bitmap("gfx/bullet1.png");
	player->weapon.w = 5;
	player->weapon.h = 5;
	player->weapon.origin_x = 0;
	player->weapon.origin_y = -17;
	player->weapon.movement_type = 1;
	player->weapon.damage = 10;
	player->weapon.current = 0;
	player->weapon.reload_timer = 0;
	player->weapon.reload_time = 10;
	player->weapon.nframes = 6;
	player->weapon.frame_rate = 5;

	player->weapon.sprite = malloc (player->weapon.nactive * sizeof(player->weapon.sprite));

	player->weapon.d = malloc(player->weapon.nactive * sizeof(player->weapon.d));

	player->weapon.x = malloc(player->weapon.nactive * sizeof(player->weapon.x));

	player->weapon.y = malloc(player->weapon.nactive * sizeof(player->weapon.y));

	player->weapon.dx = malloc(player->weapon.nactive * sizeof(player->weapon.dx));

	player->weapon.dy = malloc(player->weapon.nactive * sizeof(player->weapon.dy));

	player->weapon.source_x = malloc(player->weapon.nactive * sizeof(player->weapon.source_x));

	player->weapon.timer = malloc(player->weapon.nactive * sizeof(player->weapon.timer));

	player->weapon.exists = malloc(player->weapon.nactive * sizeof(player->weapon.exists));

	for (i = 0; i < player->weapon.nactive; i++) {
		player->weapon.d[i] = 0;
		player->weapon.source_x[i] = 0;
		player->weapon.timer[i] = 0;
		player->weapon.exists[i] = false;
	}

	player->weapon.ext.nverts = 1;
	player->weapon.ext.vert = malloc(player->weapon.ext.nverts * sizeof(float*));
	for (i = 0; i < player->weapon.ext.nverts; i++) {
		player->weapon.ext.vert[i] = malloc(2 * sizeof(player->weapon.ext.vert[i]));
	}

	return player;
}

#endif // PLAYER_H
