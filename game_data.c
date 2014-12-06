#include "game_data.h"
#include <stdlib.h>

#include "graphics.h"
#include "log.h"
#include "physics.h" //create_regular_polygon
#include <math.h> // sin, cos

Player create_player(Point location, Ship_Template* ship, int type) {

    Player player;

    player.ship.base = ship;
    player.ship.loc = location;
    player.ship.vel = (Vector) {0, 0};
    player.ship.dir = 0;
    player.ship.health = ship->health;

    player.type = type;
    for (int i = 0; i < N_PLAYER_ACTIONS; i++)
        player.actions[i] = false;

    return player;
}

Game_Data* init_game_data() {

    Game_Data* g = malloc(sizeof(Game_Data));

    g->n_ships = 2;
    g->ships = malloc(sizeof(Ship_Template) * g->n_ships);
    g->ships[0].shape = create_regular_polygon(5,50);
    g->ships[0].sprite = create_polygon_sprite(g->ships[0].shape, al_map_rgb(154,0,154));
    g->ships[0].health = 100;
    g->ships[0].acc = 10;
    g->ships[1].shape = create_regular_polygon(3,50);
    g->ships[1].sprite = create_polygon_sprite(g->ships[1].shape, al_map_rgb(154,154,0));
    g->ships[1].health = 200;
    g->ships[1].acc = 10;

    g->n_players = 3;
    g->players = malloc(sizeof(Player) * g->n_players);
    g->players[0] = create_player((Point) {0,0}, &g->ships[1], LOCAL);
    g->players[1] = create_player((Point) {100,-50}, &g->ships[0], COMPUTER);
    g->players[2] = create_player((Point) {-150, 100}, &g->ships[0], COMPUTER);

    g->display_center = &g->players[0].ship.loc;

    for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
        g->keyboard[i] = false;

    return g;
}

// TODO destroy game data
