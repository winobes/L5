#include "common_def.c"
#include "player.c"


#ifndef AI1_H
#define AI1_H


// create a truncated cone in the given extension
//
// INPUT
//     game state to access npc state and properties
//     ext - the extension to create
//     left - leftmost angle from forward on the npc
//     right - rightmost angle of cone  
//     minsr - minimum sight range
//     maxsr - maximum sight range
void make_cone(NPC *npc,
				Extension *ext,
				float left,
				float right,
				int minsr,
				int maxsr)
{
	ext->vert[0][0] = minsr * sin(left) + npc->pos.cx;
	ext->vert[0][1] = minsr * cos(left + PI) + npc->pos.cy;

	ext->vert[1][0] = maxsr * sin(left) + npc->pos.cx;
	ext->vert[1][1] = maxsr * cos(left + PI) + npc->pos.cy;

	ext->vert[2][0] = maxsr * sin(right) + npc->pos.cx;
	ext->vert[2][1] = maxsr * cos(right + PI) + npc->pos.cy;

	ext->vert[3][0] = minsr * sin(right) + npc->pos.cx;
	ext->vert[3][1] = minsr * cos(right + PI) + npc->pos.cy;
}


// setup truncated vision cone to determine ai movement and following behavior
//
// cone starts a distance away from npc to avoid overshooting
//
// INPUT :
//     game state to access npc state and properties
//     vision left centre
//     vision centre
//     vision right centre
//     dimension of the space
//     minimum sight range
//     maximum sight range
void setup_vision(NPC *npc,
					Extension *vlc,
					Extension *vc,
					Extension *vrc,
					int ndims,
					int minsr,
					int maxsr)
{
	int i;

    vlc->nverts = 4;
	vlc->vert = malloc(vlc->nverts * sizeof(float*));
	for (i = 0; i < vlc->nverts; i++) {
		vlc->vert[i] = malloc(ndims * sizeof(vlc->vert[i]));
	}
	vrc->nverts = 4;
	vrc->vert = malloc(vrc->nverts * sizeof(float*));
	for (i = 0; i < vrc->nverts; i++) {
		vrc->vert[i] = malloc(ndims * sizeof(vrc->vert[i]));
	}
	vc->nverts = 4;
	vc->vert = malloc(vc->nverts * sizeof(float*));
	for (i = 0; i < vc->nverts; i++) {
		vc->vert[i] = malloc(ndims * sizeof(vc->vert[i]));
	}

	// leftmost angle of vision from the forward direction of npc unit
    float lvis = npc->pos.cd - PI/2;
    // angle divding left and centre vision
    float lcvis = npc->pos.cd - PI/8;
    // angle divding centre and right vision
	float rcvis = npc->pos.cd + PI/8;
    // rightmost angle
    float rvis = npc->pos.cd + PI/2;

	make_cone(npc,
				vlc,
				lvis,
				lcvis,
				minsr,
				maxsr);
	make_cone(npc,
				vc,
				lcvis,
				rcvis,
				minsr,
				maxsr);
	make_cone(npc,
				vrc,
				rcvis,
				rvis,
				minsr,
				maxsr);
}


void teardown_vision(Extension *visLeftCentre,
					Extension *visCentre,
					Extension *visRightCentre)
{
	int i;
	for(i = 0; i < visCentre->nverts; i++) {
		free(visLeftCentre->vert[i]);
		free(visRightCentre->vert[i]);
		free(visCentre->vert[i]);
	}
	free(visLeftCentre->vert);
	free(visRightCentre->vert);
	free(visCentre->vert);
}


void ai1 (NPC *npc, Extension target, int current_room) {


	Extension visLeftCentre;
	Extension visRightCentre;
	Extension visCentre;

	bool sighted = false;

	float penetration_scalar;
	float penetration_vector[2];


	setup_vision(npc,
				&visLeftCentre,
				&visCentre,
				&visRightCentre,
				2,
				150,
				200);

	if (npc->pos.room == current_room) {
		// going after the player if it is ahead
		if (collide(visLeftCentre, target, penetration_vector, &penetration_scalar)) {
            rotate_left(&npc->pos, &npc->mot, npc->man, 2);
			sighted = true;
		} else if (collide(visCentre, target, penetration_vector, &penetration_scalar)) {
			// turning to get the player ahead if it is in sight
            thrust_forward(&npc->pos, &npc->mot, npc->man, 0);
			sighted = true;
		} else if (collide(visRightCentre, target, penetration_vector, &penetration_scalar)) {
            rotate_right(&npc->pos, &npc->mot, npc->man, 1);
			sighted = true;
		}
	}

	if ((!sighted) && (sqrt(npc->mot.dx*npc->mot.dx + npc->mot.dy*npc->mot.dy) > .05)) {
		slow_to_stop(&npc->pos, &npc->mot, npc->man, 4);
	}
	teardown_vision(&visLeftCentre, &visCentre, &visRightCentre);
}

#endif // AI1_H
