namespace AI {
	void print_debug_info(Snake*);
	snake_direction get_best_direction(Snake*);
	bool delta_is_valid(Snake*, int, int);
	bool front_is_clear(Snake*);
	snake_direction get_right_turn(snake_direction);
}
