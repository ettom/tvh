#include "show.h"

std::tuple<std::string, std::string> extract_series_name_season(const std::vector<std::string>& lines)
{
	std::string series_name;
	std::string season;

	std::regex r("S[0-9]{2}.*");              // If string starts with Sxx, it's the season folder

	int season_seen = 0;
	for (auto line : lines) {

		if (season_seen) {                // If we have seen the season number, assume the next folder is the name of the show
			series_name = line;
			break;
		}
		if (std::regex_match (line, r)) { // Check if line is a season folder
			season = line;
			season_seen = 1;
		} else {
			series_name = line;       // If it's not, assume it's the name of the show
			season = "S01";           // Therefore the show only has one season, set season number to S01
			break;
		}
	}

	return std::make_tuple(series_name, season);
}

std::string find_last_played(const std::string& season_folder_path)
{
	// Return the contents of the .tracker file in the given season folder path
	std::string trackerfile = season_folder_path + "/.tracker";
	std::vector<std::string> lines = readfile(trackerfile);

	if (lines.empty())
		lines.push_back("");
	return lines.at(0);
}

Show::Show()
{
}

Show::Show(std::string p, int n)
{
	season_folder_path = p;
	line_number = n;

	const std::vector<std::string>& lines = reverse_file_path(season_folder_path);
	const std::tuple<std::string, std::string>& name_season = extract_series_name_season(lines);
	series_name = std::get<0>(name_season);
	season_number = std::get<1>(name_season);

	last_played_ep = find_last_played(season_folder_path);
	next_ep_path = "";

}

Show::Show(std::string p)
{
	this->next_ep_path = p;
	this->next_ep_parent_dir = get_parent_dir(this->next_ep_path);

	const std::vector<std::string>& lines = reverse_file_path(next_ep_parent_dir);
	const std::tuple<std::string, std::string>& name_season = extract_series_name_season(lines);

	series_name = std::get<0>(name_season);
	season_number = std::get<1>(name_season);
}


std::string Show::get_series_name()
{
	return this->series_name;
}

std::string Show::get_season_number()
{
	return this->season_number;
}

std::string Show::get_season_folder_path()
{
	return this->season_folder_path;
}

std::string Show::get_last_played_file()
{
	return this->last_played_ep;
}

std::string Show::get_last_played_path()
{
	return this->season_folder_path + '/' + this->last_played_ep;
}

std::string Show::get_next_ep_path()
{
	return this->next_ep_path;
}

std::string Show::find_next_season_path()
{
	std::regex rgx("S([0-9]+)");
	int last_season_number = std::stoi(extract_substring(last_played_ep, rgx));
	std::string next_season_number = "S" + calculate_next(last_season_number);

	const std::string& parent_dir = get_parent_dir(this->season_folder_path);
	const std::vector<std::string>& dir_contents = lsdir(parent_dir);

	return find_match_in_dir(dir_contents, next_season_number);
}

void Show::set_next_ep_path()
{
	if (this->next_ep_path != "")
		return;
	std::string next_ep_path;

	std::regex rgx("E([0-9]+)");
	int last_ep_number = std::stoi(extract_substring(this->last_played_ep, rgx));
	std::string next_ep_number = "E" + calculate_next(last_ep_number);

	std::vector<std::string> dir_contents = lsdir(this->season_folder_path);
	next_ep_path = find_match_in_dir(dir_contents, next_ep_number);

	if (next_ep_path == "") {
		std::string next_season_path = find_next_season_path();
		dir_contents = lsdir(next_season_path);
		next_ep_path = find_match_in_dir(dir_contents, "E01");
	}

	this->next_ep_path = next_ep_path;
	this->next_ep_parent_dir = get_parent_dir(next_ep_path);
}

std::string Show::get_next_ep_name()
{
	if (this->next_ep_path == "")
		this->set_next_ep_path();
	std::vector<std::string> reversed_path = reverse_file_path(this->next_ep_path);
	if (reversed_path.empty())
		reversed_path.push_back("");

	this->next_ep_name = reversed_path.at(0);
	return this->next_ep_name;
}

void Show::add_to_tracker_file()
{
	const std::vector<std::string>& to_write = {next_ep_path};
	write_file(this->next_ep_parent_dir + "/.tracker", to_write);
}

void Show::add_to_history_file()
{
	std::vector<std::string> history_contents = readfile(settings.TV_HISTORY_FILE); // Read the current file contents

	std::regex rgx = std::regex(".*" + series_name + ".*");
	std::string to_delete = "";

	// Delete the line that contains the name of the current show
	for (auto line : history_contents) {
		if (std::regex_match(line, rgx))
			to_delete = line;
	}
	history_contents.erase(std::remove(history_contents.begin(), history_contents.end(), to_delete), history_contents.end());

	// Put the parent dir of the next episode to the first line
	history_contents.insert(history_contents.begin(), this->next_ep_parent_dir);

	// Keep the number of lines at specified length
	if (history_contents.size() > settings.HISTORY_SIZE)
		history_contents.resize(settings.HISTORY_SIZE);

	write_file(settings.TV_HISTORY_FILE, history_contents);
}
