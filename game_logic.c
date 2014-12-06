#include "game_logic.h"

void update_game(Game_Data* g, Settings t) {

    Player *p = NULL;
    Ship *s = NULL;

    for (int i = 0; i < g->n_players; i++) {

        p = &g->players[i];
        s = &p->ship;

        // update actions
        switch(p->type) {
        case LOCAL:
            for (int j = 0; j < N_PLAYER_ACTIONS; j++)
                p->actions[j] = g->keyboard[t.player_controls[j]];
            break;
        case COMPUTER:
            // TODO make some AI
            break;
        }

        // update direction
        if (p->actions[SHIP_RIGHT])
            s->dir += s->base->acc;
        if (p->actions[SHIP_LEFT])
            s->dir -= s->base->acc;

        // update velocitity
        if (i == 0)
        if (p->actions[SHIP_FORWARD])
            vector_add_to(&s->vel, (Vector) {s->dir, s->base->acc});
        if (p->actions[SHIP_BACKWARD])
            vector_add_to(&s->vel, (Vector) {s->dir, -s->base->acc});

        // update position
        move_by(&s->loc, s->vel);
        
    }
}
