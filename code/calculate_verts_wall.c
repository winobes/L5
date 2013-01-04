void calculate_verts_wall(struct Extension* ext, float w, float h, float d) {

	//vert[0] must already be set.

	ext->vert[1][0] = w * sin(ALLEGRO_PI/2 - d) + ext->vert[0][0];
	ext->vert[1][1] = w * cos(ALLEGRO_PI/2 - d) + ext->vert[0][1];

	ext->vert[3][0] = ext->vert[0][0] - h * sin(d);
	ext->vert[3][1] = h * cos(d) + ext->vert[0][1];

	ext->vert[2][0] = w * sin(ALLEGRO_PI/2 - d) + ext->vert[3][0];
	ext->vert[2][1] = w * cos(ALLEGRO_PI/2 - d) + ext->vert[3][1];

}
