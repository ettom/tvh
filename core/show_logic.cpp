#include "show_logic.h"

// std::vector<std::string> generate_history_contents(Settings settings, const std::string& next_ep_parent_dir, std::vector<std::string> history_contents, const std::string& series_name)
// {
// 	std::regex rgx = std::regex(".*" + series_name + ".*");
// 	std::string to_delete = "";

// 	// Delete the line that contains the name of the current show
// 	for (auto line : history_contents) {
// 		if (std::regex_match(line, rgx))
// 			to_delete = line;
// 	}
// 	history_contents.erase(std::remove(history_contents.begin(), history_contents.end(), to_delete), history_contents.end());

// 	// Put the parent dir of the next episode to the first line
// 	history_contents.insert(history_contents.begin(), next_ep_parent_dir);

// 	// Keep the number of lines at specified length
// 	if (history_contents.size() > settings.HISTORY_SIZE)
// 		history_contents.resize(settings.HISTORY_SIZE);
// 	return history_contents;
// }


// split to three
// one function for deleting line that contains the name of the current show
// one function for resizing to HISTORY_SIZE
// one function for inserting to first position
