#include "image_generation.h"

#define PREFIX "./frames/"

namespace IMAGE_GEN {
	std::string generate_folder_name() {
		// for image generation:                       
		auto t = std::time(nullptr);                   
		auto tm = *std::localtime(&t);                 

		std::ostringstream oss;                        
		oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
		return oss.str();
	}

	void create_folder(std::string folder_name) {
		std::filesystem::create_directories(PREFIX + folder_name);
	}

	void print_to_image(Snake* snake) {
		unsigned int b_width = snake->get_board_width();
		unsigned int b_height = snake->get_board_height();

		// get file name
		std::string filename = PREFIX;
		filename.append(snake->get_folder_name());
		filename.append("/");
		filename.append(std::to_string(snake->get_next_frame_number()));
		filename.append(".ppm");

		// create file stream
		std::ofstream ofs(filename, std::ios_base::out | std::ios_base::binary);

		ofs << "P6" << std::endl << b_width << ' ' << b_height << std::endl << "255" << std::endl;

		for (unsigned int j = 0u; j < b_height; ++j) {
	 		for (unsigned int i = 0u; i < b_width; ++i) {
				// ofs << (char) (i % 256) << (char) (j % 256) << (char) ((i * j) % 256);       // red, green, blue
				Pixel pixel = {
					(color) (i % 256),
					(color) (j % 256),
					(color) ((i * j) % 256),
				};

				write_pixel_to_ofstream(&ofs, pixel);
			}
		}

		ofs.close();

	}

	void write_pixel_to_ofstream(std::ofstream& ofs, Pixel pixel) {
		ofs << (char) pixel.r << (char) pixel.g << (char) pixel.b;
	}
}
