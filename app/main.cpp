#include <string>
#include <vector>
#include <clocale>

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


	if (argc > 1) { // If a filename is passed
		std::string path_to_file;
		try {
			path_to_file = get_absolute_path(argv[1]);
		} catch (const std::runtime_error&) {
			std::cerr << "Cannot open " << argv[1] << "." << std::endl;
			return EXIT_FAILURE;
		}
		play_passed_filename(settings, path_to_file);

	} else {
		std::string working_dir = std::filesystem::current_path();
		std::vector<std::string> dir_contents = lsdir(working_dir);

		if (! find_matches_in_vector(dir_contents, ".tracker").empty()) { // Dir contains .tracker file
			try {
				play_next_from_dir(settings, working_dir);
			} catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
				return EXIT_FAILURE;
			}
		} else {
			launch_menu(settings);
		}
	}

	return EXIT_SUCCESS;
}
