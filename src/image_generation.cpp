#include "image_generation.h"

#define PREFIX "./frames/"
#define DEFAULT_PIXEL Pixel{61u, 61u, 61u} // a nice gray color
#define BORDER_PIXEL Pixel{31u, 28u, 28u}  // a darker gray color
#define SNAKE_PIXEL Pixel{255u, 0u, 0u}  // a darker gray color

#define SCALAR 7

#define IMAGE_FORMAT 6 // valid options are 3 and 6
// See https://www.cs.swarthmore.edu/~soni/cs35/f13/Labs/extras/01/ppm_info.html
// and http://netpbm.sourceforge.net/doc/ppm.html
// for more information about ppm files.

#define Q(x) #x
#define QUOTE(x) Q(x)

std::string left_pad(std::string &str, const size_t width)
{
	    if (width > str.size()) {
			str.insert(0, width - str.size(), '0');
		}
		return str;
}

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

	void draw_rect(vec2 top_left, vec2 bottom_right, Pixel pixel, std::vector<std::vector<Pixel>>& buffer) {
		// vec2 is being used here to represent start and end points, instead of a snake segment
		for (int y = top_left.y; y < bottom_right.y; y++) {
			for (int x = top_left.x; x < bottom_right.x; x++) {
				buffer[y][x] = pixel;
			}
		}
	}

	void connect_segments(std::vector<std::vector<Pixel>>& buffer, Snake* snake) {
		unsigned int i = 0;
		do {
			vec2 s1 = snake->get_segment(i);
			vec2 s2 = snake->get_segment(i + 1);

			vec2 top_left = {
				std::min(s1.x, s2.x) * SCALAR + 2, 
				std::min(s1.y, s2.y) * SCALAR + 2, 
			};

			vec2 bottom_right = {
				std::max(s1.x, s2.x) * SCALAR + 5, 
				std::max(s1.y, s2.y) * SCALAR + 5, 
			};

			std::cout << "top left: (" 
				<< top_left.x << "," 
				<< top_left.y << ")"
				<< std::endl;

			std::cout << "bottom right: (" 
				<< bottom_right.x << "," 
				<< bottom_right.y << ")"
				<< std::endl;

			std::cout << std::endl;

			draw_rect(top_left, bottom_right, SNAKE_PIXEL, buffer);

			// unsigned int x_1 = segment_1.x * SCALAR;
			// unsigned int y_1 = segment_1.y * SCALAR;

		} while (++i < snake->get_size() - 1);
	}

	void draw_segment(unsigned int index, std::vector<std::vector<Pixel>>& buffer, Snake* snake) {
		vec2 segment = snake->get_segment(index);

		unsigned int x = segment.x * SCALAR;
		unsigned int y = segment.y * SCALAR;

		vec2 top_left = {x + 2, y + 2};
		vec2 bottom_right = {x + 5, y + 5};

		draw_rect(top_left, bottom_right, SNAKE_PIXEL, buffer);
	}

	void draw_snake(std::vector<std::vector<Pixel>>& buffer, Snake* snake) {
		for (unsigned int i = 0; i < snake->get_size(); i++) {
			draw_segment(i, buffer, snake);
		}

		connect_segments(buffer, snake);
	}

	void print_to_image(Snake* snake) {
		unsigned int b_width = snake->get_board_width();
		unsigned int b_height = snake->get_board_height();

		// get file name
		std::string filename = PREFIX;
		filename.append(snake->get_folder_name());
		filename.append("/");
		std::string filenumber = std::to_string(snake->get_next_frame_number());
		filename.append(left_pad(filenumber, 5));
		filename.append(".ppm");

		// create file stream
		std::ofstream ofs(
			filename,
			std::ios_base::out | std::ios_base::binary
		);

		ofs << 'P' << QUOTE(IMAGE_FORMAT)
			<< std::endl << b_width * SCALAR
			<< ' ' << b_height * SCALAR << std::endl
			<< "255" << std::endl;

		std::vector<std::vector<Pixel>> buffer = create_snake_buffer(snake);
		draw_borders(buffer, snake);
		draw_snake(buffer, snake);

		for (auto row : buffer) {
			 for (auto pixel : row) {
				write_pixel_to_ofstream(ofs, pixel);
			}
		}

		ofs.close();

	}

	void write_pixel_to_ofstream(std::ofstream& ofs, Pixel pixel) {
#if IMAGE_FORMAT == 6
		// write P6 format
		ofs << (char) pixel.r << (char) pixel.g << (char) pixel.b;
#else
		// write P3 format
		ofs << std::to_string(pixel.r) <<  ' ' <<
			std::to_string(pixel.g) <<  ' ' <<
			std::to_string(pixel.b) << std::endl;
#endif
	}
}
