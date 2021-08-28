#ifndef IMAGE_GEN_GUARD
#define IMAGE_GEN_GUARD

#include <iostream>
#include <fstream>
#include <cstdio>

// time string generation
#include <iomanip>
#include <ctime>
#include <sstream>

// create folder
#include <filesystem>

typedef unsigned char color;

struct Pixel {
	color r;
	color g;
	color b;
};

namespace IMAGE_GEN {
	void print_to_image(Snake* snake);
	std::string generate_folder_name();
	void create_folder(std::string);
	void write_pixel_to_ofstream(std::ofstream&, Pixel);

	std::vector<std::vector<Pixel>> create_snake_buffer(Snake*);
}

#endif

