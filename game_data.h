#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "physics.h"
#include <allegro5/allegro.h>

typedef struct Ship {
    Polygon shape;
    ALLEGRO_BITMAP* sprite;
    long max_health;
    long health;
} Ship;

typedef struct Game_Data { 
    Point display_center;
    Ship* player;
    Ship* enemies;
    int n_enemies;
} Game_Data;

Game_Data* init_game_data();
#endif /* GAME_LOGIC_H */
