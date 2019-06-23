#pragma once

#include <string>
#include <vector>
#include <regex>

struct Settings
{
	size_t HISTORY_SIZE = 5;
	std::string TV_HISTORY_FILE = "/.local/share/tvhistory"; // relative to $HOME
	std::string VIDEO_PLAYER = "mpv";
	std::string FILE_MANAGER = "ranger_launch";
	std::vector<std::string> EXTENSIONS_TO_IGNORE {"sub", "srt", "ass"};

	// Don't change these
	std::regex EP_REGEX = std::regex("E([0-9]+)");
	std::regex SEASON_REGEX = std::regex("S([0-9]+)");
};
