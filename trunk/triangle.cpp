#include "point.cpp"
#include <math.h>

class triangleclass {
	public:
	point points[3];
	float lengths[3];
	int length;
	
	triangleclass(point arg_points[3]) {
		points[0] = arg_points[0];
		points[1] = arg_points[1];
		points[2] = arg_points[2];
		
		default_init();
	}
	triangleclass() {
		default_init();
	}
	
	void shape() {
		for (int x = 0; x < length; ++x) {
			float katX, katY;
			if (x == length-1) {
				katX = points[0].pos_x - points[x].pos_x;
				katY = points[0].pos_y - points[x].pos_y;
			}
			else {
				katX = points[x+1].pos_x - points[x].pos_x;
				katY = points[x+1].pos_y - points[x].pos_y;
			}
			
			float hyp  = sqrt( pow(katX, 2) + pow(katY, 2) );
			
			float moveX = (lengths[x]-hyp) * (katX/hyp);
			float moveY = (lengths[x]-hyp) * (katY/hyp);
			
			points[x].attract_to(false, moveX, moveY);
			
			if (x == length -1) {
				points[0].attract_to(true, moveX, moveY);
			}
			else {
				points[x+1].attract_to(true, moveX, moveY);
			}
		}
	}
	
	void update_phys() {
		shape();
		for (int x = 0; x < length; x++) {
			points[x].update_phys();
		}
	}
	
	void draw(BITMAP* buffer) {
		for (int x = 0; x < length; ++x) {
			if (x == length - 1)
				line(buffer, points[x].pos_x, points[x].pos_y, points[0].pos_x, points[0].pos_y, makecol(255,0,0));
			else
				line(buffer, points[x].pos_x, points[x].pos_y, points[x+1].pos_x, points[x+1].pos_y, makecol(255,0,0));
		
		}
		/*
		 triangle(
			buffer, 
			points[0].pos_x, 
			points[0].pos_y, 
			points[1].pos_x, 
			points[1].pos_y, 
			points[2].pos_x, 
			points[2].pos_y, 
			makecol(255,0,0));
		 */
	}
	
	private:
	void default_init() {
		length = 3;
		
		float katX = points[1].pos_x - points[0].pos_x;
		float katY = points[1].pos_y - points[0].pos_y;
		lengths[0]  = sqrt( pow(katX, 2) + pow(katY, 2) );
	
		katX = points[2].pos_x - points[1].pos_x;
		katY = points[2].pos_y - points[1].pos_y;
		lengths[1]  = sqrt( pow(katX, 2) + pow(katY, 2) );
		
		katX = points[0].pos_x - points[2].pos_x;
		katY = points[0].pos_y - points[2].pos_y;
		lengths[2] = sqrt( pow(katX, 2) + pow(katY, 2) );
	}

};
