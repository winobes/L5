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


/*
	player->ext.dis[0] = player->ext.dis[1] = sqrt((4*4) + (17*17));
	player->ext.dis[2] = player->ext.dis[7] = sqrt((16*16) + (3*3));
	player->ext.dis[3] = player->ext.dis[6] = sqrt((17*17) + (9*9));
	player->ext.dis[4] = player->ext.dis[5] = sqrt((9*9) + (17*17));

	player->ext.ang[0] = -atanf((float)5/(float)17);
	player->ext.ang[1] = atanf((float)5/(float)17);
	player->ext.ang[2] = atanf((float)16/(float)3);
	player->ext.ang[3] = atanf((float)9/(float)17) + ALLEGRO_PI/2; 
	player->ext.ang[4] = atanf((float)17/(float)9) + ALLEGRO_PI/2; 
	player->ext.ang[5] = -atanf((float)17/(float)9) - ALLEGRO_PI/2;
	player->ext.ang[6] = -atanf((float)9/(float)17) - ALLEGRO_PI/2;
	player->ext.ang[7] = -atanf((float)16/(float)3);*/

    for (i = 0; i < 8; i++) {
 //       printf("ang[%i] = %f\n", i, player->ext.ang[i]);
    }


	player->mot.dx = 0;
	player->mot.dy = 0;
	player->mot.dd = .03;
	player->mot.ddxy = .03;

	player->gfx_w = 100;
	player->gfx_h = 100;

	player->sprite = al_create_bitmap(player->gfx_w, player->gfx_h);
	player->spritesheet = al_load_bitmap("gfx/FireflySpritesheet.png");
	player->nanimatics = 7;
	player->ani = malloc(player->nanimatics * sizeof(struct Animatic));

	player->aniflags = malloc(player->nanimatics * sizeof(bool));
	for (i = 0; i < player->nanimatics; i++) {
		player->aniflags[i] = false;
	}

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
	player->ani[0].draw = true;
	player->ani[0].type = 0;
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
