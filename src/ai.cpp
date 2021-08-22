#include "ai.h"

namespace AI {
	snake_direction get_best_direction(Snake* snake) {
		print_debug_info(snake);
		snake_direction direction = snake->get_direction();

		if (!front_is_clear(snake))
			return get_right_turn(direction);
		else 
			return direction;
	}

	// check whether or not (x,y) squares away from the segment is a valid square
	bool delta_is_valid(Snake* snake, int x, int y) {
		// TODO: Check for body 
		vec2 head = snake->get_segment(0);
		return snake->check_is_valid(head.x + x, head.y + y);
	}

	bool front_is_clear(Snake* snake) {
		// remember that translations are based off of (0,0) being the top left
		switch (snake->get_direction()) {
			case snake_direction::up:
				return delta_is_valid(snake, 0, -1);
			case snake_direction::right:
				return delta_is_valid(snake, 1, 0);
			case snake_direction::down:
				return delta_is_valid(snake, 0, 1);
			case snake_direction::left:
				return delta_is_valid(snake, -1, 0);
			default:
				throw std::logic_error("front_is_clear");
		}
	}

	void print_debug_info(Snake* snake) {
		std::cout 
			<< "snake ai:" << std::endl
			<< "(" << snake->get_segment(0).x
			<< "," << snake->get_segment(0).y
			<< ")" << std::endl;
	}

	snake_direction get_right_turn(snake_direction direction) {
		switch (direction) {
			case snake_direction::up:
				return snake_direction::right;
			case snake_direction::right:
				return snake_direction::down;
			case snake_direction::down:
				return snake_direction::left;
			case snake_direction::left:
				return snake_direction::up;
			default:
				throw std::logic_error("get_right_turn");
		}
	}
} 
