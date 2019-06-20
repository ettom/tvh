#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <limits.h>

#include <ncurses.h>

#include "show.h"
#include "helpers.h"
#include "config.h"

extern Settings settings;

class Display
{
	public:
		Display(const std::map<int, Show> showmap);
		void startup();
		void cleanup();
		void draw_window();
		char clear_and_print(const std::string& toprint);
	private:
		void display_last_played_ep_name(int current_pos);
		void display_next_ep_name(int current_pos);
		void print_menu(int to_highlight);
		std::vector<std::string> format_lines();

		WINDOW *w;
		std::map<int, Show> showmap;
		std::vector<std::string> list;
		int max_line_length = 0;
};
