#include "core.h"
#include "log.h"
#include "error.h"
#include "game_data.h"
#include "graphics.h"
#include "game_logic.h"

void game_loop(Engine_Core *core) {

    log_msg(LOADING, "Loading default settings.");
    Settings t = load_default_settings();
    log_msg(LOADING, "Initializing game data.");
    Game_Data* g = init_game_data();

    bool exit_game = false;
    bool redraw = true;

    ALLEGRO_EVENT event;
    al_start_timer(core->timer);

    log_msg(LOADING, "Starting game loop.");
    while(!exit_game) {

        al_wait_for_event(core->queue, &event);
        switch(event.type) {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            process_key(event.keyboard.keycode, true, t, g);
            break;
        case ALLEGRO_EVENT_KEY_UP:
            process_key(event.keyboard.keycode, true, t, g);
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            exit_game = true;
            break;
        }

        if (redraw && al_event_queue_is_empty(core->queue)) {
            update_graphics(core->display, g);
            redraw = false;
        }
    }

}


void init_allegro(Engine_Core *core) {
    log_msg(LOADING, "Initializing core components...");

    core->timer = NULL;
    core->queue = NULL;
    core->display = NULL;

    log_msg(LOADING, "Initializing Allegro...");
    if (al_init()) 
        log_version("Allegro is version ", al_get_allegro_version(), 45);
    else 
        error("Allegro failed to Initialize.");

    /* Native Dialog */
    log_msg(LOADING, "Initializing Allegro Native Dialog Addon...");
    if (al_init_native_dialog_addon())
        log_version("Native Dialog Addon", al_get_allegro_native_dialog_version());
    else
        log_msg(WARNING, "Allegro Native Dialog Addon failed to initialize.");
    
    /* Event queue */
    log_msg(LOADING, "Creating event queue...");
    core->queue = al_create_event_queue(); 
    if (!core->queue) 
        error("Failed to create Allegro event queue.");

    /* Keyboard */
    log_msg(LOADING, "Installing keyboard...");
    if (al_install_keyboard()) {
        log_msg(LOADING, "Registering keyboard to event queue.");
        al_register_event_source(core->queue, al_get_keyboard_event_source());
    } else 
        log_msg(WARNING, "Could not find keyboard.");

    /* Timer */
    log_msg(LOADING, "Creating Timer...");
    core->timer = al_create_timer(ALLEGRO_BPS_TO_SECS(BPS));
    if (core->timer) { 
        log_msg(LOADING, "Set to %i BPS.", BPS);
        log_msg(LOADING, "Registering timer to event queue.");
        al_register_event_source(core->queue, al_get_timer_event_source(core->timer));
    } else
        error("Could not start game timer.");

    /* Display */
    log_msg(LOADING, "Creating display (%i X %i)...", DISPLAY_WIDTH, DISPLAY_HEIGHT);
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    core->display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if(core->display) { 
        log_msg(LOADING, "Registering display to event queue.");
        al_register_event_source(core->queue,
        al_get_display_event_source(core->display));
    } else
        error("Could not create Allegro display.");

}


void game_shutdown(Engine_Core *core) {

    log_msg(LOADING, "Shutting down core components...");

    if (core->timer != NULL) {
        log_msg(LOADING, "Destroying timer");
        al_destroy_timer(core->timer);
    }

    if (core->display != NULL) {
        log_msg(LOADING, "Destroying display");
        al_destroy_display(core->display);
    }

    if (core->queue != NULL) {
        log_msg(LOADING, "Destroying event queue");
        al_destroy_event_queue(core->queue);
    }

    log_msg(LOADING, "Uninstalling Allegro");
    al_uninstall_system();

}
