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



int main(int argc, char *argv[])
{
	std::string env_HOME = std::getenv("HOME");
	std::string tv_history_file = env_HOME + "/.local/share/tvhistory";
	Settings settings;
	settings.tv_history_file = tv_history_file;

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
		if (std::regex_match(path_to_file, rgx)) { // If path is an ep file
			Show show(settings, path_to_file); // Create show object
			show.add_to_tracker_file();        // Write filename to .tracker file in same dir
			show.add_to_history_file();        // Write the dir of the file to the global history file
		}
	} else {
		launch_menu(settings);
	}

	return 0;
}
