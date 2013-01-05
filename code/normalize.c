void normalize(float* v) {

	float normalizer;

	normalizer = sqrt(v[0]*v[0] + v[1]*v[1]);

	v[0] /= normalizer;
	v[1] /= normalizer;
}
