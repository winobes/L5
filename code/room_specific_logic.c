#include "common_def.c"

#ifndef ROOM_SPECIFIC_H
#define ROOM_SPECIFIC_H

void do_room_specific_update(GameState *gs)
{
	if (gs->current_room == 0) {
		if (gs->player->hit_wall != 18) {
			gs->room[0]->wall[18]->hot = true;
		}

		if (gs->player->hit_wall != 19) {
			gs->room[0]->wall[19]->hot = true;
		}

		if (gs->player->hit_wall == 18 && gs->room[0]->wall[18]->hot) {
			gs->current_room = 1;
			gs->player->pos.cx += gs->room[1]->wall[12]->ext.vert[0][0] - gs->room[0]->wall[18]->ext.vert[0][0];
			gs->player->pos.cy += gs->room[1]->wall[12]->ext.vert[0][1] - gs->room[0]->wall[18]->ext.vert[0][1];
			gs->room[1]->wall[12]->hot = false;
		}

		if (gs->player->hit_wall == 19 && gs->room[0]->wall[19]->hot) {
			gs->current_room = 1;
			gs->player->pos.cx += gs->room[1]->wall[13]->ext.vert[0][0] - gs->room[0]->wall[19]->ext.vert[0][0];
			gs->player->pos.cy += gs->room[1]->wall[13]->ext.vert[0][1] - gs->room[0]->wall[19]->ext.vert[0][1];
			gs->room[1]->wall[13]->hot = false;
		}
	} else if (gs->current_room == 1) {
		if (gs->player->hit_wall != 12) {
			gs->room[1]->wall[12]->hot = true;
		}

		if (gs->player->hit_wall != 13) {
			gs->room[1]->wall[13]->hot = true;
		}

		if(gs->player->hit_wall == 12 && gs->room[1]->wall[12]->hot) {
			gs->current_room = 0;
			gs->player->pos.cx += gs->room[0]->wall[18]->ext.vert[0][0] - gs->room[1]->wall[12]->ext.vert[0][0];
			gs->player->pos.cy += gs->room[0]->wall[18]->ext.vert[0][1] - gs->room[1]->wall[12]->ext.vert[0][1];
			gs->room[0]->wall[18]->hot = false;
		}

		if(gs->player->hit_wall == 13 && gs->room[1]->wall[13]->hot) {
			gs->current_room = 0;
			gs->player->pos.cx += gs->room[0]->wall[19]->ext.vert[0][0] - gs->room[1]->wall[13]->ext.vert[0][0];
			gs->player->pos.cy += gs->room[0]->wall[19]->ext.vert[0][1] - gs->room[1]->wall[13]->ext.vert[0][1];
			gs->room[0]->wall[19]->hot = false;
		}
	}
}

#endif // ROOM_SPECIFIC_H