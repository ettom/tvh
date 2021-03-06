#pragma once

#include <climits>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <ncurses.h>

#include "config.h"
#include "extcmd.h"
#include "helpers.h"
#include "show.h"

class Display
{
public:
	Display(const Settings& settings, const std::vector<Show>& all_shows, size_t show_names_length);
	~Display();
	void startup();
	void draw_window();
	char clear_and_print(const std::string& toprint);

private:
	Settings settings;
	size_t show_names_length;
	void display_last_played_ep_name(int current_pos);
	void display_next_ep_name(int current_pos);
	void print_menu(int to_highlight);
	void delete_entry_from_menu(int current_pos);
	void delete_entry_from_history(const std::string& series_name);
	std::vector<std::string> format_lines();

	WINDOW* w;
	std::vector<Show> all_shows;
	std::vector<std::string> show_names;
	int max_line_length = 0;
};
