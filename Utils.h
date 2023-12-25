#ifndef __UTILS__
#define __UTILS__

enum Direction { Up, Down, Left, Right };

typedef struct Vec {
	int x = 0;
	int y = 0;

	bool operator < (const Vec& obj) { return (this->x < obj.x) || (this->y < obj.y); }
	bool operator > (const Vec& obj) { return (this->x > obj.x) || (this->y > obj.y); }
	bool operator == (const Vec& obj) { return (this->x == obj.x) && (this->y == obj.y); }
	bool operator <= (const Vec& obj) { return (this->x < obj.x) || (this->y < obj.y) || this->y == obj.y; }
	bool operator >= (const Vec& obj) { return (this->x > obj.x) || (this->y > obj.y) || this->y == obj.y; }
} Vec;

#endif // !__UTILS__
