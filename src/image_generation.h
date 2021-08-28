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

#define PREFIX "./frames/"
#define DEFAULT_PIXEL Pixel{61u, 61u, 61u} // a nice gray color
#define BORDER_PIXEL Pixel{31u, 28u, 28u}  // a darker gray color
#define SNAKE_PIXEL Pixel{140u, 247u, 93u}  // a light green color
#define FOOD_PIXEL Pixel{254u, 0u, 0u}  // red

#define SCALAR 7

#define IMAGE_FORMAT 6 // valid options are 3 and 6
// See https://www.cs.swarthmore.edu/~soni/cs35/f13/Labs/extras/01/ppm_info.html
// and http://netpbm.sourceforge.net/doc/ppm.html
// for more information about ppm files.

#define Q(x) #x
#define QUOTE(x) Q(x)

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
	void draw_borders(std::vector<std::vector<Pixel>>&, Snake*);
	void draw_snake(std::vector<std::vector<Pixel>>&, Snake*);
	void draw_food(std::vector<std::vector<Pixel>>&, Snake*);
	void draw_segment(unsigned int, std::vector<std::vector<Pixel>>&, Snake*);
	void connect_segments(std::vector<std::vector<Pixel>>&, Snake*);
}

#endif

