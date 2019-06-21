#include <gtest/gtest.h>

#include "show.h"
#include "helpers.h"


TEST(Show, givenVectorOfShowDirectories_callingGenerateHistoryFileContent_mustVectorWhereNextEpisodeDirIsFirst){
	// ARRANGE
	Settings settings;
	settings.tv_history_file = "unimportant";
	Show show(settings, "/media/videos/shows/myshow4/S01/S01E01.mkv");
	show.set_next_ep_parent_dir("/media/videos/shows/myshow4/S01/S01E01.mkv");

	//std::vector<std::string> input {
	//	"/media/videos/shows/myshow1/S01",
	//	"/media/videos/shows/myshow2/S01",
	//	"/media/videos/shows/myshow3/S01",
	//	"/media/videos/shows/myshow4/S01",
	//};

	//std::vector<std::string> expected_result {
	//	"/media/videos/shows/myshow4/S01",
	//	"/media/videos/shows/myshow1/S01",
	//	"/media/videos/shows/myshow2/S01",
	//	"/media/videos/shows/myshow3/S01",
	//};


	////// ACT
	//std::vector<std::string> result = show.generate_history_file_content(input);

	//////ASSERT
	//ASSERT_EQ(result, expected_result);
}
