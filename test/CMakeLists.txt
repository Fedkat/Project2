
# We create a test driver executable
add_executable(test_game_of_lines test_game_of_lines.c)
# We link the library to the test driver
target_link_libraries(test_game_of_lines game_of_lines mtest)
# We add the test cases to CTest
discover_tests(test_game_of_lines)
