#include "common_def.c"

void calculate_verts_ship(int shape, struct Extension* ext, float cx, float cy, float w, float h, float d) {

/*calculates the vertices of an object based on it's shape, center position, and direction. Shape flags are as follows:

1 - rectangular

*/

float diangle = atan(w/h);
float ray = sqrt((w*w) + (h*h))/2;

	switch (shape) {

		case 1:
			ext->vert[0][0] = ray * sin(d - diangle) + cx;
			ext->vert[0][1] = ray * cos(d - diangle + ALLEGRO_PI) + cy;

			ext->vert[1][0] = ray * sin(d + diangle) + cx;
			ext->vert[1][1] = ray * cos(d + diangle + ALLEGRO_PI) + cy;

			ext->vert[2][0] = ray * sin(d - diangle + ALLEGRO_PI) + cx;
			ext->vert[2][1] = ray * cos(d - diangle) + cy;

			ext->vert[3][0] = ray * sin(d + diangle + ALLEGRO_PI) + cx;
			ext->vert[3][1] = ray * cos(d + diangle) + cy;

		break;
	}
}
