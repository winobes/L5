float projdot(float vertex[2], float axis[2]) {
//projects vertex onto axis and dots the result with axis. Used to determine if there is intersection on a particular axis.
	float proj[2];

	proj[0] = (dot(vertex, axis) / (axis[0]*axis[0] + axis[1]*axis[1])) * axis[0];
	proj[1] = (dot(vertex, axis) / (axis[0]*axis[0] + axis[1]*axis[1])) * axis[1];

	return dot(proj, axis);

}
