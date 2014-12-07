#include "game_logic.h"
#include "log.h"

bool check_collision(Polygon shape_a, Vector pos_a, double dir_a,
                     Polygon shape_b, Vector pos_b, double dir_b,
                     Vector *collision_vec) {

    // create the absolute-position polygons to check against
    Vector verts_a[shape_a.n_verts]; 
    Polygon a = { shape_a.n_verts, verts_a};
    for (int i = 0; i < a.n_verts; i++)
        a.verts[i] = shape_a.verts[i];
    Vector verts_b[shape_b.n_verts]; 
    Polygon b = { shape_b.n_verts, verts_b};
    for (int i = 0; i < b.n_verts; i++)
        b.verts[i] = shape_b.verts[i];

    // move them into position
    polygon_translate(&a, dir_a, pos_a);
    polygon_translate(&b, dir_b, pos_b);

    return polygon_intersect(a, b, collision_vec);

}


Vector reflect(Vector v, Vector axis) {
    double a = (axis.x * axis.x - axis.y * axis.y) / (axis.x * axis.x + axis.y * axis.y);
    double b = 2 * axis.x * axis.y / (axis.x * axis.x + axis.y * axis.y);
    double x = a * (v.x - 

void update_game(Game_Data* g, Settings t) {


    Vector collision_vec;

    for (int i = 0; i < g->n_players; i++) {

        Ship *s1 = &g->players[i].ship;
        for (int j = i+1; j < g -> n_players; j++) {
            Ship *s2 = &g->players[j].ship;
            if (check_collision(s1->base->shape, s1->pos, s1->dir,
                s2->base->shape, s2->pos, s2->dir, &collision_vec)) {
                s1->pos = vec_add(s1->pos, collision_vec);
                s1->vel = reflect(s1->vel, collision_vec);
                /*vector_add_to(&s1->vel, penetration);*/
            }
        }

        Player *p = &g->players[i];

        // update actions
        switch(p->type) {
        case LOCAL:
            for (int j = 0; j < N_PLAYER_ACTIONS; j++)
                p->actions[j] = g->keyboard[t.player_controls[j]];
            break;
        case COMPUTER:
            // TODO make some AI
            break;
        }

        // update ship direction
        if (p->actions[SHIP_RIGHT])
            p->ship.dir += p->ship.base->acc;
        if (p->actions[SHIP_LEFT])
            p->ship.dir -= p->ship.base->acc;

        // update ship velocitity
        if (p->actions[SHIP_FORWARD])
            p->ship.vel = vec_add(p->ship.vel, polar_to_vec(p->ship.dir, p->ship.base->acc));
        if (p->actions[SHIP_BACKWARD])
            p->ship.vel = vec_add(p->ship.vel, polar_to_vec(p->ship.dir, -p->ship.base->acc));

        // update ship position
        p->ship.pos = vec_add(p->ship.pos, p->ship.vel);
        
    }
}


