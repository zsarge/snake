#include <iostream>
#include <chrono>
#include <thread>
#include "snake.cpp"

int main() {
	Snake snek;
	for (;;) {
		snek.print_to_terminal();
		snek.print_to_image();
		snek.move();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}
