#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

#include <ncurses.h>

#include "show.h"
#include "helpers.h"
#include "display.h"

const std::string& VIDEO_PLAYER = "mpv";
const std::vector<std::string> extensions_to_ignore {"sub", "srt", "ass"};
const size_t HISTORY_SIZE = 5;

std::string TV_HISTORY_FILE;
int LIST_LENGTH = 0;

std::map<int, Show> create_shows()
{
	// Create show objects for every directory name in the history file
	std::map<int, Show> all_shows;

	std::vector<std::string> lines = readfile(TV_HISTORY_FILE);
	for (std::string line : lines) {
		Show show(line, LIST_LENGTH);  // Create show object
		all_shows[LIST_LENGTH] = show; // Assign to map where key is the current line number and object is the value

		LIST_LENGTH++;
	}

	return all_shows;
}

void launch_menu()
{
	const std::map<int, Show>& showmap = create_shows();
	Display disp(showmap); // Create display object

	if (showmap.empty()) {
		disp.startup();
		disp.clear_and_print("No shows in history!");
		disp.cleanup();
	} else {
		disp.draw_window();
	}
}


int main(int argc, char *argv[])
{
	std::string env_HOME = std::getenv("HOME");
	TV_HISTORY_FILE = env_HOME + "/.local/share/tvhistory";

	if (argc > 1) { // If a filename is passed
		std::string path_to_file;
		try {
			path_to_file = get_absolute_path(argv[1]);
		} catch (std::runtime_error&) {
			std::cout << "Cannot access " << argv[1] << " , no such file." << std::endl;
			return 1;
		}

		play_video(path_to_file);

		std::regex rgx(".*E([0-9]+).*");
		if (std::regex_match(path_to_file, rgx)) { // If path is an episode file
			Show show(path_to_file);           // Create show object
			show.add_to_tracker_file();        // Write filename to .tracker file in same directory
			show.add_to_history_file();        // Write the directory of the file to the global history file
		}
	} else {
		launch_menu();
	}

	return 0;
}
