if (current_room == 0) {

	if (player.hit_wall != 18) {
		room[0].wall[18].hot = true;
	}

	if (player.hit_wall != 19) {
		room[0].wall[19].hot = true;
	}

	if (player.hit_wall == 18 && room[0].wall[18].hot) {
		current_room = 1;
		player.cx += room[1].wall[12].ext.vert[0][0] - room[0].wall[18].ext.vert[0][0];
		player.cy += room[1].wall[12].ext.vert[0][1] - room[0].wall[18].ext.vert[0][1];
		room[1].wall[12].hot = false;
	}

	if (player.hit_wall == 19 && room[0].wall[19].hot) {
		current_room = 1;
		player.cx += room[1].wall[13].ext.vert[0][0] - room[0].wall[19].ext.vert[0][0];
		player.cy += room[1].wall[13].ext.vert[0][1] - room[0].wall[19].ext.vert[0][1];
		room[1].wall[13].hot = false;
	}


}

else if (current_room == 1) {

	if (player.hit_wall != 12) {
		room[1].wall[12].hot = true;
	}

	if (player.hit_wall != 13) {
		room[1].wall[13].hot = true;
	}

	if(player.hit_wall == 12 && room[1].wall[12].hot) {
		current_room = 0;
		player.cx += room[0].wall[18].ext.vert[0][0] - room[1].wall[12].ext.vert[0][0];
		player.cy += room[0].wall[18].ext.vert[0][1] - room[1].wall[12].ext.vert[0][1];
		room[0].wall[18].hot = false;
	}

	if(player.hit_wall == 13 && room[1].wall[13].hot) {
		current_room = 0;
		player.cx += room[0].wall[19].ext.vert[0][0] - room[1].wall[13].ext.vert[0][0];
		player.cy += room[0].wall[19].ext.vert[0][1] - room[1].wall[13].ext.vert[0][1];
		room[0].wall[19].hot = false;
	}

}
