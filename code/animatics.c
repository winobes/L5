void complete_cycle(Animatic *ani, int c) 
{
// completes the loop if the flag goes false in the middle
// 0,1,2,3,0,1,2,3,0,...

    ani[c].timer++;
    
    if (ani[c].timer == ani[c].frame_rate) {
        ani[c].timer = 0;
        if (ani[c].frame == ani[c].nframes-1) {
            ani[c].frame = 0;  
        }
        else {
            ani[c].frame++;
        }
    }

    if (!ani[c].flag && (ani[c].frame == 0)) {
    //if the flag is off and we're at the end of the loop, turn the animation off.
        ani[c].is_running = false;
    } else {
        ani[c].is_running = true;
    }

	ani[c].draw = ani[c].is_running;
	//if the animation is running, there is always something to draw-> There is no blank frame in the loop->

    return;
}

void default_on_static (Animatic *ani, int c)
{
//ani[c].is_running must be initalized to true

    ani[c].is_running = true;

    if (ani[c].flag == true) {
        ani[c].draw = false;
    }

    if (ani[c].flag == false) {
        ani[c].draw = true;
    }

    return;
}

void default_on_loop (Animatic *ani, int c)
{
//a normal loop - stays on unless the flag is held false

//0,1,2,3,0,1,2,...

//ani[c].is_running must be initialized to true 

    if (ani[c].flag) {

        ani[c].is_running = true;
        ani[c].draw = false;

    } else {

        ani[c].is_running = true;
        ani[c].draw = true;
    ani[c].timer++;

        if (ani[c].timer == ani[c].frame_rate) {
            ani[c].timer = 0;
            if (ani[c].frame == ani[c].nframes-1) {
                ani[c].frame = 0;  
            }
            else {
                ani[c].frame++;
            }
        }    


    }

    return;
}

void glow_loop (Animatic *ani, int c)
{
// loops with self-connected ends: 0,1,2,3,2,1,0,1,2..


    if (ani[c].flag) {

    ani[c].is_running = true;
    ani[c].timer++;
    ani[c].draw = true;
   
        if (ani[c].timer == ani[c].frame_rate) {
            ani[c].timer = 0;
            
            if (ani[c].state == 0) {
                ani[c].frame++;
                if (ani[c].frame >= ani[c].nframes) {
                    ani[c].frame -= 2;
                    ani[c].state = 1;
                }
            }else if (ani[c].state == 1) {
                ani[c].frame--;
                if (ani[c].frame < 0) {
                    ani[c].frame += 2;
                    ani[c].state = 0;
                }
            }
        }
    } else {

        ani[c].is_running = false;
        ani[c].timer = 0;
        ani[c].draw = false;
        ani[c].state = 0;
        ani[c].frame = 0;
    }

    return;
}
        
