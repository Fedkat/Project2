#include <stdio.h>
#include <stdlib.h>
#include "game_of_lines.h"
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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

int main() {
    int opponent_is_ai, size_of_arena, size_of_win_line;
    srand(time(NULL)); //kun brugt til ai

    scan_settings(&opponent_is_ai, &size_of_arena, &size_of_win_line);
    game_of_lines(opponent_is_ai, size_of_arena, size_of_win_line);

    return 0;
}

void game_of_lines(int opponent_is_ai, int size_of_arena, int size_of_win_line) {
    cell_values** arena[size_of_arena][size_of_arena] = {{ empty }};

    print_arena(arena, size_of_arena);

    int whose_turn = 0;
    int the_winner, column_to_play, row;
    
    do {
        //hvis man vil have ai og det er spiller 2 tur så laver ai et træk, ellers er det spiller 1 eller 2 (menneske)
        column_to_play = opponent_is_ai && whose_turn ? ai_move(arena, size_of_arena) : scan_move(arena, size_of_arena, whose_turn);

        column_to_play--;
        update_arena(arena[column_to_play], size_of_arena, &row, whose_turn);

        print_arena(arena, size_of_arena);

        //hvis der ikke kan placeres flere brikker, så er spillet uafgjort
        if (check_draw(arena, size_of_arena)) {
            printf("game ends in draw");
            exit(EXIT_SUCCESS);
        }
        the_winner = winner(arena, size_of_arena, column_to_play, row, size_of_win_line, whose_turn);
        //der skiftes hvilken spiller der er aktiv
        whose_turn = !whose_turn; 
    } while (the_winner == -1);
    printf("player %d won", the_winner + 1);
}

//giver mulighed for input til indstillinger, med input validering
void scan_settings(int* opponent_is_ai, int* size_of_arena, int* size_of_win_line) {
    char opponent_is_ai_char = '';
    while (opponent_is_ai_char != 'y' || opponent_is_ai_char != 'n') {
        printf("Play against a computer (y/n)\n>");
        scanf(" %c", &opponent_is_ai_char);
    }
    opponent_is_ai_char = tolower(opponent_is_ai_char);
    //opponent_is_ai bliver 1 hvis opponent_is_ai_char har værdien 'y',
    //ellers bliver den til 0, da der er blevet tjekket om opponent_is_ai_char
    //endten er y eller n, så kan opponent_is_ai kun blive 0 hvis opponent_is_ai_char er 'n'
    *opponent_is_ai = opponent_is_ai_char == 'y';

    char size_of_arena_str[100] = { NULL };
    //programmet fejler hvis der inputtes en meget lang string og så et korrekt nummer, men kan ikke fikse
    //inputtet bliver også godkendt hvis det er for langt til at opbevare i strengen, men resultatet ændres grundet noget med memory ig
    while (!string_is_number(size_of_arena_str)) {
        printf("Size of arena\n>");
        scanf(" %s", size_of_arena_str);
        
        *size_of_arena = string_to_int(size_of_arena_str);
    }
    
    //programmet fejler hvis der inputtes en meget lang string og så et korrekt nummer, men kan ikke fikse
    while (1) {
        char size_of_win_line_str[100];

        printf("Length of winning lines\n>");
        scanf(" %s", size_of_win_line_str);
        *size_of_win_line = string_to_int(size_of_win_line_str);

        //validation
        //tillader ikke vindende linjer længere end der er plads til
        if (!string_is_number(size_of_win_line_str)) {
            printf("invalid\n");
            continue;
        }
        if (*size_of_win_line > *size_of_arena) {
            printf("invalid\n");
            continue;
        }
        if (size_of_win_line <= 1) {
            printf("invalid\n");
            continue;
        }
        
        /* alternativt kunne du osgå gøre det her
        if (*size_of_win_line <= 1)
            || *size_of_win_line > *size_of_arena 
            || *size_of_win_line <= 1){
            printf("invalid\n");
            continue;
        }*/

        *size_of_win_line = string_to_int(size_of_win_line_str);

        break;
    }
}

int string_is_number(char* str) {
    const int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (!isdigit(str[i])) { return 0; }
    }
    
    return 1; //returns 1 if all elements align with condition, otherwise returns 0
}

//ved godt der findes en funktion til dette, men ville bare prøve krafter af med det
int string_to_int(char* str)
{
    const int length = strlen(str);
    int num = 0;
    //starter ved den sidste ciffer og går mod venstre.
    for (int i = 0; i < length; i++)
    {
        //der subtraheres med '0' da tal-karakterenes ('0' → '9')
        //int værdier strækker sig mellem 48 til 57, så for at
        //konvertere et enkelt tegn til tal trækkes den laveste tal karakter ('0') fra
        const int current_index = (length - 1) - i;
        num += (str[current_index] - '0') * pow(10.0, i);
    }
    return num;
}
