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
void make_cone(GameState *gs,
				Extension *ext,
				float left,
				float right,
				int minsr,
				int maxsr)
{
	ext->vert[0][0] = minsr * sin(left) + gs->npc->pos.cx;
	ext->vert[0][1] = minsr * cos(left + PI) + gs->npc->pos.cy;

	ext->vert[1][0] = maxsr * sin(left) + gs->npc->pos.cx;
	ext->vert[1][1] = maxsr * cos(left + PI) + gs->npc->pos.cy;

	ext->vert[2][0] = maxsr * sin(right) + gs->npc->pos.cx;
	ext->vert[2][1] = maxsr * cos(right + PI) + gs->npc->pos.cy;

	ext->vert[3][0] = minsr * sin(right) + gs->npc->pos.cx;
	ext->vert[3][1] = minsr * cos(right + PI) + gs->npc->pos.cy;
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
void setup_vision(GameState *gs,
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
    float lvis = gs->npc->pos.cd - PI/2;
    // angle divding left and centre vision
    float lcvis = gs->npc->pos.cd - PI/8;
    // angle divding centre and right vision
	float rcvis = gs->npc->pos.cd + PI/8;
    // rightmost angle
    float rvis = gs->npc->pos.cd + PI/2;

	make_cone(gs,
				vlc,
				lvis,
				lcvis,
				minsr,
				maxsr);
	make_cone(gs,
				vc,
				lcvis,
				rcvis,
				minsr,
				maxsr);
	make_cone(gs,
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


void ai1 (GameState *gs, int npcid) {

	NPC *npc = &gs->npc[npcid];
	Player *target = gs->player;

	Extension visLeftCentre;
	Extension visRightCentre;
	Extension visCentre;

	bool sighted = false;

	float penetration_scalar;
	float penetration_vector[2];

	int i;

	setup_vision(gs,
				&visLeftCentre,
				&visCentre,
				&visRightCentre,
				2,
				150,
				200);

	for (i = 0; i < 5; i++) {
		npc->keys[i] = false;
	}

	if (npc[0].room == gs->current_room) {
		// going after the player if it is ahead
		if (collide(visLeftCentre, target->ext, penetration_vector, &penetration_scalar)) {
			npc->keys[LEFT] = true;
			sighted = true;
		} else if (collide(visCentre, target->ext, penetration_vector, &penetration_scalar)) {
			// turning to get the player ahead if it is in sight
			npc->keys[UP] = true;
			sighted = true;
		} else if (collide(visRightCentre, target->ext, penetration_vector, &penetration_scalar)) {
			npc->keys[RIGHT] = true;
			sighted = true;
		}
	}

	if (sighted == false)  {
		stopping(&npc->pos, &npc->mot, npc->keys);
	}
	teardown_vision(&visLeftCentre, &visCentre, &visRightCentre);
}

#endif // AI1_H
