void proj(float *v, float axis[2]) {

v[0] = (dot(v, axis) / (axis[0]*axis[0] + axis[1]*axis[1])) * axis[0];
v[1] = (dot(v, axis) / (axis[0]*axis[0] + axis[1]*axis[1])) * axis[1];

}
