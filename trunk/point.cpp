#include "basic_physics_object.cpp"

class point : public basic_physics_object {
	public:
	int width, height;
	
	point(Vector v, int arg_width, int arg_height) {
		pos = v;
		width = arg_width;
		height = arg_height;
		default_init();
	}
	point() {
		width = 0;
		height = 0;
		default_init();
	}
	
	void update_phys() {
		accelerate();
		move();
		
		if (pos.x < 0+5) {
			pos.x = 0+5;
			speed.x = -speed.x * 0.5f;
			speed.y *= 0.8f;
		}
		else if (pos.x > width-5) {
			pos.x = width-5;
			speed.x = -speed.x * 0.5f;
			speed.y *= 0.8f;
		}
		
		if (pos.y < 0+5) {
			pos.y = 0+5;
			speed.y = -speed.y * 0.5f;
			speed.x *= 0.8f;
		}
		else if (pos.y > height-5) {
			pos.y = height-5;
			speed.y = -speed.y * 0.5f;
			speed.x *= 0.8f;
		}
		
		int speed_max = 10;
		
		if (speed.x > speed_max) speed.x = speed_max;
		else if (speed.x < -speed_max) speed.x = -speed_max;
		
		if (speed.y > speed_max) speed.y = speed_max;
		else if (speed.y < -speed_max) speed.y = -speed_max;
	}
	
	void attract_to(bool add, float moveX, float moveY) {
		if (add) {
			speed.x += moveX / 4;
			pos.x   += moveX / 2;
			
			speed.y += moveY / 4;
			pos.y   += moveY / 2;
		}
		else {
			speed.x -= moveX / 4;
			pos.x   -= moveX / 2;
			
			speed.y -= moveY / 4;
			pos.y   -= moveY / 2;
		}
	}
	void attract_to(Vector v) {
		speed = speed + (v / 4);
		pos   = pos   + (v / 2);
	}

	private:
	void default_init() {
		speed.x = 2;
		speed.y = 1;
		accel.y = 0.5f;
		accel.x = 0;
	}
};
