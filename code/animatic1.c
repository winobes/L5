void animatic1 (struct Animatic* animatic, bool *anikeys) {

	
	//if the key is not pressed and the animation loop is on its last frame, stop running the animation
	if (!anikeys[animatic->flag] &&
		animatic->source_x == animatic->w * (animatic->nframes - 1)) {
		animatic->is_running = false;
	}



	if (!animatic->is_running && 
    anikeys[animatic->flag]) {

		animatic->is_running = true;
		animatic->timer = 0;
		
	}


	if (animatic->is_running) {

		animatic->timer++; //incriment the animation timer

		//if the animation timer and the frame rate agree, move to the next frame-> If its the last frame, move to the first-> Reset the timer->
		if (animatic->timer == animatic->frame_rate) {
			animatic->timer = 0;
			if(animatic->source_x == animatic->w * (animatic->nframes - 1)) {
				animatic->source_x = 0;
			}
			else {
				animatic->source_x += animatic->w;
			}
		}
	}

	animatic->draw = animatic->is_running;
	//if the animation is running, there is always something to draw-> There is no blank frame in the loop->

}
