#include "game_data.h"
#include <stdlib.h>
#include "graphics.h"
#include "log.h"
#include "physics.h" //create_regular_polygon

Player create_player(Vector location, Ship_Template* ship, int type) {

    Player player;

    player.ship.base = ship;
    player.ship.pos = location;
    player.ship.vel = (Vector) {0, 0};
    player.ship.dir = 0;
    player.ship.health = ship->health;

    player.type = type;
    for (int i = 0; i < N_PLAYER_ACTIONS; i++)
        player.actions[i] = false;

    return player;
}


void destroy_player(Player *p) {
    // nothing malloc'd in player for now...
}


void destroy_ship_template(Ship_Template s) {
    free(s.shape.verts);
    al_destroy_bitmap(s.sprite);
}


Game_Data* init_game_data() {

    Game_Data* g = malloc(sizeof(Game_Data));

    g->n_ships = 3;
    g->ships = malloc(sizeof(Ship_Template) * g->n_ships);
    g->ships[0].shape = create_regular_polygon(5,50);
    g->ships[0].sprite = create_polygon_sprite(g->ships[0].shape, al_map_rgb(154,0,154));
    g->ships[0].health = 100;
    g->ships[0].acc = 0.1;
    g->ships[1].shape = create_regular_polygon(3,50);
    g->ships[1].sprite = create_polygon_sprite(g->ships[1].shape, al_map_rgb(154,154,0));
    g->ships[1].health = 200;
    g->ships[1].acc = 0.1;
    g->ships[2].shape = create_regular_polygon(3,30);
    g->ships[2].sprite = al_load_bitmap("../assets/ships/Firefly.png");
    g->ships[2].health = 200;
    g->ships[2].acc = 0.1;

    g->n_players = 4;
    g->players = malloc(sizeof(Player) * g->n_players);
    g->players[0] = create_player((Vector) {0,0}, &g->ships[2], LOCAL);
    g->players[1] = create_player((Vector) {100,-50}, &g->ships[1], COMPUTER);
    g->players[2] = create_player((Vector) {-150, 100}, &g->ships[0], COMPUTER);
    g->players[3] = create_player((Vector) {-10, 20}, &g->ships[0], COMPUTER);

    g->display_center = &g->players[0].ship.pos;

    for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
        g->keyboard[i] = false;

    return g;
}


void destroy_game_data(Game_Data *g) {
    for (int i = 0; i < g->n_ships; i++)
        destroy_ship_template(g->ships[i]);
    free(g->players);
    free(g->ships);
}
