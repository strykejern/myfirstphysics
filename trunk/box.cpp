#include "triangle.cpp"

class box {
	public:
	triangleclass triangles[3];
	point * points[4];
	
	box(point * arg_points[4]) {
		points[0] = arg_points[0];
		points[1] = arg_points[1];
		points[2] = arg_points[2];
		points[3] = arg_points[3];
		
		point * arg_points1[] = {points[0], points[1], points[2]};
		triangleclass triangle1 (arg_points1);
		
		point * arg_points2[] = {points[1], points[2], points[3]};
		triangleclass triangle2 (arg_points2);
		
		point * arg_points3[] = {points[2], points[3], points[0]};
		triangleclass triangle3 (arg_points3);
		
		
		triangles[0] = triangle1;
		triangles[1] = triangle2;
		triangles[2] = triangle3;
	}
	
	void update_phys(bool mouse) {
		triangles[0].update_phys();
		
		if (mouse) move_to_mouse(triangles[0].points[0]);
		
		triangles[1].update_phys();
		
		triangles[2].update_phys();
		
		if (mouse) move_to_mouse(triangles[2].points[2]);
	}
	
	void draw(BITMAP* buffer) {
		triangles[0].draw(buffer);
		triangles[1].draw(buffer);
		triangles[2].draw(buffer);
	}

	bool inside(point point1) {
		float p[4][2];
		p[0][0] = points[0]->pos_x + ((points[1]->pos_x - points[0]->pos_x)/2);
		p[0][1] = points[0]->pos_y + ((points[1]->pos_y - points[0]->pos_y)/2);
		
		p[1][0] = points[1]->pos_x + ((points[2]->pos_x - points[1]->pos_x)/2);
		p[1][1] = points[1]->pos_y + ((points[2]->pos_y - points[1]->pos_y)/2);
		
		p[2][0] = points[2]->pos_x + ((points[3]->pos_x - points[2]->pos_x)/2);
		p[2][1] = points[2]->pos_y + ((points[3]->pos_y - points[2]->pos_y)/2);
		
		p[3][0] = points[3]->pos_x + ((points[0]->pos_x - points[3]->pos_x)/2);
		p[3][1] = points[3]->pos_y + ((points[0]->pos_y - points[3]->pos_y)/2);
		
		float v[4][2];
		v[0][0] = points[1]->pos_x - points[0]->pos_x;
		v[0][1] = points[1]->pos_y - points[0]->pos_y;
		
		v[1][0] = points[2]->pos_x - points[1]->pos_x;
		v[1][1] = points[2]->pos_y - points[1]->pos_y;
		
		v[2][0] = points[3]->pos_x - points[2]->pos_x;
		v[2][1] = points[3]->pos_y - points[2]->pos_y;
		
		v[3][0] = points[0]->pos_x - points[3]->pos_x;
		v[3][1] = points[0]->pos_y - points[3]->pos_y;
		
		float v2[4][2];
		v2[0][0] = point1.pos_x - p[0][0];
		v2[0][1] = point1.pos_y - p[0][1];
		
		v2[1][0] = point1.pos_x - p[1][0];
		v2[1][1] = point1.pos_y - p[1][1];
		
		v2[2][0] = point1.pos_x - p[2][0];
		v2[2][1] = point1.pos_y - p[2][1];
		
		v2[3][0] = point1.pos_x - p[3][0];
		v2[3][1] = point1.pos_y - p[3][1];
		
		if (0<=skalarpr(v[0],v2[0]) && 
			0<=skalarpr(v[1],v2[1]) && 
			0<=skalarpr(v[2],v2[2]) && 
			0<=skalarpr(v[3],v2[3])) {
			return true;
		}
		
		/*float v[] = {point1.pos_x - points[0]->pos_x, point1.pos_y - points[0]->pos_y};
		float v1[] = {points[1]->pos_x - points[0]->pos_x, points[1]->pos_y - points[0]->pos_y};
		float v2[] = {points[3]->pos_x - points[0]->pos_x, points[3]->pos_y - points[0]->pos_y};
		if (0<=skalarpr(v,v1) && 
			0<=skalarpr(v1,v1) && 
			0<=skalarpr(v,v2) && 
			0<=skalarpr(v2,v2)) {
			return true;
		}*/
		return false;
	}
	
	private:
	void move_to_mouse(point * mousepoint) {
		*mousepoint = * new point(mouse_x, mouse_y, mousepoint->width, mousepoint->height);
	}
	
	float skalarpr(float v1[2], float v2[2]) {
		return (v1[0] * v2[0]) + (v1[1] * v2[1]);
	}
	
};
