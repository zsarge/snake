#ifndef SNAKE_GUARD
#define SNAKE_GUARD

#include <vector>
#include <iostream>

// for time string generation
#include <iomanip>
#include <ctime>
#include <sstream>

// for random number generation
#include <random>

struct vec2 {
	unsigned int x;
	unsigned int y;
};

enum square {
	blank = 0,
	snake = 1,
	food  = 2
};

enum snake_direction {
	up,
	down,
	left,
	right,
};

struct invalid_move_exception : public std::exception {
   const char * what () const throw () {
      return "Invalid move. Index is out of bounds.";
   }
};

class Snake {
	public:
		Snake();
		~Snake();
		void move();
		void print_body() const;
		unsigned int get_size() const;
		vec2 get_segment(int) const;
		void set_segment(int, vec2);
		void set_segment(int, unsigned int, unsigned int);
		void print_to_terminal() const;
		void print_to_image();
		bool check_is_valid(unsigned int, unsigned int) const;
		snake_direction get_direction() const;
		unsigned int get_board_width() const;
		unsigned int get_board_height() const;
		unsigned int get_next_frame_number();
		std::string get_folder_name() const;
		vec2 get_food() const;

	private:
		void assert_is_valid(unsigned int, unsigned int) const;
		std::vector<vec2> body;
		unsigned int board_width;
		unsigned int board_height;
		snake_direction direction;
		vec2 food;
		vec2 get_new_food_location() const;

		// for image generation:
		unsigned int frame_number;
		std::string folder_name;
};

// include at end to avoid circular dependancy
#include "ai.cpp"
#include "image_generation.cpp"

#endif
