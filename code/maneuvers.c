void thrust_forward (Position *pos, Motion *mot, Maneuver *man, int current)
{

    mot->dx += mot->forward_speed * cos(pos->cd - PI/2);
    mot->dy += mot->forward_speed * sin(pos->cd - PI/2);

    //persists for one frame unless player is holding the key 

return;
}


void thrust_backward (Position *pos, Motion *mot, Maneuver *man, int current)
{

    //persists for one frame unless player is holding the key
    //may want to add a backward_speed to the mot type at some point
	    mot->dx -= mot->forward_speed * cos(pos->cd - PI/2);
	    mot->dy -= mot->forward_speed * sin(pos->cd - PI/2);

    return;
}


void rotate_right (Position *pos, Motion *mot, Maneuver *man, int current)
{
    //persists for one frame unless player is holding the key
    pos->cd += mot->turn_speed * mot->dd*PI;

    return;
}

void rotate_left (Position *pos, Motion *mot, Maneuver *man, int current)
{

    //persists for one frame unless player is holding the key
    pos->cd -= mot->turn_speed * mot->dd*PI;

    return;
}


void rotate_right_thrust_forward (Position *pos, Motion *mot, Maneuver *man, int current)
{

    //persists for one frame unless player is holding the key
    pos->cd += mot->turn_speed * mot->dd*PI;

    if(!man[0].on) {
    // man[0] is expected to be forward_thrust. This clause prevents the player from glitching an extra forward boost with the left, right, forward combination
	    mot->dx += mot->forward_speed/2 * cos(pos->cd - PI/2);
	    mot->dy += mot->forward_speed/2 * sin(pos->cd - PI/2);
    }

    return;
}


void rotate_left_thrust_forward (Position *pos, Motion *mot, Maneuver *man, int current)
{

    //persists for one frame unless player is holding the key
    pos->cd -= mot->turn_speed * mot->dd*PI;
	
    if(!man[0].on) {
    // man[0] is expected to be forward_thrust. This clause prevents the player from glitching an extra boost with the left, right, forward combination
	    mot->dx += mot->forward_speed/2 * cos(pos->cd - PI/2);
	    mot->dy += mot->forward_speed/2 * sin(pos->cd - PI/2);
    }

    return;
}


void thrust_forward_warpspeed (Position *pos, Motion *mot, Maneuver *man, int current)
{

    //persists for one frame unless player is holding the key
    mot->dx += mot->forward_speed * mot->warp_speed * cos(pos->cd - PI/2);
    mot->dy += mot->forward_speed * mot->warp_speed * sin(pos->cd - PI/2);
    
    return;
}

void thrust_right (Position *pos, Motion *mot, Maneuver *man, int current)
{

    //persists for one frame unless player is holding the key
    mot->dx -= mot->side_speed * mot->forward_speed * cos(pos->cd - PI);
    mot->dy -= mot->side_speed * mot->forward_speed * sin(pos->cd - PI);

    return;
}



void thrust_left (Position *pos, Motion *mot, Maneuver *man, int current)
{

   //persists for one frame unless player is holding the key
    mot->dx += mot->side_speed * mot->forward_speed * cos(pos->cd - PI);
    mot->dy += mot->side_speed * mot->forward_speed * sin(pos->cd - PI);
    return;
}

void slow_to_stop (Position *pos, Motion *mot, Maneuver *man, int current)
{

    man[2].on = false;
    man[3].on = false;
    man[4].on = false;

    float normaldx = mot->dx / sqrt(mot->dx*mot->dx + mot->dy*mot->dy);
    float velangle = get_velangle(mot->dx, mot->dy);
    // angle delta
    float angled = velangle - pos->cd;
    if (sqrt(mot->dx*mot->dx + mot->dy*mot->dy) > .05) {
	
	    if((-PI/8 < angled) && (angled < PI/8)) {
		    // moving forward, oppose motion
		    man[1].on = true;
	    } else if(asin(normaldx) - pos->cd < PI) {
		    man[3].on = true;
	    } else if(asin(normaldx) - pos->cd > PI) {
		    man[2].on = true;
	    }
    }


return;
}



    

