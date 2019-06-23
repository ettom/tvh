#include "show.h"

std::string find_last_played(const std::string& last_season_dir)
{
	// Can be tested, pass tracker file contents as arguments, not sure if necessary
	// Return the contents of the .tracker file in the given season dir path
	std::string trackerfile = last_season_dir + "/.tracker";
	std::vector<std::string> lines = readfile(trackerfile);
	return get_first_element_otherwise_empty(lines);
}

Show::Show()
{
}

Show::Show(Settings s, std::string p, int n)
{
	this->settings = s;
	this->last_season_dir = p;
	this->line_number = n;

	this->TV_HISTORY_FILE = settings.TV_HISTORY_FILE;
	this->EXTENSIONS_TO_IGNORE = settings.EXTENSIONS_TO_IGNORE;

	set_series_name_season(last_season_dir);
}

Show::Show(Settings s, std::string p, std::string n)
{
	this->settings = s;
	this->next_ep_path = p;

	this->TV_HISTORY_FILE = settings.TV_HISTORY_FILE;
	this->EXTENSIONS_TO_IGNORE = settings.EXTENSIONS_TO_IGNORE;

	this->next_season_dir = n;

	set_series_name_season(this->next_season_dir);
}

Show::Show(Settings s, std::string p)
{
	this->settings = s;
	this->last_played_ep = p;

	this->TV_HISTORY_FILE = settings.TV_HISTORY_FILE;
	this->EXTENSIONS_TO_IGNORE = settings.EXTENSIONS_TO_IGNORE;

	set_series_name_season(get_parent_dir(last_played_ep));

}

void Show::set_series_name_season(std::string path)
{
	const std::vector<std::string>& lines = reverse_file_path(path);
	const std::tuple<std::string, std::string>& name_season = extract_series_name_season(lines, settings.SEASON_REGEX);
	this->series_name = std::get<0>(name_season);
	this->season_number = std::get<1>(name_season);

}

void Show::set_season_dir(std::string dir)
{
	this->last_season_dir = dir;
}


std::string Show::get_series_name()
{
	return this->series_name;
}

std::string Show::get_next_season_dir()
{
	return this->next_season_dir;
}

std::string Show::get_season_number()
{
	return this->season_number;
}

std::string Show::get_last_season_dir()
{
	return this->last_season_dir;
}

std::string Show::get_last_played_file()
{
	return this->last_played_ep;
}

std::string Show::get_last_played_path()
{
	return this->last_season_dir + '/' + this->last_played_ep;
}

std::string Show::get_next_ep_path()
{
	return this->next_ep_path;
}

std::string Show::find_next_season_dir()
{
	// Can probably be tested, not sure if necessary
	int last_season_number = std::stoi(extract_substring(last_played_ep, this->settings.SEASON_REGEX));
	std::string next_season_number = "S" + calculate_next(last_season_number);

	const std::string& parent_dir = get_parent_dir(this->last_season_dir);
	const std::vector<std::string>& dir_contents = lsdir(parent_dir);
	const std::vector<std::string>& dirs_matching_next_season_number = find_matches_in_vector(dir_contents, next_season_number);

	return get_first_element_otherwise_empty(dirs_matching_next_season_number);
}

std::string Show::find_first_ep_in_next_season_dir()
{
	// Can be tested, pass directory contents and extensions to ignore as arguments
	std::string next_season_dir = find_next_season_dir();
	std::vector<std::string> dir_contents = lsdir(this->next_season_dir);
	std::vector<std::string> matches_in_dir = find_matches_in_vector(dir_contents, "E01");
	std::vector<std::string> filtered_dir_contents = filter_filenames_by_extension(matches_in_dir, this->EXTENSIONS_TO_IGNORE);
	return get_first_element_otherwise_empty(filtered_dir_contents);
}

std::string Show::find_next_ep_in_this_season_dir(const std::string& next_ep_number)
{
	// Can be tested, pass directory contents and extensions to ignore as arguments
	std::vector<std::string> dir_contents = lsdir(this->last_season_dir);
	std::vector<std::string> matches_in_dir = find_matches_in_vector(dir_contents, next_ep_number);
	std::vector<std::string> filtered_dir_contents = filter_filenames_by_extension(matches_in_dir, this->EXTENSIONS_TO_IGNORE);
	return get_first_element_otherwise_empty(filtered_dir_contents);
}

void Show::set_next_ep_path()
{
	if (this->next_ep_path != "")
		return;
	std::string next_ep_path = "";
	int last_ep_number = std::stoi(extract_substring(this->last_played_ep, this->settings.EP_REGEX));
	std::string next_ep_number = "E" + calculate_next(last_ep_number);

	next_ep_path = find_next_ep_in_this_season_dir(next_ep_number);

	if (next_ep_path == "") { // There is no next episode in current season dir, try next season first episode
		next_ep_path = find_first_ep_in_next_season_dir();
	}

	this->next_ep_path = next_ep_path;
	this->next_season_dir = get_parent_dir(next_ep_path);
}

std::string Show::get_next_ep_name()
{
	// Can be tested, separate method for getting the first element of a reversed vector
	// Inputs - next ep path
	if (this->next_ep_path == "")
		this->set_next_ep_path();
	std::vector<std::string> reversed_path = reverse_file_path(this->next_ep_path);

	this->next_ep_name = get_first_element_otherwise_empty(reversed_path);
	return this->next_ep_name;
}

void Show::add_to_tracker_file()
{
	const std::vector<std::string>& to_write = {next_ep_path};
	write_file(this->next_season_dir + "/.tracker", to_write);
}

void Show::add_to_history_file()
{
	std::vector<std::string> history_contents = readfile(this->TV_HISTORY_FILE); // Read the current file contents

	std::regex rgx = std::regex(".*" + this->series_name + ".*");
	history_contents = delete_match_from_vector(history_contents, rgx);
	history_contents = insert_element_to_first_pos(history_contents, this->next_season_dir);
	history_contents = resize_vector_to_size(history_contents, settings.HISTORY_SIZE);
	write_file(this->TV_HISTORY_FILE, history_contents);
}
