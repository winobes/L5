#include "game_data.h"
#include <stdlib.h>

#include "graphics.h"
#include "log.h"
#include "physics.h" //create_regular_polygon
#include <math.h> // sin, cos

Player create_player(Point location, 
                 Polygon ext, 
                 ALLEGRO_COLOR color,
                 long max_health) {

    Player s;
    s.max_health = max_health;
    s.sprite = create_polygon_sprite(ext, color);
    s.ext = ext;
    s.ext.center = location;

    return s;
}

Game_Data* init_game_data() {
    Game_Data* g = malloc(sizeof(Game_Data));

    g->n_players = 4;
    g->players = malloc(sizeof(Player) * g->n_players);
    g->players[0] = create_player(ORIGIN, create_regular_polygon(4, 100),
            al_map_rgb(154,154,0), 1000);
    g->players[1] = create_player((Point){200,-100},  create_regular_polygon(5, 50),
            al_map_rgb(154,0,154), 1000);
    g->players[2] = create_player((Point){-300,-250}, create_regular_polygon(5, 300),
            al_map_rgb(154,0,154), 1000);
    g->players[3] = create_player((Point){50,100}, create_regular_polygon(5, 5),
            al_map_rgb(154,0,154), 1000);

    g->display_center = &g->players[0].ext.center;

    return g;
}

// TODO destroy game data
