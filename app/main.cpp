#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

#include <ncurses.h>

#include "show.h"
#include "helpers.h"
#include "display.h"
#include "init_menu.h"
#include "filesystem.h"


int main(int argc, char *argv[])
{
	Settings settings;

	std::string env_HOME = std::getenv("HOME");
	std::string TV_HISTORY_FILE = env_HOME + settings.TV_HISTORY_FILE;

	settings.TV_HISTORY_FILE = TV_HISTORY_FILE;

	if (argc > 1) { // If a filename is passed
		std::string path_to_file;
		try {
			path_to_file = get_absolute_path(argv[1]);
		} catch (std::runtime_error&) {
			std::cout << "Cannot access " << argv[1] << " , no such file." << std::endl;
			return 1;
		}

		play_video(settings.VIDEO_PLAYER, path_to_file);

		std::regex rgx(".*E([0-9]+).*");
		if (std::regex_match(path_to_file, rgx)) {                             // If path is an ep file
			std::string next_season_dir = get_parent_dir(path_to_file);
			Show show(settings, path_to_file, next_season_dir);         // Create show object
			show.add_to_tracker_file();                                    // Write filename to .tracker file in same dir
			show.add_to_history_file();                                    // Write the dir of the file to the global history file
		}
	} else {
		std::string working_dir = std::filesystem::current_path();
		std::vector<std::string> dircontents = lsdir(working_dir);
		if (!find_matches_in_vector(dircontents, ".tracker").empty()) { // Dir contains .tracker file
			std::string last_played_path = working_dir + "/" + get_first_element_otherwise_empty(readfile(working_dir + "/.tracker"));
			Show show(settings, last_played_path);         // Create show object
			show.set_season_dir(working_dir);
			show.set_next_season_dir(last_played_path);
			show.set_next_ep_path();
			play_video(settings.VIDEO_PLAYER, show.get_next_ep_path());
			show.add_to_tracker_file();
			show.add_to_history_file();
		} else {
			launch_menu(settings);
		}
	}

	return 0;
}
