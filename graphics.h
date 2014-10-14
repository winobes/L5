#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <allegro5/allegro.h>
#include "game_data.h"
#include "physics.h"

void draw_polygon(Polygon* s, float dx, float dy, ALLEGRO_COLOR color);

void update_graphics(ALLEGRO_DISPLAY* display, const Game_Data* g);

void draw_ship(Ship* s, Point display_center);

#endif /* GRAPHICS_H */
