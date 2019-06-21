#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <regex>
#include <iostream>
#include <regex>

#include "show_logic.h"
#include "helpers.h"
#include "config.h"


std::tuple<std::string, std::string> extract_series_name_season(const std::vector<std::string>&);
std::string find_last_played(const std::string&);



class Show
{
	public:
		// Default constructor
		Show();
		// Constructor for passing the season dir and a menu position - launched normally
		Show(Settings settings, std::string season_dir_path, int line_number);
		// Constructor for passing a filename - launched as a wrapper to video player
		Show(Settings settings, std::string next_ep_path, std::string next_ep_parent_dir);

		std::string get_series_name();
		std::string get_season_number();
		std::string get_season_dir_path();
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
		Settings settings;

		int line_number;
		std::string find_first_ep_in_next_season_dir();
		std::string find_next_ep_in_this_season_dir(const std::string& next_ep_number);
		std::vector<std::string> extensions_to_ignore;
		std::string tv_history_file;
		std::string next_ep_path;
		std::string next_ep_name;
		std::string season_dir_path;
		std::string season_number;
		std::string series_name;
		std::string last_played_ep;
		std::string next_ep_parent_dir;
		std::regex ep_regex = std::regex("E([0-9]+)");
		std::regex season_regex = std::regex("S([0-9]+)");

};
