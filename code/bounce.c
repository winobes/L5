
/* Thank you to Thomas Smid http://www.plasmaphysics.org.uk/ for his explaination of the phisics in this function*/ 

void bounce(float m1, float m2, float R, float x1, float y1, float x2, float y2, float *vx1, float *vy1, float *vx2, float *vy2) {

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
