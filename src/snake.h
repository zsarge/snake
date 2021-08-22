#ifndef SNAKE_GUARD
#define SNAKE_GUARD

#include <vector>

struct vec2 {
	unsigned int x;
	unsigned int y;
};

class Snake {
	public:
		Snake();
		~Snake();
		void move();
		void print_body();
	private:
		int length;
		std::vector<vec2> body;
};

#endif
