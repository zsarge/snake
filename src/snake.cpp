#include <iostream>
#include "snake.h"

void Snake::move() {
	std::cout << "moved" << std::endl;
}

Snake::Snake() {
	vec2 segment = {5, 5};
	Snake::body.push_back(segment);
	segment = {6, 5};
	Snake::body.push_back(segment);

	board_height = 10;
	board_width  = 10;
}

Snake::~Snake() {
	body.clear();
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
	std::cout << "+" << std::endl;
}

void Snake::print_to_terminal() const {
	// render everything to a layer, and then print that layer
	// this is not the most efficient, but, to me, it is simpler
	square layer[board_height][board_width] = {{square::blank}};

	// initialize all memory
	for (unsigned int y = 0; y < board_height; y++)
		for (unsigned int x = 0; x < board_width; x++)
			layer[y][x] = square::blank;

	// copy snake positions to board layer
	for (vec2 segment : Snake::body) {
		layer[segment.y][segment.x] = square::snake;
	}

	// print the board to the terminal
	print_header(board_width);
	for (unsigned int y = 0; y < board_height; y++) {
		std::cout << "|";
		for (unsigned int x = 0; x < board_width; x++) {
			std::cout << square_to_char(layer[y][x]);
		}
		std::cout << "|" << std::endl;
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


