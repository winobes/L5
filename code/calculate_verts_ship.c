#include "common_def.c"

void calculate_verts_ship(int shape, struct Extension* ext, float cx, float cy, float w, float h, float d) {

/*calculates the vertices of an object based on it's shape, center position, and direction. Shape flags are as follows:

1 - RECTANGLE

*/

float diangle = atan(w/h);
float ray = sqrt((w*w) + (h*h))/2;

	switch (shape) {

	case RECTANGLE:
		ext->vert[0][0] = ray * sin(d - diangle) + cx;
		ext->vert[0][1] = ray * cos(d - diangle + ALLEGRO_PI) + cy;

		ext->vert[1][0] = ray * sin(d + diangle) + cx;
		ext->vert[1][1] = ray * cos(d + diangle + ALLEGRO_PI) + cy;

		ext->vert[2][0] = ray * sin(d - diangle + ALLEGRO_PI) + cx;
		ext->vert[2][1] = ray * cos(d - diangle) + cy;

		ext->vert[3][0] = ray * sin(d + diangle + ALLEGRO_PI) + cx;
		ext->vert[3][1] = ray * cos(d + diangle) + cy;
	break;

	//TODO fix this case 
	case OCTAGON:
		diangle = atan(-4/-16);
		ray = sqrt((-4*-4) + (-16*-16))/2;
		ext->vert[0][0] = ray * sin(d - diangle) + cx;
		ext->vert[0][1] = ray * cos(d - diangle) + cy;

		diangle = atan(-4/-16);
		ext->vert[1][0] = ray * sin(d - diangle) + cx;
		ext->vert[1][1] = ray * cos(d - diangle) + cy;

		diangle = atan(17/-3);
		ray = sqrt((-17*-17) + (-3*-3))/2;
		ext->vert[2][0] = ray * sin(d - diangle) + cx;
		ext->vert[2][1] = ray * cos(d - diangle) + cy;

		diangle = atan(-16/-3);
		ext->vert[7][0] = ray * sin(d - diangle) + cx;
		ext->vert[7][1] = ray * cos(d - diangle) + cy;

		diangle = atan(17/9);
		ray = sqrt((17*17) + (9*9))/2;
		ext->vert[3][0] = ray * sin(d - diangle) + cx;
		ext->vert[3][1] = ray * cos(d - diangle) + cy;

		diangle = atan(-16/9);
		ext->vert[6][0] = ray * sin(d - diangle) + cx;
		ext->vert[6][1] = ray * cos(d - diangle) + cy;

		diangle = atan(9/18);
		ray = sqrt((9*9) + (18*18))/2;
		ext->vert[4][0] = ray * sin(d - diangle) + cx;
		ext->vert[4][1] = ray * cos(d - diangle) + cy;

		diangle = atan(-9/18);
		ext->vert[5][0] = ray * sin(d - diangle) + cx;
		ext->vert[5][1] = ray * cos(d - diangle) + cy;

	}
}
