#include <iostream>
#include "snake.cpp"

int main() {
	Snake snek;
	for (;;) {
		snek.print_to_terminal();
		snek.move();
	}
}
