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
    N_ACTIONS
} Ship_Actions;

typedef struct Ship {
    Polygon shape;
    ALLEGRO_BITMAP* sprite;
    double forward_thrust;
    double backward_thrust;
    double rotational_thrust;
    Vector velocity;
    long max_health;
    long health;
} Ship;

typedef struct Game_Data { 
    Point display_center;
    Ship player;
    bool player_controls[N_ACTIONS];
    Ship* enemies;
    size_t n_enemies;
} Game_Data;

Game_Data* init_game_data();

#endif /* GAME_DATA_H */
