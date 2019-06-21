#pragma once

#include <string>
#include <vector>

struct Settings
{
	std::string tv_history_file;
	size_t HISTORY_SIZE = 5;
	std::string VIDEO_PLAYER = "mpv";
	std::vector<std::string> extensions_to_ignore {"sub", "srt", "ass"};
};
