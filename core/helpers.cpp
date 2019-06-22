#include "helpers.h"

std::string remove_extension(const std::string& filename) {
	size_t lastdot = filename.find_last_of(".");
	if (lastdot == std::string::npos)
		return filename;
	return filename.substr(0, lastdot);
}


std::vector<std::string> reverse_file_path(const std::string& input)
{
	std::istringstream string_stream(input);

	std::string line;
	std::vector<std::string> lines;
	while (std::getline(string_stream, line, '/')) {
		if (!line.empty())
			lines.push_back(line);
	}
	std::reverse(lines.begin(),lines.end());
	return lines;
}

int run_ext_cmd(const std::string& cmd)
{
	int status = system(cmd.c_str());
	return status;
}

void play_video(const std::string& video_player, const std::string& path_to_file)
{
	const std::string& cmd = "setsid " + video_player + " \"" + path_to_file + "\" > /dev/null 2>&1 &";
	run_ext_cmd(cmd);
}

void open_dir_in_file_manager(const std::string& file_manager, const std::string& dir_path)
{
	const std::string& cmd = "setsid " + file_manager + " \"" + dir_path + "\" > /dev/null 2>&1 &";
	run_ext_cmd(cmd);
}

std::string calculate_next(int last_number)
{
	std::string next_as_string = "";
	last_number++;
	if (last_number < 10)
		next_as_string += "0";


	return next_as_string + std::to_string(last_number);
}

std::string extract_substring(const std::string& input, const std::regex& rgx)
{
	std::smatch match;

	if (std::regex_search(input.begin(), input.end(), match, rgx))
		return match[1];

	throw std::exception();
}

bool ends_in(const std::string& filename, const std::vector<std::string>& endings)
{
	bool ends_in;
	for (auto ending : endings) {
		if (filename.length() >= ending.length()) {
			ends_in = (0 == filename.compare (filename.length() - ending.length(), ending.length(), ending));
			if (ends_in)
				return true;
		}
	}

	return false;
}

std::vector<std::string> find_matches_in_vector(const std::vector<std::string>& input, const std::string& to_search)
{
	std::regex rgx = std::regex(".*" + to_search + ".*");
	std::vector<std::string> result;
	for (auto i : input) {
		if (std::regex_match(i, rgx))
			result.push_back(i);
	}

	return result;
}

std::vector<std::string> filter_filenames_by_extension(const std::vector<std::string>& filenames, const std::vector<std::string>& extensions_to_ignore)
{
	std::vector<std::string> result;
	for (auto i : filenames) {
		if (!ends_in(i, extensions_to_ignore))
			result.push_back(i);
	}

	return result;
}


std::tuple<std::string, std::string> extract_series_name_season(const std::vector<std::string>& lines)
{
	std::string series_name;
	std::string season;

	std::regex r("S[0-9]{2}.*");              // If string starts with Sxx, it's the season dir

	int season_seen = 0;
	for (auto line : lines) {

		if (season_seen) {                // If we have seen the season number, assume the next dir is the name of the show
			series_name = line;
			break;
		}
		if (std::regex_match (line, r)) { // Check if line is a season dir
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

std::vector<std::string> resize_vector_to_size(std::vector<std::string>& input, int target_size)
{
	if (input.size() > target_size)
		input.resize(target_size);
	return input;

}

std::vector<std::string> delete_match_from_vector(std::vector<std::string>& input, const std::regex& rgx)
{

	std::string to_delete = "";
	for (std::string line : input) {
		if (std::regex_match(line, rgx))
			to_delete = line;
	}
	input.erase(std::remove(input.begin(), input.end(), to_delete), input.end());
	return input;

}

std::vector<std::string> insert_element_to_first_pos(std::vector<std::string>& input, const std::string& element)
{
	input.insert(input.begin(), element);
	return input;
}


std::vector<std::string> get_first_element_(std::vector<std::string>& input, const std::string& element)
{
	input.insert(input.begin(), element);
	return input;
}
