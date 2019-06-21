#include "helpers.h"



std::string remove_extension(const std::string& filename) {
	size_t lastdot = filename.find_last_of(".");
	if (lastdot == std::string::npos)
		return filename;
	return filename.substr(0, lastdot);
}

std::vector<std::string> readfile(const std::string& filename)
{
	std::ifstream infile(filename);
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(infile, line)) {
		lines.push_back(line);
	}
	infile.close();
	return lines;
}

int write_file(const std::string& filename, const std::vector<std::string>& to_write)
{
	std::ofstream ofs(filename);

	if(! ofs) {
		throw std::runtime_error("Error opening file for output");
	}
	for (auto line : to_write) {
		ofs << line << std::endl;
	}
	ofs.close();
	return 0;
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

void play_video(const std::string& path_to_file)
{
	const std::string& cmd = "setsid " + settings.VIDEO_PLAYER + " \"" + path_to_file + "\" > /dev/null 2>&1 &";
	run_ext_cmd(cmd);
}

std::vector<std::string> lsdir(const std::string& dir_path)
{
	std::vector<std::string> dir_contents;

	try {
		for (const auto & entry : std::filesystem::directory_iterator(dir_path))
			dir_contents.push_back(entry.path());
	} catch (std::filesystem::filesystem_error&) {
	}

	return dir_contents;
}

std::string calculate_next(int last_number)
{
	std::string next_as_string = "";
	last_number++;
	if (last_number < 10)
		next_as_string += "0"; // Episode name must always contain two numbers eg. E01 not E1


	return next_as_string + std::to_string(last_number);
}

std::string extract_substring(const std::string& input, const std::regex& rgx)
{
	std::smatch match;

	if (std::regex_search(input.begin(), input.end(), match, rgx))
		return match[1];

	throw std::exception();
}

// Check if filename ends in one of the given filenames
bool ending_in(const std::string& filename, const std::vector<std::string>& endings)
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

std::string find_match_in_dir(const std::vector<std::string>& input, const std::string& to_search)
{
	std::regex rgx = std::regex(".*" + to_search + ".*");
	for (auto i : input) {
		if (std::regex_match(i, rgx) && !ending_in(i, settings.extensions_to_ignore))
			return i;
	}

	return "";
}

std::string get_parent_dir(const std::string& path)
{
	std::string parent_dir = "";
	try {
		parent_dir = static_cast<std::filesystem::path>(path).parent_path();
	}
	catch (std::filesystem::filesystem_error&) {
	}
	return parent_dir;
}

std::string get_absolute_path(const std::string& path)
{
	// Get absolute path and validate it
	// Throw exception if invalid path
	auto p = static_cast<std::filesystem::path>(path);
	std::ifstream test(p);
	if (!test)
	{
		throw std::runtime_error(p);
	}
	test.close();
	return std::filesystem::absolute(p);
}
