#include "point.cpp"

class box {
	public:
	point points[4];
	float lengths[6];
	
	box(point arg_points[4]) {
		for (int x = 0; x < 4; ++x)
			points[x] = arg_points[x];
		
		for (int x = 0; x < 4; ++x)
			lengths[x]  = (points[(x<3)?x+1:0].pos - points[x].pos).length();
		
		lengths[4]  = (points[2].pos - points[0].pos).length();
		
		lengths[5]  = (points[3].pos - points[1].pos).length();
	}
	
	void update_phys(bool mouse) {
		if (mouse) move_to_mouse(&points[0]);
		
		shape();
		shape();
		for (int x = 0; x < 4; x++) {
			points[x].update_phys();
		}
		shape();
		shape();
		
		if (mouse) move_to_mouse(&points[0]);
	}
	
	void draw(BITMAP* buffer) {
		for (int x = 0; x < 4; ++x)
			line(buffer,
			points[x].pos.x, 
			points[x].pos.y, 
			points[(x<3)?x+1:0].pos.x, 
			points[(x<3)?x+1:0].pos.y,
			makecol(255, 0, 0));
	}

	Vector * inside(Vector point1) {
		static Vector p[4];
		p[0] = points[0].pos + ((points[1].pos - points[0].pos)/2);
		p[1] = points[1].pos + ((points[2].pos - points[1].pos)/2);
		p[2] = points[2].pos + ((points[3].pos - points[2].pos)/2);
		p[3] = points[3].pos + ((points[0].pos - points[3].pos)/2);
		
		Vector v[4];
		v[0] = (points[1].pos-points[0].pos).ccper();
		v[1] = (points[2].pos-points[1].pos).ccper();
		v[2] = (points[3].pos-points[2].pos).ccper();
		v[3] = (points[0].pos-points[3].pos).ccper();
		
		Vector v2[4];
		v2[0] = point1 - p[0];
		v2[1] = point1 - p[1];
		v2[2] = point1 - p[2];
		v2[3] = point1 - p[3];
		
		
		if (0<=skalarpr(v[0],v2[0]) && 
			0<=skalarpr(v[1],v2[1]) && 
			0<=skalarpr(v[2],v2[2]) && 
			0<=skalarpr(v[3],v2[3])) {
			return p;
		}
		return 0;
	}
	
	void shape() {
		attract_points(&points[0], &points[2], lengths[4]);
		attract_points(&points[1], &points[3], lengths[5]);
		
		for (int x = 0; x < 4; ++x)
			attract_points(&points[x], &points[(x<3)?x+1:0], lengths[x]);
		
		attract_points(&points[0], &points[2], lengths[4]);
		attract_points(&points[1], &points[3], lengths[5]);
		
		if (is_vreng()) vreng();
	}
	private:
	void attract_points(point * p1, point * p2, float dist) {
		float katX = p2->pos.x - p1->pos.x;
		float katY = p2->pos.y - p1->pos.y;
		
		float hyp  = sqrt( pow(katX, 2) + pow(katY, 2) );
		
		float moveX = (dist-hyp) * (katX/hyp);
		float moveY = (dist-hyp) * (katY/hyp);
		
		p1->attract_to(false, moveX, moveY);
		p2->attract_to(true , moveX, moveY);
	}
	
	void move_to_mouse(point * mousepoint) {
		*mousepoint = * new point(Vector(mouse_x, mouse_y), mousepoint->width, mousepoint->height);
	}
	
	float skalarpr(Vector v1, Vector v2) {
		return (v1.x * v2.x) + (v1.y * v2.y);
	}
	
	bool is_vreng() {
		Vector v = points[0].pos + ((points[1].pos - points[0].pos)/20);
		Vector v1 = v + ((points[3].pos - points[0].pos)/20);
		return (0 == inside(v1));
	}
	
	void vreng() {
		point temp;
		temp = points[0];
		points[0] = points[2];
		points[2] = temp;
	}
	
};
