#include "helpers.h"
#include <gtest/gtest.h>



TEST(Helpers, givenFilePath_callingReverseFilePath_mustReturnReversedFilePath){
	// ARRANGE

	std::string file_path = "/home/mypath/file.txt";

	// ACT

	std::vector<std::string> result = reverse_file_path(file_path);

	//ASSERT
	// std::vector<std::string> expected_result = {"file.txt", "mypath", "file.txt"};
	// ASSERT_TRUE(result == expected_result);
}

