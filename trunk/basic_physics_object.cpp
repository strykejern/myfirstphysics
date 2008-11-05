#include "basic_game_object.cpp"

class basic_physics_object : public basic_game_object {
	public:
	float speed_x, speed_y;
	float accel_x, accel_y;
	
	void accel() {
		speed_x += accel_x;
		speed_y += accel_y;
	}
	
	void move() {
		pos_x += speed_x;
		pos_y += speed_y;
	}
	
	
};
