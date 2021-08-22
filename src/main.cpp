#include <iostream>
#include "snake.cpp"

int main() {
	Snake snek;
	snek.print_to_terminal();
	snek.move();
	snek.print_to_terminal();
	snek.print_body();
}
