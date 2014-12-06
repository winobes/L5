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

typedef struct Ship_Template {
    Polygon shape;
    ALLEGRO_BITMAP *sprite;
    long health;
    double acc;
} Ship_Template;

typedef struct Ship {
    Ship_Template* base;
    Point loc;
    Vector vel;
    double dir;
    long health;
} Ship;

typedef struct Player {
    Ship ship;
    int type;
    bool actions[N_PLAYER_ACTIONS];
} Player;

typedef struct Game_Data { 
    Point* display_center;
    bool player_controls[N_PLAYER_ACTIONS];
    Player* players;
    size_t n_players;
    Ship_Template* ships;
    size_t n_ships;
} Game_Data;

Game_Data* init_game_data();

#endif /* GAME_DATA_H */
