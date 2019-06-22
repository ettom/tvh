#include "extcmd.h"

int run_ext_cmd(const std::string& cmd)
{
	int status = system(cmd.c_str());
	return status;
}

void play_video(const std::string& video_player, const std::string& path_to_file)
{
	const std::string& cmd = "setsid " + video_player + " \"" + path_to_file + "\" > /dev/null 2>&1 &";
	run_ext_cmd(cmd);
}

void open_dir_in_file_manager(const std::string& file_manager, const std::string& dir_path)
{
	const std::string& cmd = "setsid " + file_manager + " \"" + dir_path + "\" > /dev/null 2>&1 &";
	run_ext_cmd(cmd);
}
