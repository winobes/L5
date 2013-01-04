void reflect(float *x, float *y, float N[2]) {

	float V[2] = {*x, *y};
	float R[2] = {0, 0};	

	float Mdot = dot(V, N);

	R[0] = V[0] - 2*Mdot * N[0];
	R[1] = V[1] - 2*Mdot * N[1];

	*x = R[0];
	*y = R[1];

}
