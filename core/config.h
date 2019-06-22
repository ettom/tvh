#pragma once

#include <string>
#include <vector>
#include <regex>

struct Settings
{
	std::string tv_history_file;
	size_t HISTORY_SIZE = 5;
	std::string VIDEO_PLAYER = "mpv";
	std::string FILE_MANAGER = "ranger_launch";
	std::vector<std::string> extensions_to_ignore {"sub", "srt", "ass"};
	std::regex ep_regex = std::regex("E([0-9]+)");
	std::regex season_regex = std::regex("S([0-9]+)");
};
