#pragma once

#include "show.h"
#include "display.h"
#include "filesystem.h"

std::map<int, Show> create_shows(Settings settings)
{
	// Create show objects for every dir name in the history file
	std::map<int, Show> all_shows;

	std::vector<std::string> lines = readfile(settings.tv_history_file);
	int current_line_number = 0;
	for (std::string line : lines) {
		Show show(settings, line, current_line_number); // Create show object
		all_shows[current_line_number] = show;                           // Assign to map where key is the current line number and object is the value
		current_line_number++;
	}

	return all_shows;
}

void launch_menu(Settings settings)
{
	const std::map<int, Show>& showmap = create_shows(settings);
	size_t list_length = showmap.size();
	Display disp(settings, showmap, list_length); // Create display object

	if (showmap.empty()) {
		disp.startup();
		disp.clear_and_print("No shows in history!");
		disp.cleanup();
	} else {
		disp.draw_window();
	}
}

