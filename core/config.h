#pragma once

#include <regex>
#include <string>
#include <vector>

struct Settings {
	size_t HISTORY_SIZE = 5;
	std::string TV_HISTORY_FILE = "/.local/share/tvhistory"; // relative to $HOME
	std::string VIDEO_PLAYER = "mpv";
	std::string FILE_MANAGER = "thunar";
	std::vector<std::string> EXTENSIONS_TO_IGNORE {"sub", "srt", "ass"};

	// Don't change these
	std::regex EP_REGEX = std::regex("E([0-9]+)");
	std::regex SEASON_REGEX = std::regex("S([0-9]+)");
};

struct Path {
	std::string last_season_dir;
	std::string last_played_ep;
	std::string next_ep_path;
	std::string next_season_dir;
};
