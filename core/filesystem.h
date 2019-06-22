#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>
#include <filesystem>

int write_file(const std::string& filename, const std::vector<std::string>& to_write);
std::vector<std::string> readfile(const std::string& filename);
std::vector<std::string> lsdir(const std::string& dir_path);
std::string get_absolute_path(const std::string& path);
std::string get_parent_dir(const std::string& path);
