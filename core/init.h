#pragma once

#include "show.h"
#include "display.h"
#include "filesystem.h"

std::vector<Show> create_shows(const Settings& settings)
{
	// Create show objects for every dir name in the history file
	std::vector<Show> all_shows;
	Path p;

	std::vector<std::string> lines = readfile(settings.TV_HISTORY_FILE);
	for (std::string line : lines) {
		p.last_season_dir = line;
		p.last_played_ep = find_last_played(line);
		Show show(settings, p); // Create show object
		all_shows.push_back(show);
	}

	return all_shows;
}

void play_passed_filename(const Settings& settings, const std::string& path_to_file)
{
	play_video(settings.VIDEO_PLAYER, path_to_file);
	Path p;

	std::regex rgx(".*E([0-9]+).*");
	if (std::regex_match(path_to_file, rgx)) {                // If path is an ep file
		p.next_season_dir = get_parent_dir(path_to_file);
		p.next_ep_path = path_to_file;
		Show show(settings, p);                           // Create show object
		show.add_to_tracker_file();                       // Write filename to .tracker file in same dir
		show.add_to_history_file();                       // Write the dir of the file to the global history file
	}
}

void play_next_from_dir(const Settings& settings, const std::string& working_dir)
{
	Path p;
	p.last_played_ep = working_dir + "/" + get_first_element_otherwise_empty(readfile(working_dir + "/.tracker"));
	p.last_season_dir = get_parent_dir(p.last_played_ep);
	Show show(settings, p);
	show.set_season_dir(working_dir);
	show.set_next_ep_path();
	std::string next_ep_path = show.get_next_ep_path();
	if (! next_ep_path.empty()) {
		play_video(settings.VIDEO_PLAYER, show.get_next_ep_path());
		show.add_to_tracker_file();
		show.add_to_history_file();
	}
}

void launch_menu(const Settings& settings)
{
	std::vector<Show> all_shows = create_shows(settings);
	size_t list_length = all_shows.size();
	Display disp(settings, all_shows, list_length); // Create display object

	if (all_shows.empty()) {
		disp.startup();
		disp.clear_and_print("No shows in history!");
		disp.cleanup();
	} else {
		disp.draw_window();
	}
}
