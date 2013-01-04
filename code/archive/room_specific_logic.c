if (current_room == 0) {

	player_can_collide = true;

//hole in the south-east side of the crate
	if (player.y > 250 + player.height && player.y < 350  && player.x > 750 && player.x < 790 - player.width) {
		player_can_collide = false;
		if (player.y > 260) {
			change_room = 1;
			player.x = 580;
			player.y = 90;
		}
	}
//door to the crate opens after it has been shot from the inside
	if (room[0].subject[6].exist) {
		if (player.y > 250 && player.y < 250 + 100 - player.height && player.x > 200 - player.width && player.x < 220 - player.width) {
			player_can_collide = false;
			if (player.x > 210 - player.width) {
				change_room = 1;
				player.x = 10;
				player.y -= 250 - 10;
			}
		}
	}



}

if (current_room == 1) {

	player_can_collide = true;

	if (player.x < -10) {
		change_room = 0;
		player.x = 200 - player.width;
		player.y += 250 - 10;
	}

	if (!room[1].subject[3].exist) {
		room[0].subject[6].exist = true;
	}
}
