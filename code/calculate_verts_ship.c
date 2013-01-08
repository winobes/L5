#include "common_def.c"

void calculate_verts_ship(struct Extension* ext, float cx, float cy, float d) {

	/*calculates the position of the veritces given their vector position (dis,ang) relative to some point (cx,cy) on the subject and the subject's rotational direction (d)*/

	int i;

	for (i = 0; i < ext->nverts; i++) {
		ext->vert[i][0] = ext->dis[i] * sin(d + ext->ang[i]) + cx;
		ext->vert[i][1] = ext->dis[i] * -cos(d + ext->ang[i]) + cy;
		//the y axis is inverted
	}


}
