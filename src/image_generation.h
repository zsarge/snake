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

namespace IMAGE_GEN {
	void print_to_image(Snake* snake);
	std::string generate_folder_name();
	void create_folder(std::string);
}

#endif

