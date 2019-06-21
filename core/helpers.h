#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>
#include <filesystem>

#include "config.h"
#include "show.h"

int write_file(const std::string& filename, const std::vector<std::string>& to_write);
std::vector<std::string> readfile(const std::string& filename);
std::vector<std::string> lsdir(const std::string& dir_path);
std::vector<std::string> reverse_file_path(const std::string& input);

std::string remove_extension(const std::string& filename);
std::string calculate_next(int last_number);
std::string extract_substring(const std::string& input, const std::regex& rgx);
std::vector<std::string> find_matches_in_dir(const std::vector<std::string>& input, const std::string& to_search);
std::vector<std::string> filter_filenames_by_extension(const std::vector<std::string>& filenames, const std::vector<std::string>& extensions_to_ignore);
std::string get_parent_dir(const std::string& path);
std::string get_absolute_path(const std::string& path);
bool ends_in(const std::string& filename, const std::vector<std::string>& endings);


void play_video(const std::string& video_player, const std::string& path_to_file);
void open_dir_in_file_manager(const std::string& file_manager, const std::string& dir_path);
int run_ext_cmd(const std::string& cmd);
