#include "game_data.h"
#include <stdlib.h>

#include "graphics.h"
#include "log.h"
#include "physics.h" //create_regular_polygon
#include <math.h> // sin, cos

Ship create_ship(Point location, 
                 Polygon shape, 
                 ALLEGRO_BITMAP* sprite,
                 long max_health) {

    Ship s;
    s.max_health = max_health;
    s.sprite = sprite;
    s.shape = shape;
    s.shape.center = location;

    return s;
}

Game_Data* init_game_data() {
    Game_Data* g = malloc(sizeof(Game_Data));

    g->display_center = ORIGIN;
   
    Polygon shape = create_regular_polygon(4, 100);
    g->player = create_ship(ORIGIN, shape, 
            create_polygon_sprite(shape, al_map_rgb(154,154,0)), 1000);
                            
    g->n_enemies = 3;
    g->enemies = malloc(sizeof(Ship) * g->n_enemies);
    shape = create_regular_polygon(5, 50);
    g->enemies[0] = create_ship((Point){200,-100}, 
            shape, 
            create_polygon_sprite(shape, al_map_rgb(154,0,154)), 
            1000);
    shape = create_regular_polygon(5, 300);
    g->enemies[1] = create_ship((Point){-300,-250}, 
            shape, 
            create_polygon_sprite(shape, al_map_rgb(154,0,154)), 
            1000);
    shape = create_regular_polygon(5, 5);
    g->enemies[2] = create_ship((Point){50,100}, 
            shape, 
            create_polygon_sprite(shape, al_map_rgb(154,0,154)), 
            1000);

    return g;
}

// TODO destroy game data
