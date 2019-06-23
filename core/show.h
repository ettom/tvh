#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <regex>
#include <iostream>
#include <regex>

#include "helpers.h"
#include "config.h"
#include "filesystem.h"


std::string find_last_played(const std::string&);

class Show
{
	public:
		// Default constructor
		Show();
		// Constructor for passing the season dir and a menu position - launched without arguments
		Show(Settings settings, std::string last_season_dir, int line_number);
		// Constructor for passing a filename(next episode) - launched as a wrapper to video player
		Show(Settings settings, std::string next_ep_path, std::string next_season_dir);
		// Constructor for passing a filename(last episode) - launched without arguments in a show dir
		Show(Settings settings, std::string last_ep_path);

		std::string get_series_name();
		std::string get_season_number();
		std::string get_last_season_dir();
		std::string get_last_played_file();
		std::string get_last_played_path();
		std::string get_next_ep_path();
		std::string get_next_ep_name();
		std::string get_next_season_dir();

		void set_season_dir(std::string dir);
		void set_next_ep_path();

		void add_to_tracker_file();
		void add_to_history_file();

	private:
		Settings settings;
		int line_number;

		std::string find_next_season_dir();
		std::string find_first_ep_in_next_season_dir();
		std::string find_next_ep_in_this_season_dir(const std::string& next_ep_number);
		void set_series_name_season(std::string path);

		std::vector<std::string> EXTENSIONS_TO_IGNORE;
		std::string TV_HISTORY_FILE;

		std::string next_ep_path;
		std::string next_ep_name;
		std::string last_season_dir;
		std::string season_number;
		std::string series_name;
		std::string last_played_ep;
		std::string next_season_dir;
};
