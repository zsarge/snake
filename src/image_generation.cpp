#include "image_generation.h"

#define PREFIX "./frames/"
#define DEFAULT_PIXEL Pixel{61u, 61u, 61u} // a nice gray color
#define BORDER_PIXEL Pixel{31u, 28u, 28u}  // a darker gray color

#define SCALAR 7

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

	/* We want a buffer for our snake so that we can write to it positionally. 
	 * Additionally, this allows multiple layers to render to the same buffer,
	 * which would not be possible if we were writing to a stream.
	 */
	std::vector<std::vector<Pixel>> create_snake_buffer(Snake* snake) {
		unsigned int b_width = snake->get_board_width();
		unsigned int b_height = snake->get_board_height();

		// each pixel of board size gets 7x7 pixels in the buffer
		std::vector<std::vector<Pixel>> buffer(
			b_height * 7,
			std::vector<Pixel>(b_width * SCALAR, DEFAULT_PIXEL)
		);

		return buffer;
	}

	void draw_borders(std::vector<std::vector<Pixel>>& buffer, Snake* snake) {
		// lines are created on both sides of each grid square
		int starts[] = {0, SCALAR - 1};
		
		// draw horizontal lines
		for (int start : starts) {
			for (unsigned int y = start; y < snake->get_board_height() * SCALAR; y += SCALAR) {
				for (unsigned int x = 0; x < snake->get_board_width() * SCALAR; x++) {
					buffer[y][x] = BORDER_PIXEL;
				}
			}
		}

		// draw vertical lines
		for (int start : starts) {
			for (unsigned int x = start; x < snake->get_board_width() * SCALAR; x += SCALAR) {
				for (unsigned int y = 0; y < snake->get_board_height() * SCALAR; y++) {
					buffer[y][x] = BORDER_PIXEL;
				}
			}
		}
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

		ofs << "P3" << std::endl << b_width * SCALAR
			<< ' ' << b_height * SCALAR << std::endl
			<< "255" << std::endl;

		std::vector<std::vector<Pixel>> buffer = create_snake_buffer(snake);
		draw_borders(buffer, snake);

		for (auto row : buffer) {
			 for (auto pixel : row) {
				write_pixel_to_ofstream(ofs, pixel);
			}
		}

		ofs.close();

	}

	void write_pixel_to_ofstream(std::ofstream& ofs, Pixel pixel) {
		// write P6
		// ofs << (char) pixel.r << (char) pixel.g << (char) pixel.b;
		// write P3
		ofs << std::to_string(pixel.r) <<  ' ' <<
			std::to_string(pixel.g) <<  ' ' <<
			std::to_string(pixel.b) << std::endl;
	}
}
