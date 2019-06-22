#include "filesystem.h"

int write_file(const std::string& filename, const std::vector<std::string>& to_write)
{
	std::ofstream ofs(filename);

	if (! ofs.is_open())
		throw std::runtime_error("Error opening file for output");

	for (auto line : to_write) {
		ofs << line << std::endl;
	}
	ofs.close();
	return 0;
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

