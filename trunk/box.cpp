#include "triangle.cpp"

class box {
	public:
	triangleclass triangles[3];
	
	box(point points[4]) {
		point points1[] = {points[0], points[1], points[2]};
		triangleclass triangle1 (points1);
		
		point points2[] = {points[1], points[2], points[3]};
		triangleclass triangle2 (points2);
		
		point points3[] = {points[2], points[3], points[0]};
		triangleclass triangle3 (points3);
		
		
		triangles[0] = triangle1;
		triangles[1] = triangle2;
		triangles[2] = triangle3;
	}
	
	void update_phys() {
		triangles[0].update_phys();
		
		move_to_mouse(&triangles[0].points[0]);
		triangles[1].points[0] = triangles[0].points[1];
		triangles[1].points[1] = triangles[0].points[2];
		triangles[2].points[0] = triangles[0].points[2];
		triangles[2].points[2] = triangles[0].points[0];
		
		triangles[1].update_phys();
		
		triangles[0].points[1] = triangles[1].points[0];
		triangles[0].points[2] = triangles[1].points[1];
		triangles[2].points[0] = triangles[1].points[1];
		triangles[2].points[1] = triangles[1].points[2];
		
		triangles[2].update_phys();
		
		move_to_mouse(&triangles[2].points[2]);
		triangles[0].points[0] = triangles[2].points[2];
		triangles[0].points[2] = triangles[2].points[0];
		triangles[1].points[1] = triangles[2].points[0];
		triangles[1].points[2] = triangles[2].points[1];
	}
	
	void draw(BITMAP* buffer) {
		triangles[0].draw(buffer);
		triangles[1].draw(buffer);
		triangles[2].draw(buffer);
	}

	private:
	void move_to_mouse(point * mousepoint) {
		*mousepoint = * new point(mouse_x, mouse_y, mousepoint->width, mousepoint->height);
	}
	
};
