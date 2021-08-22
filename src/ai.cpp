namespace AI {
	void print_test(Snake* snake) {
		std::cout 
			<< "snake ai:" << std::endl
			<< "(" << snake->get_segment(0).x
			<< "," << snake->get_segment(0).y
			<< ")" << std::endl;
	}
}
