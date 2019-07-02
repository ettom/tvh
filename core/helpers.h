#pragma once
#include <string>
#include <vector>
#include <regex>

#include "config.h"
#include "show.h"
#include "filesystem.h"

std::tuple<std::string, std::string> extract_series_name_season(const std::vector<std::string>& lines, const std::regex& SEASON_REGEX);
std::vector<std::string> reverse_file_path(const std::string& input);
std::string remove_extension(const std::string& filename);
std::string calculate_next(int last_number);
std::string extract_substring(const std::string& input, const std::regex& rgx);
std::vector<std::string> find_matches_in_vector(const std::vector<std::string>& input, const std::string& to_search);
std::vector<std::string> filter_filenames_by_extension(const std::vector<std::string>& filenames, const std::vector<std::string>& EXTENSIONS_TO_IGNORE);
bool ends_in(const std::string& filename, const std::vector<std::string>& endings);

std::vector<std::string> delete_match_from_vector(std::vector<std::string>& input, const std::regex& to_match);
std::vector<std::string> insert_element_to_first_pos(std::vector<std::string>& input, const std::string& element);
std::vector<std::string> resize_vector_to_size(std::vector<std::string>& input, int target_size);
std::string get_first_element_otherwise_empty(const std::vector<std::string>& input);
std::vector<std::string> wrap_string_to_lines(std::string source, std::size_t width, std::string whitespace = " \t\r");
int calc_line_to_start_printing(std::vector<std::string> lines);
std::string center_string(const std::string& s, const int w);
