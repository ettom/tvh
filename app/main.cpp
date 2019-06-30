#include <string>
#include <vector>
#include <locale.h>

#include <ncurses.h>

#include "init.h"
#include "filesystem.h"
#include "config.h"
#include "helpers.h"



int main(int argc, char *argv[])
{
	setlocale(LC_ALL, ""); // Locale should be set correctly on the host machine
	Settings settings;

	std::string env_HOME = std::getenv("HOME");
	std::string TV_HISTORY_FILE = env_HOME + settings.TV_HISTORY_FILE;

	settings.TV_HISTORY_FILE = TV_HISTORY_FILE;

	int exit_code = 0;

	if (argc > 1) { // If a filename is passed
		std::string path_to_file;
		try {
			path_to_file = get_absolute_path(argv[1]);
			play_passed_filename(settings, path_to_file);
		} catch (std::runtime_error&) {
			std::cout << "Cannot access " << argv[1] << " , no such file." << std::endl;
			exit_code = 1;
		}

	} else {
		std::string working_dir = std::filesystem::current_path();
		std::vector<std::string> dir_contents = lsdir(working_dir);

		if (! find_matches_in_vector(dir_contents, ".tracker").empty()) {	// Dir contains .tracker file
			exit_code = play_next_from_dir(settings, working_dir);
		} else {
			launch_menu(settings);
		}
	}

	return exit_code;
}
