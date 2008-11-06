
bool collision_box(box * boks1, box * boks2) {
	box * boks[2];
	for (int y = 0; y < 2; ++y) {
		if (y == 0) {
			boks[0] = boks1;
			boks[1] = boks2;
		}
		else {
			boks[0] = boks2;
			boks[1] = boks1;
		}
		
		for (int x = 0; x < 4; ++x) {
			if (boks[0]->inside(*boks[1]->points[x])) {
				return true;
			}
		}
	}
	return false;
}
