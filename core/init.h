#pragma once

#include "show.h"
#include "display.h"
#include "filesystem.h"

std::map<int, Show> create_shows(Settings settings)
{
	// Create show objects for every dir name in the history file
	std::map<int, Show> all_shows;

	std::vector<std::string> lines = readfile(settings.TV_HISTORY_FILE);
	int current_line_number = 0;
	for (std::string line : lines) {
		Show show(settings, line, current_line_number); // Create show object
		all_shows[current_line_number] = show;          // Assign to map where key is the current line number and object is the value
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

void play_passed_filename(Settings settings, std::string path_to_file)
{
	play_video(settings.VIDEO_PLAYER, path_to_file);

	std::regex rgx(".*E([0-9]+).*");
	if (std::regex_match(path_to_file, rgx)) {                          // If path is an ep file
		std::string next_season_dir = get_parent_dir(path_to_file);
		Show show(settings, path_to_file, next_season_dir);         // Create show object
		show.add_to_tracker_file();                                 // Write filename to .tracker file in same dir
		show.add_to_history_file();                                 // Write the dir of the file to the global history file
	}
}

void play_next_from_dir(Settings settings, std::string working_dir)
{
	std::string last_played_path = working_dir + "/" + get_first_element_otherwise_empty(readfile(working_dir + "/.tracker"));
	Show show(settings, last_played_path);
	show.set_season_dir(working_dir);
	// show.set_next_season_dir();
	show.set_next_ep_path();
	play_video(settings.VIDEO_PLAYER, show.get_next_ep_path());
	show.add_to_tracker_file();
	show.add_to_history_file();
}

