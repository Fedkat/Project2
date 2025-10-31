#include <stdio.h>
#include <stdlib.h>
#include "game_of_lines.h"


//spilleren vælger en kolonne, hvis det ikke er et gyldigt træk så må de ikke
int scan_move(cell_values** arena, int size_of_arena, int player)
{
    int move;
    while (1)
    {
        printf("player %d choose a column from 1 to %d (and not a full one)\n>", player + 1, size_of_arena);
        scanf("%d", &move);

        if (move < 1 || size_of_arena < move || arena[move - 1][0] != empty)
        {
            printf("invalid\n");
            continue;
        }
        return move;
    }
}

//meget sofistikeret ai med dyb machinelearning algoritme trænet på tusindvis af professionele fire på stribe spillere
int ai_move(cell_values** arena, int size_of_arena)
{
    int move;
    printf("player 2 choose a column from 1 to %d (and not a full one)\n>", size_of_arena);

    do
    {
        move = rand() % size_of_arena + 1;
    } while (arena[move - 1][0] != empty);
    printf("%d\n", move);
    return move;
}

//kolonnen som spilleren har valgt får en brik der hvor der er plads nederst, spilleren kan ikke vælge en kolonne som
//er fuld, derfor tjekkes dette ikke
void update_arena(cell_values* column, int size_of_arena, int* row, int player)
{
    for (int i = 0; i <= size_of_arena; i++)
    {
        if (column[i] == player1_piece || column[i] == player2_piece || i == size_of_arena)
        {
            *row = i - 1;
            column[*row] = player;

            break;
        }
    }
}

//printer hele arenaen, arrayets rækker bliver printet som kolonner fordi det giver mere mening i mit hoved
//når fire på stribe kan ses som en række vertikale lister som har brikker i dem
void print_arena(cell_values** arena, int size_of_arena)
{
    for (int i = 0; i < size_of_arena; i++)
    {
        for (int j = 0; j < size_of_arena; j++)
        {
            switch (arena[j][i])
            {
            case empty:
                printf("_");
                break;
            case player1_piece:
                printf("1");
                break;
            case player2_piece:
                printf("2");
                break;
            }
        }
        printf("\n");
    }
}

//tjekker om spillet er uafgjort
int check_draw(cell_values** arena, int size_of_arena)
{
    for (int i = 0; i < size_of_arena; i++)
    {
        if (arena[i][0] != empty && i >= size_of_arena - 1)
        {
            return 1;
        }
    }
    return 0;
}

//tjekker om den seneste spiller vandt
int winner(cell_values** arena, int size_of_arena, int prev_column, int prev_row, int size_of_win_line, int player)
{
    //tjekker om mængden af brikker der forekommer i streg
    //er lig med eller højere end mængden påkrævet for at vinde
    //der tjekkes kun om den sidst placerede brik var et vindende træk,
    //da brikker ikke bare bliver fremtryllet
    if (check_column(arena[prev_column], size_of_arena, size_of_win_line, player) ||
        check_row(arena, size_of_arena, prev_row, size_of_win_line, player) ||
        check_diagonals(arena, size_of_arena, prev_column, prev_row, size_of_win_line, player))
    {
        return player;
    }

    return -1;
}

//tjekker igennem hele kolonnen hvor den sidst placerede brik blev sat i for at se om det var et vindende træk
int check_column(cell_values* prev_column, int size_of_arena, int size_of_win_line, int player)
{
    int counter = 0;
    for (int i = 0; i < size_of_arena; i++)
    {
        if (prev_column[i] == player)
        {
            counter++;
            if (counter >= size_of_win_line)
            {
                return 1;
            }
        }
        else
        {
            counter = 0;
        }
    }
    return 0;
}

//tjekker igennem hele rækken hvor den sidst placerede brik blev sat i for at se om det var et vindende træk
int check_row(cell_values** arena, int size_of_arena, int prev_row, int size_of_win_line, int player)
{
    int counter = 0;
    for (int i = 0; i < size_of_arena; i++)
    {
        if (arena[i][prev_row] == player)
        {
            counter++;
            if (counter >= size_of_win_line)
            {
                return 1;
            }
        }
        else
        {
            counter = 0;
        }
    }
    return 0;
}

//tjekker i et kryds som går henover den sidst placerede brik for at se om det var et vindende træk
int check_diagonals(cell_values** arena, int size_of_arena, int prev_column, int prev_row, int size_of_win_line, int player)
{
    int temp_column = prev_column;
    int temp_row = prev_row;

    //går diagonalt opad mod venstre fra den sidst placerede brik indtil en væg bliver ramt
    for (; temp_column > 0 && temp_row > 0; temp_column--, temp_row--);

    //tæller hvor mange gange en spillers brik fremkommer i streg når der bevæges digonalt nedad mod højre
    int counter = 0;
    for (int i = 0; temp_column + i < size_of_arena && temp_row + i < size_of_arena; i++)
    {
        if (arena[temp_column + i][temp_row + i] == player)
        {
            counter++;
            if (counter >= size_of_win_line)
            {
                return 1;
            }
        }
        else
        {
            counter = 0;
        }
    }

    temp_column = prev_column;
    temp_row = prev_row;

    //går diagonalt opad mod højre fra den sidst placerede brik indtil en væg bliver ramt
    for (; temp_column < size_of_arena - 1 && temp_row > 0; temp_column++, temp_row--);

    //tæller hvor mange gange en spillers brik fremkommer i streg når der bevæges digonalt nedad mod venstre
    counter = 0;
    for (int i = 0; temp_column - i >= 0 && temp_row + i < size_of_arena; i++)
    {
        if (arena[temp_column - i][temp_row + i] == player)
        {
            counter++;
            if (counter >= size_of_win_line)
            {
                return 1;
            }
        }
        else
        {
            counter = 0;
        }
    }

    return 0;
}
