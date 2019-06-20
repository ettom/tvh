#pragma once

#include "show.h"

std::map<int, Show> create_shows()
{
	// Create show objects for every directory name in the history file
	std::map<int, Show> all_shows;

	std::vector<std::string> lines = readfile(settings.TV_HISTORY_FILE);
	for (std::string line : lines) {
		Show show(line, settings.LIST_LENGTH);  // Create show object
		all_shows[settings.LIST_LENGTH] = show; // Assign to map where key is the current line number and object is the value

		settings.LIST_LENGTH++;
	}

	return all_shows;
}
