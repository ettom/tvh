#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits.h>

#include <ncurses.h>

#include "show.h"
#include "helpers.h"
#include "config.h"
#include "extcmd.h"

class Display
{
	public:
		Display(Settings settings, const std::map<int, Show> showmap, size_t list_length);
		void startup();
		void cleanup();
		void draw_window();
		char clear_and_print(const std::string& toprint);
	private:
		Settings settings;
		size_t list_length;
		void display_last_played_ep_name(int current_pos);
		void display_next_ep_name(int current_pos);
		void print_menu(int to_highlight);
		std::vector<std::string> format_lines();

		WINDOW *w;
		std::map<int, Show> showmap;
		std::vector<std::string> list;
		int max_line_length = 0;
};
