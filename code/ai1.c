#include "player.c"

void ai1 (NPC *npc, Player *target) {

	struct Extension visLeftCentre;
	struct Extension visRightCentre;
	struct Extension visCentre;

	float normaldx;
	float velangle;

	bool sighted = false;

	int i;
	float penetration_scalar;
	float penetration_vector[2];

	visLeftCentre.nverts = 3;
	visLeftCentre.vert = malloc(3 * sizeof(float*));
	for (i = 0; i < 3; i++) {
		visLeftCentre.vert[i] = malloc(2 * sizeof(visLeftCentre.vert[i]));
	}
	visRightCentre.nverts = 3;
	visRightCentre.vert = malloc(3 * sizeof(float*));
	for (i = 0; i < 3; i++) {
		visRightCentre.vert[i] = malloc(2 * sizeof(visRightCentre.vert[i]));
	}
	visCentre.nverts = 3;
	visCentre.vert = malloc(3 * sizeof(float*));
	for (i = 0; i < 3; i++) {
		visCentre.vert[i] = malloc(2 * sizeof(visCentre.vert[i]));
	}

	visLeftCentre.vert[0][0] = npc->cx;
	visLeftCentre.vert[0][1] = npc->cy;
	visCentre.vert[0][0] = visLeftCentre.vert[0][0];
	visCentre.vert[0][1] = visLeftCentre.vert[0][1];
	visRightCentre.vert[0][0] = visLeftCentre.vert[0][0];
	visRightCentre.vert[0][1] = visLeftCentre.vert[0][1];

	visLeftCentre.vert[1][0] = 300 * sin(npc->d - ALLEGRO_PI/2) + npc->cx;
	visLeftCentre.vert[1][1] = 300 * cos(npc->d  - ALLEGRO_PI/2 + ALLEGRO_PI) + npc->cy;

	visLeftCentre.vert[2][0] = 300 * sin(npc->d - ALLEGRO_PI/8) + npc->cx;
	visLeftCentre.vert[2][1] = 300 * cos(npc->d - ALLEGRO_PI/8 + ALLEGRO_PI) + npc->cy;

	visCentre.vert[1][0] = visLeftCentre.vert[2][0];
	visCentre.vert[1][1] = visLeftCentre.vert[2][1];

	visCentre.vert[2][0] = 300 * sin(npc->d + ALLEGRO_PI/8) + npc->cx;
	visCentre.vert[2][1] = 300 * cos(npc->d + ALLEGRO_PI/8 + ALLEGRO_PI) + npc->cy;

	visRightCentre.vert[1][0] = visCentre.vert[2][0];
	visRightCentre.vert[1][1] = visCentre.vert[2][1];

	visRightCentre.vert[2][0] = 300 * sin(npc->d + ALLEGRO_PI/2) + npc->cx;
	visRightCentre.vert[2][1] = 300 * cos(npc->d + ALLEGRO_PI/2 + ALLEGRO_PI) + npc->cy;

	for (i = 0; i < 5; i++) {
		npc->keys[i] = false;
	}

	if (npc[0].room == current_room) {
	 // going after the player if it is ahead
		if (collide(visLeftCentre, target->ext, penetration_vector, &penetration_scalar)) {
			npc->keys[LEFT] = true;
			sighted = true;
		}
	// turning to get the player ahead if it is in sight
		else if (collide(visCentre, target->ext, penetration_vector, &penetration_scalar)) {
			npc->keys[UP] = true;
			sighted = true;
		}

		else if (collide(visRightCentre, target->ext, penetration_vector, &penetration_scalar)) {
			npc->keys[RIGHT] = true;
			sighted = true;
		}

	}

	// stopping if the player is not in sight

	if (sighted == false)  {

		normaldx = npc->dx / sqrt(npc->dx*npc->dx + npc->dy*npc->dy);
		if (npc->dy < 0) {
			velangle = asin(normaldx);
			if (npc->dx < 0) {
				velangle += 2*ALLEGRO_PI;
			}
		}
		else {
			velangle = ALLEGRO_PI - asin(normaldx);
		}

		if (sqrt(npc->dx*npc->dx + npc->dy*npc->dy) > .05) {
			if(velangle - npc->d < ALLEGRO_PI/8 && velangle - npc->d > - ALLEGRO_PI/8) {
				npc->keys[DOWN] = true;
			}

			else if(asin(normaldx) - npc->d < ALLEGRO_PI) {
				npc->keys[LEFT] = true;
			}

			else if(asin(normaldx) - npc->d > ALLEGRO_PI) {
				npc->keys[RIGHT] = true;
			}
		}
	}
}
