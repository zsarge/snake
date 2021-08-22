#include <iostream>
#include "snake.h"

void Snake::move() {
	std::cout << "moved" << std::endl;
}

Snake::Snake() {
	Snake::length = 0;
	vec2 segment = {0, 0};
	Snake::body.push_back(segment);
}

Snake::~Snake() {
	// default constructor
}

void Snake::print_body() {
	for (int i = 0; i < Snake::body.size(); i++)
		std::cout 
			<< "(" 
			<< Snake::body[i].x 
			<< ","
			<< Snake::body[i].y 
			<< ")"
			<< std::endl;
}

