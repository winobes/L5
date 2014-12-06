#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "physics.h"
#include <allegro5/allegro.h>

typedef enum {
    SHIP_FORWARD,
    SHIP_BACKWARD,
    SHIP_LEFT,
    SHIP_RIGHT,
    WEAPON_1,
    WEAPON_2,
    N_PLAYER_ACTIONS
} Player_Actions;

typedef enum {
    COMPUTER,
    LOCAL,
    N_PLAYER_TYPES
} Player_Types;

typedef struct Player {
    int type;
    bool actions[N_PLAYER_ACTIONS];
    Polygon ext;
    ALLEGRO_BITMAP* sprite;
    double forward_acc;
    double backward_acc;
    double rotational_acc;
    Vector velocity;
    long max_health;
    long health;
} Player;

typedef struct Game_Data { 
    Point* display_center;
    bool player_controls[N_PLAYER_ACTIONS];
    Player* players;
    size_t n_players;
} Game_Data;

Game_Data* init_game_data();

#endif /* GAME_DATA_H */
