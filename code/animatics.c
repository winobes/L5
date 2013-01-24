void complete_cycle(Animatic *ani, int current) 
{

    ani[current].timer++;
    
    if (ani[current].timer == ani[current].frame_rate) {
        ani[current].timer = 0;
        if (ani[current].source_x == ani[current].w * (ani[current].nframes-1)) {
            ani[current].source_x = 0;  
        }
        else {
            ani[current].source_x += ani[current].w;
        }
    }

    if (!ani[current].flag && (ani[current].source_x == 0)) {
    //if the flag is off and we're at the end of the loop, turn the animation off.
        ani[current].is_running = false;
    } else {
        ani[current].is_running = true;
    }

	ani[current].draw = ani[current].is_running;
	//if the animation is running, there is always something to draw-> There is no blank frame in the loop->

    return;
}

void default_on_static (Animatic *ani, int current)
{

    ani[current].is_running = true;

    if (ani[current].flag == true) {
        ani[current].draw = false;
    }

    if (ani[current].flag == false) {
        ani[current].draw = true;
    }

    return;
}

void default_on_loop (Animatic *ani, int current)
{


    if (ani[current].flag) {

        ani[current].is_running = true;
        ani[current].draw = false;

    } else {

        ani[current].is_running = true;
        ani[current].draw = true;
    ani[current].timer++;

        if (ani[current].timer == ani[current].frame_rate) {
            ani[current].timer = 0;
            if (ani[current].source_x == ani[current].w * (ani[current].nframes-1)) {
                ani[current].source_x = 0;  
            }
            else {
                ani[current].source_x += ani[current].w;
            }
        }    


    }

    return;
}
