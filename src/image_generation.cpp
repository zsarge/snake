#include "image_generation.h"

namespace IMAGE_GEN {
	std::string generate_folder_name() {
		// for image generation:                       
		auto t = std::time(nullptr);                   
		auto tm = *std::localtime(&t);                 

		std::ostringstream oss;                        
		oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
		return oss.str();
	}

	void print_to_image(const Snake* snake) {
		unsigned int b_width = snake->get_board_width();
		unsigned int b_height = snake->get_board_height();

		std::ofstream ofs("first.ppm", std::ios_base::out | std::ios_base::binary);
		ofs << "P6" << std::endl << b_width << ' ' << b_height << std::endl << "255" << std::endl;

		for (auto j = 0u; j < b_height; ++j)
			for (auto i = 0u; i < b_width; ++i)
				ofs << (char) (i % 256) << (char) (j % 256) << (char) ((i * j) % 256);       // red, green, blue

		ofs.close();

	}
}
