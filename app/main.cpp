#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

#include <ncurses.h>

#include "show.h"
#include "helpers.h"
#include "display.h"
#include "init.h"
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

		play_passed_filename(settings, path_to_file);
	} else {
		std::string working_dir = std::filesystem::current_path();
		std::vector<std::string> dir_contents = lsdir(working_dir);

		if (! find_matches_in_vector(dir_contents, ".tracker").empty()) {	// Dir contains .tracker file
			play_next_from_dir(settings, working_dir);
		} else {
			launch_menu(settings);
		}
	}

	return 0;
}
