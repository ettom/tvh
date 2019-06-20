#pragma once

#include <string>
#include <vector>

struct settings
{
	std::string TV_HISTORY_FILE;
	size_t HISTORY_SIZE = 5;
	std::string VIDEO_PLAYER = "mpv";
	std::vector<std::string> extensions_to_ignore {"sub", "srt", "ass"};
};
