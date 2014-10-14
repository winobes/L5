#include "game_data.h"
#include <stdlib.h> // malloc
#include "graphics.h"
#include "log.h"

Ship* create_triangle_ship() {

    Ship* s = malloc(sizeof(Ship));
    s->shape.center = ORIGIN;
    s->shape.direction = 0;
    s->shape.n_verts = 3;
    s->shape.verts = malloc(sizeof(Point) * s->shape.n_verts);
    s->shape.verts[0].x = 0,  s->shape.verts[0].y = -10;
    s->shape.verts[1].x = 5,  s->shape.verts[1].y =  5;
    s->shape.verts[2].x = -5, s->shape.verts[2].y =  5;

    /* We make sprite_width, sprite height 2*max(|x|) by 2*max(|y's|) 
     * so that the ship's center point is at the center of its bitmap.
     */
    int sprite_width  = 0;
    int sprite_height = 0;
    for (int i = 0; i < s->shape.n_verts; i++) {
        if (sprite_width  < abs(s->shape.verts[i].x))
            sprite_width  = abs(s->shape.verts[i].x);
        if (sprite_height < abs(s->shape.verts[i].y))
            sprite_height = abs(s->shape.verts[i].y);
    }
    sprite_width  *= 2;
    sprite_height *= 2;

    s->sprite = al_create_bitmap(sprite_width, sprite_height); 
    al_set_target_bitmap(s->sprite);
    al_clear_to_color(al_map_rgba(0,0,0,0));
  
    draw_polygon(&s->shape, sprite_width/2, sprite_height/2, al_map_rgb(154, 154, 0));

    return s;

}


Game_Data* init_game_data() {
    Game_Data* g = malloc(sizeof(Game_Data));

    g->display_center = ORIGIN;
    
    g->player = create_triangle_ship();

    g->n_enemies = 0;
    g->enemies = NULL;

    return g;
}

// TODO destroy game data
