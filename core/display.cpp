#include "display.h"

Display::Display(Settings s, std::map<int, Show> m, size_t n) 	// Constructor
{
	this->settings = s;
	this->showmap = m;
	this->list_length = n;
	this->list = format_lines();
}

std::vector<std::string> Display::format_lines()
{
	for(auto [key, val] : this->showmap)                                     // Iterate over show objects in map
	{
		std::string list_entry = val.get_series_name();
		list_entry += " - ";
		list_entry += val.get_season_number();                           // Add the series name and season number together

		int current_line_length = static_cast<int>(list_entry.length());
		if (max_line_length < current_line_length)
			this->max_line_length = current_line_length;             // Store the length of the longest line

		list.push_back(list_entry);                                      // Append series name + season number to vector
	}

	return list;
}

void Display::display_last_played_ep_name(int current_pos)
{
	std::string last_played = remove_extension(showmap.at(current_pos).get_last_played_file()); // Get the name of the last played episode without extension
	char ch = clear_and_print(last_played);
	if (ch == 'f')
		open_dir_in_file_manager(settings.FILE_MANAGER, showmap.at(current_pos).get_season_dir_path());
}


void Display::display_next_ep_name(int current_pos)
{
	std::string next_up = remove_extension(showmap.at(current_pos).get_next_ep_name());         // Get the name of the next episode without extension
	if (next_up == "")
		next_up = "Next episode not found!";

	char ch = clear_and_print(next_up);
	if (ch == 'f')
		open_dir_in_file_manager(settings.FILE_MANAGER, showmap.at(current_pos).get_next_ep_parent_dir());
}

void Display::print_menu(int to_highlight)
{
	int i = 0;
	char item[NAME_MAX]; // Max filename length, probably 255

	for(i = 0; i < this->list_length; ++i) {
		(i == to_highlight) ? wattron(w, A_STANDOUT) : wattroff(w, A_STANDOUT);
		sprintf(item, "%-7s",  this->list.at(static_cast<size_t>(i)).c_str());
		mvwprintw(w, i + 1, 2, "%s", item);
	}

	wattroff(w, A_STANDOUT);
}

char Display::clear_and_print(const std::string& toprint)
{
	char item[NAME_MAX];
	wclear(w);
	box(w, 0, 0);
	char ch ;

	do {
		ch = 0;
		sprintf(item, "%-7s", toprint.c_str());
		mvwprintw(w, 3, 5, "%s", item);
		ch = wgetch(w);

	} while (!ch);

	std::cout << ch << std::endl;

	wclear(w);
	box(w, 0, 0);
	return ch;

}

void Display::startup()
{
	initscr();               // initialize Ncurses
	w = newwin(7, 50, 0, 0); // create a new window
	box(w, 0, 0);            // sets default borders for the window

	print_menu(0);           // print the menu
	wrefresh(w);             // update the terminal screen

	noecho();                // disable echoing of characters on the screen
	keypad(w, TRUE);         // enable keyboard input for the window.
	curs_set(0);             // hide the default screen cursor.
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

	while((ch = wgetch(w))){                                                // get the input
		sprintf(item, "%-7s", list.at(static_cast<size_t>(i)).c_str()); // right pad with spaces to make the items appear with even width.
		mvwprintw(w, i + 1, 2, "%s", item);
		// use a variable to increment or decrement the value based on the input.
		switch(ch) {
		case KEY_LEFT: case 'h': case 'q':
			goto exit_loop;
		case KEY_UP: case 'k':
			i--;
			i = (i < 0) ? this->list_length - 1 : i;
			break;
		case KEY_DOWN: case 'j':
			i++;
			i = (i > this->list_length - 1) ? 0 : i;
			break;
		case KEY_RIGHT: case 'l':
			showmap.at(i).set_next_ep_path();                   // Set the next episode for the object
			next_ep_path = showmap.at(i).get_next_ep_path();
			if (next_ep_path == "") {
				clear_and_print("Next episode not found!");
				print_menu(i);
				continue;
			} else {
				showmap.at(i).add_to_tracker_file();
				showmap.at(i).add_to_history_file();
				play_video(settings.VIDEO_PLAYER, next_ep_path);
			}
			goto exit_loop;
		case 'p':
			display_last_played_ep_name(i);                     // Display the name of the last played episode
			print_menu(i);                                      // Display the menu again
			continue;
			break;

		case 'n':
			display_next_ep_name(i);
			print_menu(i);
			continue;
			break;
		case 'f':
			std::string dir = showmap.at(i).get_season_dir_path();
			open_dir_in_file_manager(settings.FILE_MANAGER, dir);;
			print_menu(i);
			continue;
			break;
		}

		wattron(w, A_STANDOUT); // now highlight the next item in the list.

		sprintf(item, "%-7s", list.at(static_cast<size_t>(i)).c_str());
		mvwprintw(w, i + 1, 2, "%s", item);
		wattroff(w, A_STANDOUT);
	}

exit_loop: ;
	   cleanup();
	   return;
}
