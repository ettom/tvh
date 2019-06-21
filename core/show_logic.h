#pragma once

#include <regex>
#include <vector>
#include <string>

#include "config.h"

std::vector<std::string> generate_history_contents(Settings settings, const std::string& next_ep_parent_dir, std::vector<std::string> history_contents, const std::string& series_name);
