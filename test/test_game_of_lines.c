#include "mtest.h"
#include "game_of_lines.h"

// TODO: Write unit tests!
TEST_CASE(update_arena_test,
    cell_values column[] = {empty, empty, player2_piece};
    int row;

    update_arena(column, 3, &row, player1_piece);

    CHECK_EQ_INT(column[1], player1_piece);
)

TEST_CASE(check_column_win_test,
    cell_values** arena = malloc(sizeof(int) * 4 * 4);
    for(int i = 0; i < 4; i++)
    {
        arena[i] = (cell_values*)malloc(sizeof(int) * 4);
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            arena[j][i] = empty;
        }
    }
    int row;


    for (int i = 0; i < 4; i++)
    {
        update_arena(arena[3], 4, &row, player1_piece);
    }



    int win = winner(arena, 4, 3, row, 4, player1_piece);


    CHECK_EQ_INT(win, 1);
)

TEST_CASE(check_diagonal_win_test,
    cell_values** arena = malloc(sizeof(int) * 4 * 4);
    for(int i = 0; i < 4; i++)
    {
        arena[i] = (cell_values*)malloc(sizeof(int) * 4);
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            arena[j][i] = empty;
        }
    }
    int row;

    update_arena(arena[0], 4, &row, player1_piece);
    for (int i = 0; i < 2; i++)
    {
        update_arena(arena[1], 4, &row, player1_piece);
    }
    for (int i = 0; i < 3; i++)
    {
        update_arena(arena[2], 4, &row, player1_piece);
    }
    for (int i = 0; i < 4; i++)
    {
        update_arena(arena[3], 4, &row, player1_piece);
    }



    int win = winner(arena, 4, 3, row, 4, player1_piece);

    CHECK_EQ_INT(win, 1);
)


MAIN_RUN_TESTS(update_arena_test, check_diagonal_win_test, check_column_win_test)
