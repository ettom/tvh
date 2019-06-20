#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <regex>
#include <iostream>
#include <regex>

#include "helpers.h"
#include "config.h"

extern std::string TV_HISTORY_FILE;
extern const size_t HISTORY_SIZE;
std::tuple<std::string, std::string> extract_series_name_season(const std::vector<std::string>&);
std::string find_last_played(const std::string&);



class Show
{
	public:
		Show();                                                // Default constructor
		Show(std::string next_ep_path);                        // Constructor for passing a filename
		Show(std::string season_folder_path, int line_number); // Constructor for passing the season dir and a menu position
		std::string get_series_name();
		std::string get_season_number();
		std::string get_season_folder_path();
		std::string get_last_played_file();
		std::string get_last_played_path();
		std::string get_next_ep_path();
		std::string get_next_ep_name();
		std::string get_next_ep_parent_dir();

		void set_next_ep_path();
		void add_to_tracker_file();
		void add_to_history_file();

	private:
		std::string find_next_season_path();

		int line_number;
		std::string next_ep_path;
		std::string next_ep_name;
		std::string season_folder_path;
		std::string season_number;
		std::string series_name;
		std::string last_played_ep;
		std::string next_ep_parent_dir;

};
