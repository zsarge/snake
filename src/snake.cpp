#include <iostream>
#include "snake.h"

// Snake constructor
Snake::Snake() {
	vec2 segment = {5, 5};
	Snake::body.push_back(segment);
	segment = {6, 5};
	Snake::body.push_back(segment);

	board_height = 10;
	board_width  = 10;

	Snake::direction = snake_direction::right;

	Snake::frame_number = 0;

    Snake::folder_name = IMAGE_GEN::generate_folder_name();
	IMAGE_GEN::create_folder(Snake::folder_name);

	std::cout << Snake::folder_name << std::endl;
}

// Snake destructor
Snake::~Snake() {
	body.clear();
}

bool Snake::check_is_valid(unsigned int x, unsigned int y) const {
	return (x < board_width && x >= 0) &&
		(y < board_height && y >= 0);
}

void Snake::assert_is_valid(unsigned int x, unsigned int y) const {
	if (x >= board_width || x < 0) {
		std::cout << "Error! x is invalid: " << x << std::endl;
		throw invalid_move_exception();
	}

	if (y >= board_height || y < 0)  {
		std::cout << "Error! y is invalid: " << y << std::endl;
		throw invalid_move_exception();
	}
}

void Snake::move() {
	// copy over snake positions
	for (unsigned int index = Snake::body.size() - 1; index > 0; index--) {
		vec2 next_position = Snake::get_segment(index - 1);
		Snake::set_segment(index, next_position);
	}

	direction = AI::get_best_direction(this);

	// move head in correct direction
	unsigned int x = Snake::body[0].x;
	unsigned int y = Snake::body[0].y;

	// note that translations are based around (0,0) being the top left corner
	switch (direction) {
		case up:
			Snake::assert_is_valid(x, y - 1);
			Snake::set_segment(0,  x, y - 1);
			break;
		case down:
			Snake::assert_is_valid(x, y + 1);
			Snake::set_segment(0,  x, y + 1);
			break;
		case left:
			Snake::assert_is_valid(x - 1, y);
			Snake::set_segment(0,  x - 1, y);
			break;
		case right:
			Snake::assert_is_valid(x + 1, y);
			Snake::set_segment(0,  x + 1, y);
			break;
	};
}

char square_to_char(square sqr) {
	switch (sqr) {
		case blank:
			return ' ';
		case snake:
			return '#';
		default:
			return '?';
	}
}

void print_header(unsigned int board_width) {
	std::cout << "+";

	for (unsigned int x = 0; x < board_width; x++)
		std::cout << "-";

	std::cout << "+\n";
}

void Snake::print_to_terminal() const {
	// render everything to a layer, and then print that layer
	// this is not the most efficient, but, to me, it is simpler than the alternatives
	square layer[board_height][board_width] = {{square::blank}};

	// initialize all memory
	for (unsigned int y = 0; y < board_height; y++)
		for (unsigned int x = 0; x < board_width; x++)
			layer[y][x] = square::blank;

	// copy snake positions to board layer
	for (vec2 segment : Snake::body)
		layer[segment.y][segment.x] = square::snake;

	// print the board to the terminal
	print_header(board_width);
	for (unsigned int y = 0; y < board_height; y++) {
		std::cout << "|";

		for (unsigned int x = 0; x < board_width; x++)
			std::cout << square_to_char(layer[y][x]);

		std::cout << "|\n";
	}
	print_header(board_width);

	std::cout.flush();
}

void Snake::print_body() const {
	for (int i = 0; i < Snake::body.size(); i++)
		std::cout
			<< "("
			<< Snake::body[i].x
			<< ","
			<< Snake::body[i].y
			<< ")"
			<< std::endl;
}

vec2 Snake::get_segment(int index) const {
	return body[index];
}

void Snake::set_segment(int index, vec2 segment) {
	body[index] = segment;
}

void Snake::set_segment(int index, unsigned int x, unsigned int y) {
	vec2 segment = {x, y};
	body[index] = segment;
}

snake_direction Snake::get_direction() const {
	return Snake::direction;
}

unsigned int Snake::get_board_width() const {
	return board_width;
}

unsigned int Snake::get_board_height() const {
	return board_height;
}

unsigned int Snake::get_next_frame_number() {
	frame_number++;
	return frame_number;
}

void Snake::print_to_image() {
	IMAGE_GEN::print_to_image(this);
}

std::string Snake::get_folder_name() const {
	return folder_name;
}

