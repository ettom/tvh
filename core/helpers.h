#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>
#include <filesystem>

#include "config.h"
#include "show.h"

extern Settings settings;

int write_file(const std::string& filename, const std::vector<std::string>& to_write);
std::vector<std::string> readfile(const std::string& filename);
std::vector<std::string> lsdir(const std::string& dir_path);
std::vector<std::string> reverse_file_path(const std::string& input);

std::string remove_extension(const std::string& filename);
std::string calculate_next(int last_number);
std::string extract_substring(const std::string& input, const std::regex& rgx);
std::string find_match_in_dir(const std::vector<std::string>& input, const std::string& substr);
std::string get_parent_dir(const std::string& path);
std::string get_absolute_path(const std::string& path);


void play_video(const std::string& path_to_file);
int run_ext_cmd(const std::string& cmd);
