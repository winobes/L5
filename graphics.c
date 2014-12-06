#include "graphics.h"
#include <allegro5/allegro_primitives.h>

#include "game_data.h" // GAME_DATA
#include "physics.h" // Point
#include "core.h" // DISPLAY_WIDTH, HEIGHT

ALLEGRO_BITMAP* create_polygon_sprite(Polygon shape, 
                                      ALLEGRO_COLOR color) {

    int width = 0, height = 0;
    for (int i = 0; i < shape.n_verts; i++) {
        if (width  < abs(shape.verts[i].x))
            width  = abs(shape.verts[i].x);
        if (height < abs(shape.verts[i].y))
            height = abs(shape.verts[i].y);
    }
    width  *= 2;
    height *= 2;

    ALLEGRO_BITMAP* sprite = al_create_bitmap(width, height); 
    al_set_target_bitmap(sprite);
    al_clear_to_color(al_map_rgba(0,0,0,0));
    for (int i = 0; i < shape.n_verts; i++) {
        int j = i + 1;
        if (j == shape.n_verts) 
            j = 0;
        al_draw_line(shape.verts[i].x + width/2,
                     shape.verts[i].y + height/2,
                     shape.verts[j].x + width/2,
                     shape.verts[j].y + height/2,
                     color, 0);
    }
    
    return sprite;

}

void draw_ship(Ship s, Point display_center) {
    int x, y; // location of the upper left-hand corner of the bitmap on the display
    int sprite_width  = al_get_bitmap_width(s.sprite);
    int sprite_height = al_get_bitmap_height(s.sprite);
    x = (DISPLAY_WIDTH)/2  - display_center.x + s.shape.center.x;
    y = (DISPLAY_HEIGHT)/2 - display_center.y + s.shape.center.y;
    al_draw_rotated_bitmap(s.sprite, sprite_width/2, sprite_height/2, 
                           x, y, s.shape.direction, 0);
}

void update_graphics(ALLEGRO_DISPLAY* display, const Game_Data* g) {
    al_set_target_backbuffer(display);

    al_clear_to_color(al_map_rgb(50,50,50)); // draw background

    draw_ship(g->player, g->display_center);
    for (int i = 0; i < g->n_enemies; i++)
        draw_ship(g->enemies[i], g->display_center);

    al_flip_display();
}

