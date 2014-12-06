#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <allegro5/allegro.h>
#include "game_data.h"
#include "physics.h"

ALLEGRO_BITMAP* create_polygon_sprite(Polygon shape, ALLEGRO_COLOR color);

void update_graphics(ALLEGRO_DISPLAY* display, const Game_Data* g);

void draw_ship(Ship s, Point display_center);

#endif /* GRAPHICS_H */
