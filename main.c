#include "core.h"

int main (int argc, char* argv[]) {

        Engine_Core core; 

        init_allegro(&core); 
        game_loop(&core);
	game_shutdown(&core);

	return 0;
}
