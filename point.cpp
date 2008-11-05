#include "basic_physics_object.cpp"

class point : public basic_physics_object {
	public:
	int width, height;
	
	point(int x, int y, int arg_width, int arg_height) {
		pos_x = x;
		pos_y = y;
		width = arg_width;
		height = arg_height;
		default_init();
	}
	point() {
		pos_x = 0;
		pos_y = 0;
		width = 0;
		height = 0;
		default_init();
	}
	
	void update_phys() {
		accel();
		move();
		
		if (pos_x < 0) {
			pos_x = 0;
			speed_x = -speed_x * 0.5f;
			speed_y *= 0.9f;
		}
		else if (pos_x > width) {
			pos_x = width;
			speed_x = -speed_x * 0.5f;
			speed_y *= 0.9f;
		}
		
		if (pos_y < 0) {
			pos_y = 0;
			speed_y = -speed_y * 0.5f;
			speed_x *= 0.9f;
		}
		else if (pos_y > height) {
			pos_y = height;
			speed_y = -speed_y * 0.5f;
			speed_x *= 0.9f;
		}
		
		int speed_max = 50;
		
		if (speed_x > speed_max) speed_x = speed_max;
		else if (speed_x < -speed_max) speed_x = -speed_max;
		
		if (speed_y > speed_max) speed_y = speed_max;
		else if (speed_y < -speed_max) speed_y = -speed_max;
	}
	
	void attract_to(bool add, float moveX, float moveY) {
		if (add) {
			speed_x += moveX / 2;
			pos_x   += moveX / 2;
			
			speed_y += moveY / 2;
			pos_y   += moveY / 2;
		}
		else {
			speed_x -= moveX / 2;
			pos_x   -= moveX / 2;
			
			speed_y -= moveY / 2;
			pos_y   -= moveY / 2;
		}
	}

	private:
	void default_init() {
		speed_x = 2;
		speed_y = 0;
		accel_y = 0.5f;
		accel_x = 0;
	}
};
