#include "helpers.h"
#include <gtest/gtest.h>


TEST(Helpers, givenFileName_callingRemoveExtension_mustReturnFileNameWithOutExtension){
	// ARRANGE
	std::string filename = "file.txt";

	// ACT
	std::string result = remove_extension(filename);

	// ASSERT
	ASSERT_EQ(result, "file");
}


TEST(Helpers, givenFilePath_callingReverseFilePath_mustReturnReversedFilePath){
	// ARRANGE
	std::string file_path = "/home/mypath/file.txt";

	// ACT
	std::vector<std::string> result = reverse_file_path(file_path);

	// ASSERT
	std::vector<std::string> expected_result = {"file.txt", "mypath", "home"};
	ASSERT_EQ(result, expected_result);
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

	// ASSERT
	ASSERT_EQ(result1, "01");
	ASSERT_EQ(result2, "02");
	ASSERT_EQ(result3, "10");
}

TEST(Helpers, givenAStringAndRegex_callingExtractSubstring_mustReturnMatchingSubstring){
	// ARRANGE
	std::string input = "some_test_string";
	std::regex rgx = std::regex("_(.*)_");

	// ACT
	std::string result = extract_substring(input, rgx);

	// ASSERT
	ASSERT_EQ(result, "test");
}

TEST(Helpers, givenFilenameAndAVectorOfExtensions_callingEndsIn_mustReturnTrueIfFilenameEndsInOneOfTheGivenExtensions){
	// ARRANGE
	std::string filename = "file.txt";
	std::vector<std::string> extensions {"cpp", "sh", "txt"};

	// ACT
	bool extension_of_filename_in_extensions = ends_in(filename, extensions);

	// ASSERT
	ASSERT_TRUE(extension_of_filename_in_extensions);
}


TEST(Helpers, givenReversedPathAsVector_callingExtractSeriesNameSeason_mustReturnTupleOfSeriesNameAndSeasonNumber){
	// ARRANGE
	std::vector<std::string> input {"S01", "myshow", "shows"};
	Settings settings;

	// ACT
	std::tuple<std::string, std::string> result = extract_series_name_season(input, settings.SEASON_REGEX);

	// ASSERT
	ASSERT_EQ(std::get<0>(result), "myshow");
	ASSERT_EQ(std::get<1>(result), "S01");
}


TEST(Helpers, givenVectorAndString_callingFindMatchesInVector_mustReturnAllMatchingElements){
	// ARRANGE
	std::vector<std::string> input_vector {"abc", "aabc", "def", "ghi"};
	std::string to_search = "a";
	std::vector<std::string> expected_result {"abc", "aabc"};

	// ACT
	std::vector<std::string> result = find_matches_in_vector(input_vector, to_search);

	// ASSERT
	ASSERT_EQ(result, expected_result);
}

TEST(Helpers, givenVectorOfFilenamesAndVectorOfExtensionsToIgnore_callingFilterFilenamesByExtension_mustReturnVectorOfFilenamesWithMatchingElementsRemoved){
	// ARRANGE
	std::vector<std::string> filenames {"myfile.txt", "myfile.sh", "myfile.cpp", "myfile.h"};
	std::vector<std::string> extensions_to_ignore {"txt", "sh"};
	std::vector<std::string> expected_result {"myfile.cpp", "myfile.h"};

	// ACT
	std::vector<std::string> result = filter_filenames_by_extension(filenames, extensions_to_ignore);

	// ASSERT
	ASSERT_EQ(result, expected_result);
}

TEST(Helpers, givenVectorAndTargetSize_callingResizeVectorToSize_mustReturnVectorWithMaxSizeOfTarget){
	// ARRANGE
	int target_size = 3;
	std::vector<std::string> input_vector {"a", "b", "c", "d"};
	std::vector<std::string> expected_result {"a", "b", "c"};

	// ACT
	std::vector<std::string> result = resize_vector_to_size(input_vector, target_size);

	// ASSERT
	ASSERT_EQ(result, expected_result);
}

TEST(Helpers, givenVectorAndRegex_callingDeleteMatchFromRegex_mustReturnVectorWithMatchingElementsRemoved){
	// ARRANGE
	std::string match1 = "a";
	std::vector<std::string> input1 {"a", "b", "c", "d"};
	std::vector<std::string> expected1 {"b", "c", "d"};

	std::string match2 = "myshow1";
	std::vector<std::string> input2 = { "myshow1 w'ith (parentheses)", "myshow2" };
	std::vector<std::string> expected2 { "myshow2" };

	std::vector<std::string> result1 = delete_match_from_vector(input1, match1);
	std::vector<std::string> result2 = delete_match_from_vector(input2, match2);

	// ASSERT
	ASSERT_EQ(result1, expected1);
	ASSERT_EQ(result2, expected2);
}

TEST(Helpers, givenVectorAndElement_callingInsertElementToFirstPos_mustReturnVectorWithElementOnFirstPositon){
	// ARRANGE
	std::string element = "8";
	std::vector<std::string> input_vector {"1", "2", "3", "4"};
	std::vector<std::string> expected_result {"8", "1", "2", "3", "4"};

	// ACT
	std::vector<std::string> result = insert_element_to_first_pos(input_vector, element);

	// ASSERT
	ASSERT_EQ(result, expected_result);
}

TEST(Helpers, givenEmptyVector_callingGetFirstElementOtherwiseEmpty_mustReturnEmptyString){
	// ARRANGE
	std::vector<std::string> input_vector {};

	// ACT
	std::string result = get_first_element_otherwise_empty(input_vector);

	// ASSERT
	ASSERT_EQ(result, "");
}

TEST(Helpers, givenVectorWithMultipleElements_callingGetFirstElementOtherwiseEmpty_mustReturnFirstElement){
	// ARRANGE
	std::vector<std::string> input_vector {"1", "2", "3", "4"};

	// ACT
	std::string result = get_first_element_otherwise_empty(input_vector);

	// ASSERT
	ASSERT_EQ(result, "1");
}

TEST(Helpers, givenStringAndLineLength_callingWrapStringToLines_mustReturnLinesNoLongerThanGivenLength){
	// ARRANGE
	std::string input = "Lorem ipsum dolor sit";
	size_t max_line_length = 10;

	std::vector<std::string> expected {
		"Lorem",
		"ipsum",
		"dolor sit",
	};


	// ACT
	std::vector<std::string> result = wrap_string_to_lines(input, max_line_length);

	// ASSERT
	ASSERT_EQ(result.at(0), expected.at(0));
	ASSERT_EQ(result.at(1), expected.at(1));
	ASSERT_EQ(result.at(2), expected.at(2));
}
