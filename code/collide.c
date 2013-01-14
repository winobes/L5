#include "motion_math.c"

// collide determines if two Extensions are intersecting using the separating
// axis theorem. If they are interesecting, it returns true and changes
// penetration_vector to the normal of the surface with the smallest
// penetration penetration_scalar is the depth of the penetration.
// Projecting the Extensions so that they are no longer colliding must be done
// outside of the function. This is done so that the two Extensions can share
// the projection in a ship on ship collision, but in ship on wall collisions
// only the ship is projected.
//
// Thank you to Raigan Burns and Mare Sheppard of http://www.metanetsoftware.com/
//  for introducing me to the separating axis theorem
bool collide(Extension a, Extension b, float *penetration_vector, float *penetration_scalar) {

	int i, j;

	float a_max, a_min, b_max, b_min;	//the max and min of the projections on the axes

	float projdot_h; //a place holder to limit calls to projdot
	float penetration_h = 0; //a place holder to simplify calculating the smallest penetration vector
	int penetration_vector_h = 0; //remembers which axis the smallest pennetration came from

	bool scalar_set = false;

	//penetration_vector[0] = 0;
	//penetration_vector[1] = 0;
	*penetration_scalar = 0;

	float *axis[a.nverts+b.nverts];

	for (i = 0; i < a.nverts + b.nverts; i++) {
		axis[i] = malloc(2 * sizeof * axis[i]);
	}

	//calculating the axes normal to the edges of the polygon there are just as many axes as vertices. Many of them will be parallel as in the case of rectangles, but we cannot assume they will be in the general case and it is (I think) at least as resource intensive to remove the parallel cases and reallocate the array as it is to go through with them

	for (i = 0; i < a.nverts; i++) {
		if (i == 0) {
			axis[i][0] = a.vert[0][1] - a.vert[a.nverts - 1][1];
			axis[i][1] = -(a.vert[0][0] - a.vert[a.nverts - 1][0]);
		} else {
			axis[i][0] = a.vert[i][1] - a.vert[i - 1][1];
			axis[i][1] = -(a.vert[i][0] - a.vert[i - 1][0]);
		}
	}

	for (i = a.nverts; i < b.nverts + a.nverts; i++) {
		if (i == a.nverts) {
			axis[i][0] = b.vert[0][1] - b.vert[b.nverts - 1][1];
			axis[i][1] = -(b.vert[0][0] - b.vert[b.nverts - 1][0]);
		} else {
			axis[i][0] = b.vert[i - a.nverts][1] - b.vert[i - a.nverts - 1][1];
			axis[i][1] = -(b.vert[i - a.nverts][0] - b.vert[i - a.nverts - 1][0]);
		}
	}

	for (i = 0; i < a.nverts+b.nverts; i++) {
		normalize(axis[i]);
	}
		
	// getting the min/max for the projection of each object on each axis
	for (j = 0; j < a.nverts + b.nverts; j++) {	
		a_min = a_max = projdot(a.vert[0], axis[j]);

		for (i = 1; i < a.nverts; i++) {
			projdot_h = projdot(a.vert[i], axis[j]);
			if (a_max < projdot_h) {
				a_max = projdot_h;
			}
			if (a_min > projdot_h) {
				a_min = projdot_h;
			}
		}

		b_min = b_max = projdot(b.vert[0], axis[j]);

		for (i = 1; i < b.nverts; i++) {
			projdot_h = projdot(b.vert[i], axis[j]);
			if (b_max < projdot_h) {
				b_max = projdot_h;
			}
			if (b_min > projdot_h) {
				b_min = projdot_h;
			}
		}
		
		if (a_max < b_min || b_max < a_min) {
			for (i = 0; i < a.nverts + b.nverts; i++) {
				free(axis[i]);
			}
			return false;
		} else {
			penetration_h = b_max - a_min;
			if (!scalar_set) {
				*penetration_scalar = penetration_h;
				penetration_vector_h = j;
				scalar_set = true;
			}
			else if (penetration_h < *penetration_scalar) {
				*penetration_scalar = penetration_h;
				penetration_vector_h = j;
			}
		}
	}

	penetration_vector[0] = axis[penetration_vector_h][0];
	penetration_vector[1] = axis[penetration_vector_h][1];

	for (i = 0; i < a.nverts + b.nverts; i++) {
		free(axis[i]);
	}

	return true;
}

