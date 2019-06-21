#include "helpers.h"
#include <gtest/gtest.h>


TEST(Helpers, givenFileName_callingRemoveExtension_mustReturnFileNameWithOutExtension){
	// ARRANGE
	std::string filename = "file.txt";

	// ACT
	std::string result = remove_extension(filename);

	//ASSERT
	ASSERT_EQ(result, "file");
}


TEST(Helpers, givenFilePath_callingReverseFilePath_mustReturnReversedFilePath){
	// ARRANGE
	std::string file_path = "/home/mypath/file.txt";

	// ACT
	std::vector<std::string> result = reverse_file_path(file_path);

	//ASSERT
	std::vector<std::string> expected_result = {"file.txt", "mypath", "home"};
	ASSERT_EQ(result, expected_result);
}

TEST(Helpers, givenFaultySystemCommand_callingRunExtCmd_mustNotReturn0){
	// ARRANGE
	std::string command = "some_invalid_command";

	// ACT
	int result = run_ext_cmd(command);

	//ASSERT
	ASSERT_NE(result, 0);
}

TEST(Helpers, givenCorrectSystemCommand_callingRunExtCmd_mustReturn0){
	// ARRANGE
	std::string command = "date";

	// ACT
	int result = run_ext_cmd(command);

	//ASSERT
	ASSERT_EQ(result, 0);
}

TEST(Helpers, givenDigit_callingCalculateNext_mustReturnDigitPlusOneWithALeadingZeroUnlessDigitWas9){
	// ARRANGE
	int number1 = 0;
	int number2 = 1;
	int number3 = 9;

	// ACT
	std::string result1 = calculate_next(number1);
	std::string result2 = calculate_next(number2);
	std::string result3 = calculate_next(number3);

	//ASSERT
	ASSERT_EQ(result1, "01");
	ASSERT_EQ(result2, "02");
	ASSERT_EQ(result3, "10");
}

TEST(Helpers, givenFilenameAndAListOfExtensions_callingEndingIn_mustReturnTrueIfFilenameEndsInOneOfTheGivenExtensions){
	// ARRANGE
	std::string filename = "file.txt";
	std::vector<std::string> extensions {"cpp", "sh", "txt"};

	// ACT
	bool extension_of_filename_in_extensions = ending_in(filename, extensions);

	//ASSERT
	ASSERT_TRUE(extension_of_filename_in_extensions);
}

TEST(Helpers, givenAStringAndRegex_callingExtractSubstring_mustReturnMatchingSubstring){
	// ARRANGE
	std::string input = "some_test_string";
	std::regex rgx = std::regex("_(.*)_");

	// ACT
	std::string result = extract_substring(input, rgx);

	//ASSERT
	ASSERT_EQ(result, "test");
}
