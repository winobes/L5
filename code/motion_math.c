#include "common_def.c"

#ifndef MOTION_MATH_H
#define MOTION_MATH_H


float dot(float a[2], float b[2]) {
	return a[0]*b[0] + a[1]*b[1];
} 


void proj(float *v, float axis[2]) {
	v[0] = (dot(v, axis) / (axis[0]*axis[0] + axis[1]*axis[1])) * axis[0];
	v[1] = (dot(v, axis) / (axis[0]*axis[0] + axis[1]*axis[1])) * axis[1];
}


// (a projected onto b) dot b
// projects vertex onto axis and dots the result with axis.
// Used to determine if there is intersection on a particular axis.
float projdot(float vertex[2], float axis[2]) {
	float proj[2];
	proj[0] = (dot(vertex, axis) / (axis[0]*axis[0] + axis[1]*axis[1])) * axis[0];
	proj[1] = (dot(vertex, axis) / (axis[0]*axis[0] + axis[1]*axis[1])) * axis[1];
	return dot(proj, axis);
}


void normalize(float* v) {
	float normalizer = sqrt(v[0]*v[0] + v[1]*v[1]);
	v[0] /= normalizer;
	v[1] /= normalizer;
}


void calculate_speed(float dy, float dx, float* s) {
	*s = sqrt(dy*dy+dx*dx);
}


// reflect actually ususes the projection vector found by collide to reflect a
// velocity off of a particular surface of an imobile Extension (e.g. a wall)
void reflect(float *x, float *y, float N[2]) {
	float V[2] = {*x, *y};
	float R[2] = {0, 0};	
	float Mdot = dot(V, N);
	R[0] = V[0] - 2*Mdot * N[0];
	R[1] = V[1] - 2*Mdot * N[1];
	*x = R[0];
	*y = R[1];
}


// calculates vertices based on the shape flag, direction, and position.
// The NCP and Player types have approprate variables.
//
// calculates the position of the vertices given their vector position
// (dis,ang) relative to some point (cx,cy) on the subject and the subject's
// rotational direction (d)
void calculate_verts(Extension* ext, float cx, float cy, float d) {

	int i;
    float dis;
    
	for (i = 0; i < ext->nverts; i++) {

        dis = sqrt((ext->y[i]*ext->y[i]) + (ext->x[i]*ext->x[i]));


        if (ext->x[i] > 0) {
            ext->vert[i][0] = dis * cos(d + atan(ext->y[i]/ext->x[i])) + cx;
            ext->vert[i][1] = dis * sin(d + atan(ext->y[i]/ext->x[i])) + cy;
        }
        
        else if (ext->x[i] < 0) {
            ext->vert[i][0] = dis * -cos(d + atan(ext->y[i]/ext->x[i])) + cx;
            ext->vert[i][1] = dis * -sin(d + atan(ext->y[i]/ext->x[i])) + cy;
        }

        else { //ext->x[i] ==0
            if (ext->y[i] > 0) {
                ext->vert[0][0] = dis * -sin(d) + cx;
                ext->vert[0][1] = dis * cos(d) + cy;
            }
            else if (ext->y[i] < 0) {
                ext->vert[0][0] = dis * sin(d) + cx;
                ext->vert[0][1] = dis * -cos(d) + cy;

            }
            else { // ext->y[i] = 0
                ext->vert[i][0] = cx;  
                ext->vert[i][1] = cy;
            }
        }


    }
}


// calculates the three remaining vertices based on vert[0], width, height,
// and direction. Assumes that the wall is rectangular. May have to add a shape
// flag as in the above.
void calculate_verts_wall(Extension* ext, float w, float h, float d) {
	//vert[0] must already be set.
	ext->vert[1][0] = w * sin(PI/2 - d) + ext->vert[0][0];
	ext->vert[1][1] = w * cos(PI/2 - d) + ext->vert[0][1];
	ext->vert[3][0] = ext->vert[0][0] - h * sin(d);
	ext->vert[3][1] = h * cos(d) + ext->vert[0][1];
	ext->vert[2][0] = w * sin(PI/2 - d) + ext->vert[3][0];
	ext->vert[2][1] = w * cos(PI/2 - d) + ext->vert[3][1];
}


// objects may bounce upon colliding with one another
//
// bounce is used mostly for the collision of two ships (e.g. player with npc).
// The resulting collision assumes that the two ships are perfectly round
// (note however that it should only be called *after* a collision has been
//  detected collide and the Extensions have been appropriately projected away
//  from one another)
//
// Thank you to Thomas Smid http://www.plasmaphysics.org.uk/ for his
// explaination of the phisics in this function 
void bounce(float m1,
			float m2,
			float R,
			float x1,
			float y1,
			float x2,
			float y2,
			float *vx1,
			float *vy1,
			float *vx2,
			float *vy2)
{
	float  m21,dvx2,a,x21,y21,vx21,vy21,fy21,sign,vx_cm,vy_cm;
	m21=m2/m1;
	x21=x2-x1;
	y21=y2-y1;
	vx21=*vx2-*vx1;
	vy21=*vy2-*vy1;

	vx_cm = (m1**vx1+m2**vx2)/(m1+m2) ;
	vy_cm = (m1**vy1+m2**vy2)/(m1+m2) ;   

	//     *** return old velocities if balls are not approaching ***
	if ( (vx21*x21 + vy21*y21) >= 0) return;

	//     *** I have inserted the following statements to avoid a zero divide; 
	//         (for single precision calculations, 
	//          1.0E-12 should be replaced by a larger value). **************  
  
	fy21=1.0E-6*fabs(y21);                            
	if ( fabs(x21)<fy21 ) {  
		if (x21<0) { sign=-1; } else { sign=1;}  
			x21=fy21*sign; 
	} 

	//     ***  update velocities ***
	a=y21/x21;
	dvx2= -2*(vx21 +a*vy21)/((1+a*a)*(1+m21)) ;
	*vx2=*vx2+dvx2;
	*vy2=*vy2+a*dvx2;
	*vx1=*vx1-m21*dvx2;
	*vy1=*vy1-a*m21*dvx2;

	//     ***  velocity correction for inelastic collisions ***
	*vx1=(*vx1-vx_cm)*R + vx_cm;
	*vy1=(*vy1-vy_cm)*R + vy_cm;
	*vx2=(*vx2-vx_cm)*R + vx_cm;
	*vy2=(*vy2-vy_cm)*R + vy_cm;

	return;
}


// angle of current velocity
float get_velangle(float dx, float dy)
{
	float velangle;
	float normaldx = dx / sqrt(dx*dx + dy*dy);
	if (dy < 0) {
		velangle = asin(normaldx);
		if (dx < 0) {
			velangle += 2*PI;
		}
	} else {
		velangle = PI - asin(normaldx);
	}
	return velangle;
}





#endif // MOTION_MATH_H
