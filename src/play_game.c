#include <stdio.h>
#include <stdlib.h>
#include "game_of_lines.h"
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>



void game_of_lines(int opponent_is_ai, int size_of_arena, int size_of_win_line);

/**
 * tager og validerer input fra brugeren
 * @param opponent_is_ai pointer til opponent_is_ai
 * @param size_of_arena pointer til size_of_arena
 * @param size_of_win_line pointer til size_of_win_line
 */
void scan_settings(int* opponent_is_ai, int* size_of_arena, int* size_of_win_line);

//tjekker om en streng er et tal
int string_is_number(char* str);

//omdanner en string til int
int string_to_int(char* str);


int main(void) {
    int opponent_is_ai, size_of_arena, size_of_win_line;
    srand(time(NULL));

    scan_settings(&opponent_is_ai, &size_of_arena, &size_of_win_line);

    // Run the game
    game_of_lines(opponent_is_ai, size_of_arena, size_of_win_line);

    return 0;
}

void game_of_lines(int opponent_is_ai, int size_of_arena, int size_of_win_line) {
    cell_values** arena = malloc(sizeof(int) * size_of_arena * size_of_arena);
    for(int i = 0; i < size_of_arena; i++)
    {
        arena[i] = (cell_values*)malloc(sizeof(int) * size_of_arena);
    }

    for (int i = 0; i < size_of_arena; i++)
    {
        for (int j = 0; j < size_of_arena; j++)
        {
            arena[j][i] = empty;
        }
    }

    print_arena(arena, size_of_arena);


    int whose_turn = 0;  // Who should perform the next move: Player 0 or Player/Computer 1?

    int the_winner;

    int column_to_play;
    int row;
    do {
        column_to_play = opponent_is_ai && whose_turn ? ai_move(arena, size_of_arena) : scan_move(arena, size_of_arena, whose_turn);

        column_to_play--;
        update_arena(arena[column_to_play], size_of_arena, &row, whose_turn);

        print_arena(arena, size_of_arena);

        if (check_draw(arena, size_of_arena))
        {
            printf("game ends in draw");
            exit(EXIT_SUCCESS);
        }
        the_winner = winner(arena, size_of_arena, column_to_play, row, size_of_win_line, whose_turn);
        whose_turn = !whose_turn;
    } while (the_winner == -1);
    free(arena);
    printf("player %d won", the_winner + 1);
}


void scan_settings(int* opponent_is_ai, int* size_of_arena, int* size_of_win_line)
{
    while (1)
    {
        char opponent_is_ai_char;

        fseek(stdin,0,SEEK_END);
        printf("Play against a computer (y/n)\n>");
        scanf(" %c", &opponent_is_ai_char);
        opponent_is_ai_char = tolower(opponent_is_ai_char);
        if (opponent_is_ai_char != 'y' && opponent_is_ai_char != 'n')
        {
            printf("invalid\n");
            continue;
        }

        //opponent_is_ai bliver 1 hvis opponent_is_ai_char har værdien 'y',
        //ellers bliver den til 0, da der er blevet tjekket om opponent_is_ai_char
        //endten er y eller n, så kan opponent_is_ai kun blive 0 hvis opponent_is_ai_char er 'n'
        *opponent_is_ai = opponent_is_ai_char == 'y';
        break;
    }

    //programmet fejler hvis der inputtes en meget lang string og så et korrekt nummer, men kan ikke fikse
    //inputtet bliver også godkendt hvis det er for langt til at opbevare i strengen, men resultatet ændres grundet noget med memory ig
    while (1)
    {
        char size_of_arena_str[100];

        fseek(stdin,0,SEEK_END);

        printf("Size of arena\n>");
        scanf(" %s", size_of_arena_str);

        if (!string_is_number(size_of_arena_str))
        {
            printf("invalid\n");
            continue;
        }

        *size_of_arena = string_to_int(size_of_arena_str);
        break;
    }

    while (1) //programmet fejler hvis der inputtes en meget lang string og så et korrekt nummer, men kan ikke fikse
    {
        char size_of_win_line_str[100];

        fseek(stdin,0,SEEK_END);

        printf("Length of winning lines\n>");
        scanf(" %s", size_of_win_line_str);
        *size_of_win_line = string_to_int(size_of_win_line_str);

        //tillader ikke vindende linjer længere end der er plads til
        if (!string_is_number(size_of_win_line_str) || *size_of_win_line > *size_of_arena || *size_of_win_line <= 1)
        {
            printf("invalid\n");
            continue;
        }

        *size_of_win_line = string_to_int(size_of_win_line_str);


        break;
    }
}


int string_is_number(char* str)
{
    int checks = 0;
    int length = strlen(str);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1; //returns 1 if all elements align with condition, otherwise returns 0
}

//ved godt der findes en funktion til dette, men ville bare prøve krafter af med det
int string_to_int(char* str)
{
    int length = strlen(str);
    int num = 0;
    //starter ved den sidste ciffer og går mod venstre.
    for (int i = 0; i < length; i++)
    {
        //der subtraheres med '0' da tal-karakterenes ('0' → '9')
        //int værdier strækker sig mellem 48 til 57, så for at
        //konvertere et enkelt tegn til tal trækkes den laveste tal karakter ('0') fra
        num += (str[(length - 1) - i] - '0') * pow(10.0, i);
    }
    return num;
}

