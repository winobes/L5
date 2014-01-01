#include "common_def.c"

#ifndef SHUTDOWN_H
#define SHUTDOWN_H

void free_extension(Extension ext) {
    int i;
    for (i = 0; i < ext.nverts; i++) {
        free(ext.vert[i]);
    }
    free(ext.vert);
    if (ext.y != NULL)
        free(ext.y);
    if (ext.x != NULL)
        free(ext.x);
    return;
}

void free_bullet(Bullet bullet) {
    int i;
    free_extension(bullet.ext);
    if (bullet.ani != NULL)
        free(bullet.ani);
    if (bullet.man != NULL)
        free(bullet.man);
    for (i = 0; i < bullet.nmaneuvers; i++) {
        free(bullet.man[i].animatic);
    }
    if (bullet.man_func != NULL)
        free(bullet.man_func);
    if (bullet.ani_func != NULL)
        free(bullet.ani_func);
    return;
}


void shutdown_game(GameState** gs) {

    int i, j;

    // player

    #ifdef DEBUG
    printf("free player\n");
    #endif

    free_extension((*gs)->player->ext);
    free((*gs)->player->man_func);
    free((*gs)->player->man);
    free((*gs)->player->ani);
    free((*gs)->player->ani_func);

    al_destroy_bitmap((*gs)->player->spritesheet);
    (*gs)->player->spritesheet = NULL;
    al_destroy_bitmap((*gs)->player->sprite);
    (*gs)->player->sprite = NULL;
    for(j = 0; j < (*gs)->player->nweapons; j++) {
        free_bullet((*gs)->player->weapon[j].bullet_temp);
    }
    
    free((*gs)->player->weapon);
    free((*gs)->player);


    #ifdef DEBUG
    printf("free rooms\n");
    #endif

    // rooms
    for (i = 0; i < (*gs)->nrooms; i++) {
        for (j = 0; j < (*gs)->room[i]->nwalls; j++) {
            free_extension((*gs)->room[i]->wall[j]->ext);
            al_destroy_bitmap((*gs)->room[i]->wall[j]->sprite);
            (*gs)->room[i]->wall[j]->sprite = NULL;
            free((*gs)->room[i]->wall[j]);
        }
        for (j = 0; j < (*gs)->room[i]->nbackgrounds; j++) {
            al_destroy_bitmap((*gs)->room[i]->background[j].background_image);
            (*gs)->room[i]->background[j].background_image = NULL;
        }
        if ((*gs)->room[i]->nbackgrounds > 0) {
            free((*gs)->room[i]->background);			
        }
        free((*gs)->room[i]->wall);
        free((*gs)->room[i]);
    }
    free((*gs)->room);

    #ifdef DEBUG
    printf("free npcs\n");
    #endif

    // npcs
    for (i = 0; i < (*gs)->nnpcs; i++) {
        free_extension((*gs)->npc[i].ext);
        free((*gs)->npc[i].ani);
        free((*gs)->npc[i].ani_func);
        free((*gs)->npc[i].man_func);
        free((*gs)->npc[i].man);
        for(j = 0; j < (*gs)->npc[i].nweapons; j++) {
            free_bullet((*gs)->npc[i].weapon[j].bullet_temp);
        }
        if ((*gs)->npc[i].weapon != NULL) {
            free((*gs)->npc[i].weapon);
        }
    }
    free((*gs)->npc);

    #ifdef DEBUG
    printf("free game state\n");
    #endif

    // GameState
    al_destroy_font((*gs)->font10);
    (*gs)->font10 = NULL;

    for (i = 0; i < (*gs)->n_player_bullets; i++) {
        if ((*gs)->player_bullet[i].exist) {
            free_bullet((*gs)->player_bullet[i]);
        }
    }
    free((*gs)->player_bullet);


    for (i = 0; i < (*gs)->n_npc_bullets; i++) {
    if ((*gs)->npc_bullet[i].exist) {
        free_bullet((*gs)->npc_bullet[i]);
    }
    }
    free((*gs)->npc_bullet);


	#ifdef DEBUG
	printf("in shutdown\n");
	#endif

	if ((*gs)->timer) {
		#ifdef DEBUG
		printf("destroying timer\n");
		#endif
		al_destroy_timer((*gs)->timer);
		(*gs)->timer = NULL;
	}

	if ((*gs)->display) {
		#ifdef DEBUG
		printf("destroying display\n");
		#endif
		al_destroy_display((*gs)->display);
		(*gs)->display = NULL;
	}

	if ((*gs)->event_queue) {
		#ifdef DEBUG
		printf("destroying event queue\n");
		#endif
		al_destroy_event_queue((*gs)->event_queue);
		(*gs)->event_queue = NULL;
	}

    free(*gs);

}

#endif // SHUTDOWN_H
