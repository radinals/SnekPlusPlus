// #include <cstddef>

// using std::size_t;

#ifndef __UTILS__
#define __UTILS__

enum CellStatus{CellEmpty, CellFood, CellSnake};
enum Direction{GoingLeft, GoingRight, GoingUp, GoingDown};

struct COORD {
	long long y;
	long long x;
};


#endif // !__UTILS__
