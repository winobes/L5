#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>

#include "common_def.c"


#include "dotproduct.c"
#include "projection.c"
#include "bounce.c" // bounce is used mostly for the collision of two ships (e.g. player with npc). The resulting collision assumes that the two ships are perfectly round (note however that it should only be called *after* a collision has been detected collide and the Extensions have been appropriately projected away from one another)
#include "reflect.c" //reflect actually ususes the projection vector found by collide to reflect a velocity off of a particular surface of an imobile Extension (e.g. a wall)
#include "projdot.c" // (a projected onto b) dot b
#include "calculate_speed.c"
#include "normalize.c" //converts a vector to its normal by pointer
#include "collide.c" //determines if two Extensions are intersecting using the separating axis theorem. If they are interesecting, it returns true and changes penetration_vector to the normal of the surface with the smallest penetration penetration_scalar is the depth of the penetration. Projecting the Extensions so that they are no longer colliding must be done outside of the function. This is done so that the two Extensions can share the projection in a ship on ship collision, but in ship on wall collisions only the ship is projected.
#include "calculate_verts_ship.c" //calculates vertices based on the shape flag, direction, and position. the NCP and Player types have approprate variables.
#include "calculate_verts_wall.c" // calculates the three remaining vertices based on vert[0], width, height, and direction. Assumes that the wall is rectangular. May have to add a shape flag as in the above.
#include "update_background.c"
#include "ai1.c"
#include "animatic1.c"
#include "game_loop.c"


int main (int argc, char* argv[]) {

	game_loop();

	return 0;
}
