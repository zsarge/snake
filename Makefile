snake:
	mkdir -p build # create build folder only if it doesn't alrealy exist
	g++ -std=c++17 -O2 -Wall src/main.cpp -o build/snake.out

	# run './build/snake.out' to run this project
