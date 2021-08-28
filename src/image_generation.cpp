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

	std::vector<std::vector<Pixel>> create_snake_buffer(Snake* snake) {
		unsigned int b_width = snake->get_board_width();
		unsigned int b_height = snake->get_board_height();

		std::vector<std::vector<Pixel>> buffer(
			snake->get_board_height(),
			std::vector<Pixel>(snake->get_board_width())
		);

		for (unsigned int j = 0u; j < b_height; ++j) {
	 		for (unsigned int i = 0u; i < b_width; ++i) {
				Pixel pixel = {
					(color) (i % 256),
					(color) (j % 256),
					(color) ((i * j) % 256),
				};

				buffer[j][i] = pixel;
			}
		}

		return buffer;
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
		std::ofstream ofs(
			filename,
			std::ios_base::out | std::ios_base::binary
		);

		ofs << "P6" << std::endl << b_width
			<< ' ' << b_height << std::endl
			<< "255" << std::endl;

		std::vector<std::vector<Pixel>> buffer = create_snake_buffer(snake);

		for (auto row : buffer) {
			 for (auto pixel : row) {
				write_pixel_to_ofstream(ofs, pixel);
			}
		}

		// for (auto j = 0u; j < b_height; ++j) {
			// for (auto i = 0u; i < b_width; ++i) {
				// Pixel pixel = {
					// (color) (i % 256),
					// (color) (j % 256),
					// (color) ((i * j) % 256),
				// };

				// // ofs << (char) pixel.r << (char) pixel.g << (char) pixel.b;       // red, green, blue
				// write_pixel_to_ofstream(ofs, pixel);
			// }
		// }

		ofs.close();

	}

	void write_pixel_to_ofstream(std::ofstream& ofs, Pixel pixel) {
		ofs << (char) pixel.r << (char) pixel.g << (char) pixel.b;
	}
}
