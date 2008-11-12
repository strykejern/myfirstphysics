class Vector {
	public:
	float x, y;
	
	Vector() { x=0; y=0; }
	Vector(float X, float Y) { x=X; y=Y; }
	Vector operator + (Vector v) {
		Vector temp;
		temp.x = x + v.x;
		temp.y = y + v.y;
		return temp;
	}
	Vector operator - (Vector v) {
		Vector temp;
		temp.x = x - v.x;
		temp.y = y - v.y;
		return temp;
	}
	Vector operator += (Vector v) { 
		Vector temp;
		temp.x = x + v.x;
		temp.y = y + v.y;
		return temp;
	}
	Vector operator -= (Vector v) { 
		Vector temp;
		temp.x = x - v.x;
		temp.y = y - v.y;
		return temp;
	}
	Vector operator / (int d) {
		return Vector(x/d, y/d);
	}
	Vector operator - () {
		Vector temp;
		temp.x = -x;
		temp.y = -y;
		return temp;
	}
	bool operator != (Vector v) {
		return x!=v.x || y!=v.y;
	}
	Vector operator * (float m) {
		return Vector(x*m, y*m);
	}
	
	float length() {
		return sqrt(pow(x, 2)+pow(y, 2));
	}
	
	Vector ccper () {
		return Vector(-y, x);
	}
	
	void set_length(float l) {
		float fx = x / length();
		float fy = y / length();
		x = l * fx;
		y = l * fy;
	}
};
