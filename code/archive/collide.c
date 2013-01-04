int collide (struct Subject one, struct Subject two) {

	int x1 = one.x;
	int a1 = one.x + one.width;
	int y1 = one.y;
	int b1 = one.y + one.height;

	int x2 = two.x;
	int a2 = two.x + two.width;
	int y2 = two.y;
	int b2 = two.y + two.height;


	/*if (a1 < x2) {
		return 0;
	}
	if (a2 < x1) {
		return 0;
	}
	if (b1 < y2) {
		return 0;
	}
	if (b2 < y1) {
		return 0;
	}*/


	bool rel[12];

/* All of the possible relationship between the x and y positions of the two subjects given non-negative height and width
[0] x2 < x1
[1] x1 < x2
[2] x2 < a1
[3] x1 < a2
[4] a1 < a2
[5] a2 < a1
[6] y2 < y1
[7] y1 < y2
[8] y2 < b1
[9] y1 < b2
[10] b1 < b2
[11] b2 < b1
*/

	int i;

	for (i = 0; i < 12; i++) {
		rel[i] = false;
	}

	if (x2 < x1) {
		rel[0] = true;
	}
	if (x1 < x2) {
		rel[1] = true;
	}
	if (x2 < a1) {
		rel[2] = true;
	}
	if (x1 < a2) {
		rel[3] = true;
	}
	if (a1 < a2) {
		rel[4] = true;
	}
	if (a2 < a1) {
		rel[5] = true;
	}
	if (y2 < y1) {
		rel[6] = true;
	}
	if (y1 < y2) {
		rel[7] = true;
	}
	if (y2 < b1) {
		rel[8] = true;
	}
	if (y1 < b2) {
		rel[9] = true;
	}
	if (b1 < b2) {
		rel[10] = true;
	}
	if (b2 < b1) {
		rel[11] = true;
	}

	int X = 0;
	int Y = 0;

	if (rel[0] && rel[3]) {
		if (rel[4]) {
			X = 1;
		}
		if (rel[5]) {
			X = 4;
		}
	}
	if (rel[1] && rel[2]) {
		if (rel[4]) {
			X = 3;
		}
		if (rel[5]) {
			X = 2;
		}
	}
	if (rel[6] && rel[9]) {
		if (rel[10]) {
			Y = 1;
		}
		if (rel[11]) {
			Y = 4;
		}
	}
	if (rel[7] && rel[8]) {
		if (rel[10]) {
			Y = 3;
		}
		if (rel[11]) {
			Y = 2;
		}
	}

	if ((X == 1 || X == 2) && Y == 4) {
		return 1;
	}

	if (X == 3 && (Y == 1 || Y == 2)) {
		return 2;
	}

	if ((X == 1 || X == 2) && Y == 3) {
		return 3;
	}

	if (X == 4 && (Y == 1 || Y == 2)) {
		return 4;
	}

	if (X == 3 && Y == 3) {
		return 5;
	}
	
	if (X == 3 && Y == 4) {
		return 6;
	}

	if (X == 4 && Y == 3) {
		return 7;
	}

	if (X == 4 && Y == 4) {
		return 8;
	}

	if (X == 1 && Y == 1) {
		return 9;
	}

	if (X == 2 && Y == 2) {
		return 9;
	}
	
	else {
		return 0;
	}


}
