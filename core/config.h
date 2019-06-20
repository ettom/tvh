#pragma once

#include <string>
#include <vector>

struct Settings
{
	int LIST_LENGTH = 0;
	std::string TV_HISTORY_FILE = "/home/atlas/.local/share/tvhistory";
	size_t HISTORY_SIZE = 5;
	std::string VIDEO_PLAYER = "mpv";
	std::vector<std::string> extensions_to_ignore {"sub", "srt", "ass"};
};
