#include "mtest.h"
#include "game_of_lines.h"

// TODO: Write unit tests!
TEST_CASE(test_name,
    cell_values column[] = {2, 2, 1};
    int row;

    update_arena(column, 3, &row, player1_piece);

    CHECK_EQ_INT(column[1], player1_piece);
)


MAIN_RUN_TESTS(test_name)
