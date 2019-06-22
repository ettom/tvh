#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>

#include "config.h"
#include "show.h"
#include "filesystem.h"

void open_dir_in_file_manager(const std::string& file_manager, const std::string& dir_path);
void play_video(const std::string& video_player, const std::string& path_to_file);
int run_ext_cmd(const std::string& cmd);


std::tuple<std::string, std::string> extract_series_name_season(const std::vector<std::string>& lines);
std::vector<std::string> reverse_file_path(const std::string& input);
std::string remove_extension(const std::string& filename);
std::string calculate_next(int last_number);
std::string extract_substring(const std::string& input, const std::regex& rgx);
std::vector<std::string> find_matches_in_vector(const std::vector<std::string>& input, const std::string& to_search);
std::vector<std::string> filter_filenames_by_extension(const std::vector<std::string>& filenames, const std::vector<std::string>& extensions_to_ignore);
bool ends_in(const std::string& filename, const std::vector<std::string>& endings);

std::vector<std::string> delete_match_from_vector(std::vector<std::string>& input, const std::regex& to_match);
std::vector<std::string> insert_element_to_first_pos(std::vector<std::string>& input, const std::string& element);
std::vector<std::string> resize_vector_to_size(std::vector<std::string>& input, int target_size);
