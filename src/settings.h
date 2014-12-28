#ifndef SETTINGS_H
#define SETTINGS_H

#include <allegro5/allegro.h>
#include "game_data.h"

typedef struct Settings {
    int player_controls[N_PLAYER_ACTIONS]; 
} Settings;

Settings default_settings();

#endif /* SETTINGS_H */
