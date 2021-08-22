#ifndef SNAKE_GUARD
#define SNAKE_GUARD

#include <vector>

struct vec2 {
	unsigned int x;
	unsigned int y;
};

enum square {
	blank = 0,
	snake = 1,
	// food // not implemented
};

enum snake_directon {
	up,
	down,
	left,
	right,
};

class Snake {
	public:
		Snake();
		~Snake();
		void move();
		void print_body() const;
		vec2 get_segment(int) const;
		void set_segment(int, vec2);
		void set_segment(int, unsigned int, unsigned int);
		/* print to terminal */
		void print_to_terminal() const;
	private:
		std::vector<vec2> body;
		unsigned int board_width;
		unsigned int board_height;
		snake_directon direction;
};

#endif
