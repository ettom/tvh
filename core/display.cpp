#include "display.h"
#define WINDOW_WIDTH 50
#define WINDOW_HEIGHT 7
#define LINE_START    2
#define LINE_LENGTH  WINDOW_WIDTH - 2 * LINE_START

Display::Display(const Settings& s, const std::vector<Show>& l, size_t n) :
	settings{s},
	all_shows{l},
	show_names_length{n}
{
	this->show_names = format_lines();
}

std::vector<std::string> Display::format_lines()
{
	std::vector<std::string> result;
	for (auto show : this->all_shows) {
		std::string show_names_entry = show.get_series_name();
		show_names_entry += " - ";
		show_names_entry += show.get_season_number();                          // Add the series name and season number together

		int current_line_length = show_names_entry.length();
		if (max_line_length < current_line_length)
			this->max_line_length = current_line_length;                   // Store the length of the longest line

		result.push_back(show_names_entry);                                    // Append series name + season number to vector
	}

	return result;
}

void Display::display_last_played_ep_name(int current_pos)
{
	std::string last_played = remove_extension(all_shows.at(current_pos).get_last_played_file()); // Get the name of the last played episode without extension
	char ch = clear_and_print(last_played);
	if (ch == 'f')
		open_dir_in_file_manager(settings.FILE_MANAGER, all_shows.at(current_pos).get_last_season_dir());
}


void Display::display_next_ep_name(int current_pos)
{
	std::string next_up = remove_extension(all_shows.at(current_pos).get_next_ep_name()); // Get the name of the next episode without extension
	if (next_up == "")
		next_up = "Next episode not found!";

	char ch = clear_and_print(next_up);
	if (ch == 'f')
		open_dir_in_file_manager(settings.FILE_MANAGER, all_shows.at(current_pos).get_next_season_dir());
}

void Display::print_menu(int to_highlight)
{
	size_t i = 0;
	char item[NAME_MAX]; // Max filename length, probably 255

	for(i = 0; i < this->show_names_length; ++i) {
		(i == to_highlight) ? wattron(w, A_STANDOUT) : wattroff(w, A_STANDOUT);
		sprintf(item, "%-7s",  this->show_names.at(i).c_str());
		mvwprintw(w, i + 1, LINE_START, "%s", item);
	}

	wattroff(w, A_STANDOUT);
}


char Display::clear_and_print(const std::string& toprint)
{
	char item[NAME_MAX];
	wclear(w);
	box(w, 0, 0);
	char ch;

	std::vector<std::string> lines = wrap_string_to_lines(toprint, LINE_LENGTH);
	int linenr = calc_line_to_start_printing(lines);

	do {
		for (auto i : lines) {
			std::string line = center_string(i, LINE_LENGTH);
			// char item[NAME_MAX] = {0};
			// sprintf(item, "%-7s", line.c_str());
			mvwprintw(w, linenr, LINE_START, "%s", line.c_str());
			++linenr;
		}
		ch = wgetch(w);
	} while (!ch);

	wclear(w);
	box(w, 0, 0);
	return ch;

}

void Display::delete_entry_from_menu(int current_pos)
{
	all_shows.erase(all_shows.begin() + current_pos);
	this->show_names_length -= 1;
	this->show_names = format_lines();
	wclear(w);
	box(w, 0, 0);
}

void Display::delete_entry_from_history(const std::string& series_name)
{
	std::vector<std::string> history_contents = readfile(this->settings.TV_HISTORY_FILE);
	std::regex rgx = std::regex(".*" + series_name + ".*");
	history_contents = delete_match_from_vector(history_contents, rgx);
	write_file(this->settings.TV_HISTORY_FILE, history_contents);

}

void Display::startup()
{
	initscr();                                     // Initialize Ncurses
	w = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, 0, 0); // Create a new window
	box(w, 0, 0);                                  // Sets default borders for the window

	print_menu(0);                                 // Print the menu
	wrefresh(w);                                   // Update the terminal screen

	noecho();                                      // Disable echoing of characters on the screen
	keypad(w, TRUE);                               // Enable keyboard input for the window.
	curs_set(0);                                   // Hide the default screen cursor.
}

void Display::cleanup()
{
	delwin(w);
	endwin();
}

void Display::draw_window()
{
	std::string next_ep_path;

	char item[NAME_MAX];
	int ch, i = 0;
	startup();

	while((ch = wgetch(w))){
		sprintf(item, "%-7s", show_names.at(i).c_str()); // Right pad with spaces to make the items appear with even width.
		mvwprintw(w, i + 1, LINE_START, "%s", item);
		// Use a variable to increment or decrement the value based on the input.
		switch(ch) {
		case KEY_LEFT: case 'h': case 'q':
			goto exit_loop;
		case KEY_UP: case 'k':
			--i;
			i = (i < 0) ? this->show_names_length - 1 : i;
			break;
		case KEY_DOWN: case 'j':
			++i;
			i = (i > this->show_names_length - 1) ? 0 : i;
			break;
		case KEY_RIGHT: case 'l':
			all_shows.at(i).set_next_ep_path();
			next_ep_path = all_shows.at(i).get_next_ep_path();
			if (next_ep_path == "") {
				clear_and_print("Next episode not found!");
				print_menu(i);
				continue;
			} else {
				all_shows.at(i).add_to_tracker_file();
				all_shows.at(i).add_to_history_file();
				play_video(settings.VIDEO_PLAYER, next_ep_path);
			}
			goto exit_loop;
		case 'p':
			display_last_played_ep_name(i); // Display the name of the last played episode
			print_menu(i);                  // Display the menu again
			continue;
			break;

		case 'n':
			display_next_ep_name(i);
			print_menu(i);
			continue;
			break;
		case 'f':
			open_dir_in_file_manager(settings.FILE_MANAGER, all_shows.at(i).get_last_season_dir());
			print_menu(i);
			continue;
			break;
		case 'd':
			delete_entry_from_history(all_shows.at(i).get_series_name());
			delete_entry_from_menu(i);
			if (this->show_names_length <= 0) {
				clear_and_print("Next episode not found!");
				goto exit_loop;
			}
			i = (i - 1 < 0) ? 0 : i - 1;
			print_menu(i);
			break;
		}

		wattron(w, A_STANDOUT); // Now highlight the next item in the list

		sprintf(item, "%-7s", show_names.at(i).c_str());
		mvwprintw(w, i + 1, LINE_START, "%s", item);
		wattroff(w, A_STANDOUT);
	}

exit_loop: ;
	   cleanup();
}
