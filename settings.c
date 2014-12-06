#include "settings.h"

Settings default_settings() {
    Settings t;
    t.player_controls[SHIP_FORWARD]  = ALLEGRO_KEY_UP;
    t.player_controls[SHIP_BACKWARD] = ALLEGRO_KEY_DOWN;
    t.player_controls[SHIP_LEFT]     = ALLEGRO_KEY_LEFT;
    t.player_controls[SHIP_RIGHT]    = ALLEGRO_KEY_RIGHT;
    t.player_controls[WEAPON_1]      = ALLEGRO_KEY_SPACE;
    t.player_controls[WEAPON_2]      = ALLEGRO_KEY_X;
    return t;
}
