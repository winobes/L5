#include "game_logic.h"

void update_game(Game_Data* g, Settings t) {

    // update actions
    for (int i = 0; i < g->n_players; i++) {
        switch(g->players[i].type) {
        case LOCAL:
            for (int j = 0; j < N_PLAYER_ACTIONS; j++)
                g->players[i].actions[j] = g->keyboard[t.player_controls[j]];
            break;
        case COMPUTER:
            // TODO
            break;
        }
    }

    // change velocities

    // change positions
}
