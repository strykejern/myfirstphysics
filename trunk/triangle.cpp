#include "point.cpp"
#include <math.h>

class triangleclass {
	public:
	point * points[3];
	float lengths[3];
	int length;
	
	triangleclass(point * arg_points[3]) {
		points[0] = arg_points[0];
		points[1] = arg_points[1];
		points[2] = arg_points[2];
		
		default_init();
	}
	triangleclass() {
		
	}
	
	void update_phys() {
		shape();
		for (int x = 0; x < length; x++) {
			points[x]->update_phys();
		}
	}
	
	void draw(BITMAP* buffer) {
		 triangle(
			buffer, 
			points[0]->pos_x, 
			points[0]->pos_y, 
			points[1]->pos_x, 
			points[1]->pos_y, 
			points[2]->pos_x, 
			points[2]->pos_y, 
			makecol(255,0,0));
	}
	
	private:
	void shape() {
		for (int x = 0; x < length; ++x) {
			attract_points(points[x], points[(x<length-1) ? x+1 : 0], lengths[x]);
		}
	}
	
	void attract_points(point * p1, point * p2, float dist) {
		float katX = p2->pos_x - p1->pos_x;
		float katY = p2->pos_y - p1->pos_y;
		
		float hyp  = sqrt( pow(katX, 2) + pow(katY, 2) );
		
		float moveX = (dist-hyp) * (katX/hyp);
		float moveY = (dist-hyp) * (katY/hyp);
		
		p1->attract_to(false, moveX, moveY);
		p2->attract_to(true , moveX, moveY);
	}
	
	void default_init() {
		length = 3;
		
		float katX = points[1]->pos_x - points[0]->pos_x;
		float katY = points[1]->pos_y - points[0]->pos_y;
		lengths[0]  = sqrt( pow(katX, 2) + pow(katY, 2) );
	
		katX = points[2]->pos_x - points[1]->pos_x;
		katY = points[2]->pos_y - points[1]->pos_y;
		lengths[1]  = sqrt( pow(katX, 2) + pow(katY, 2) );
		
		katX = points[0]->pos_x - points[2]->pos_x;
		katY = points[0]->pos_y - points[2]->pos_y;
		lengths[2] = sqrt( pow(katX, 2) + pow(katY, 2) );
	}

};
