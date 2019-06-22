#include "extcmd.h"
#include <gtest/gtest.h>

TEST(Extcmd, givenFaultySystemCommand_callingRunExtCmd_mustNotReturn0){
	// ARRANGE
	std::string command = "some_invalid_command";

	// ACT
	int result = run_ext_cmd(command);

	// ASSERT
	ASSERT_NE(result, 0);
}

TEST(Extcmd, givenCorrectSystemCommand_callingRunExtCmd_mustReturn0){
	// ARRANGE
	std::string command = "date";

	// ACT
	int result = run_ext_cmd(command);

	// ASSERT
	ASSERT_EQ(result, 0);
}
