#include "common_def.c"
#include "player.c"
#include "init_rooms.c"
#include "init_npcs.c"
#include "init_allegro.c"
#include "update_logic.c"
#include "room_specific_logic.c"
#include "update_graphics.c"
#include "shutdown.c"

int game_loop() {
    bool exit_game = false;
    bool redraw = true;
    int i;

    GameState *gs = malloc(sizeof(GameState));
    init_allegro(gs);

    gs->player = init_player(); // TODO fix the weapon init
    gs->nrooms = 2;
    gs->room = init_rooms(gs);
    gs->nnpcs = 2;
    gs->npc = init_npcs(gs);  
    gs->current_room = 0;

    gs->n_player_bullets = 100;
    gs->player_bullet = malloc(gs->n_player_bullets * sizeof(Bullet));
    for(i = 0; i < gs->n_player_bullets; i++) {
        gs->player_bullet[i].exist = false;
    }
    gs->current_pb = 0;

    gs->n_npc_bullets = 100;
    gs->npc_bullet = malloc(gs->n_npc_bullets * sizeof(Bullet));
    for (i = 0; i < gs->n_npc_bullets; i++) {
        gs->npc_bullet[i].exist = false;
    }
    gs->current_nb = 0;
    gs->font10 = al_load_font("fonts/Roboto-Black.ttf", 10,0);

    bool *keys = malloc(NKEYS * sizeof(bool));
    for (i = 0; i < NKEYS; i++) {
        keys[i] = false;
    }

    ALLEGRO_EVENT event;
    al_start_timer(gs->timer);

    // main update loop
    while(!exit_game) {
        al_wait_for_event(gs->event_queue, &event);
        // TODO check types and inputs
        do_update(&event, keys, &exit_game, &redraw, gs);
        do_room_specific_update(gs);
        do_graphics_update(gs, &redraw);
    }

    // free everything we ever did malloc
    // TODO make individual teardown functions
    free(keys);
    shutdown_game(&gs);
    #ifdef DEBUG
    printf("exiting game_loop\n");
    #endif
    return 0;
}
