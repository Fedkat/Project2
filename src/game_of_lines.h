//enum til celle værdierne, empty kommer til sidst fordi når player1_piece = 0 og player2_piece = 1 kan man
//bare skifte frem og tilbage med !whose_turn
typedef enum {player1_piece, player2_piece, empty} cell_values;

/**
 * spilleren vælger en kolonne, hvis det ikke er et gyldigt træk så må de ikke
 * @param arena er et todimensionelt array til brættet
 * @param size_of_arena er sidelængderne til arena
 * @param player er hvilken spiller der er aktiv
 * @return den kolonne som den nuværende spiller gerne vil lægge sin brik i
 */
int scan_move(cell_values** arena, int size_of_arena, int player);

/**
 * meget sofistikeret ai med dyb machinelearning algoritme trænet på tusindvis af professionele fire på stribe spillere
 * @param arena er et todimensionelt array til brættet
 * @param size_of_arena er sidelængderne til arena
 * @return den "bedst mulige kolonne at spille i"
 */
int ai_move(cell_values** arena, int size_of_arena);

/**
 * kolonnen som spilleren har valgt får en brik der hvor der er plads nederst, spilleren kan ikke vælge en kolonne som
 * er fuld, derfor tjekkes dette ikke
 * @param column den kolonne som der bliver lagt en brik i
 * @param size_of_arena er længden på kolonnen
 * @param row er en pointer til den række som der bliver lagt en brik så programmet kan holde styr på de præcise koordinater til når der tjekkes for en vinder
 * @param player er hvilken spiller der er aktiv
 */
void update_arena(cell_values* column, int size_of_arena, int* row, int player);

/**
 * printer hele arenaen, arrayets rækker bliver printet som kolonner fordi det giver mere mening i mit hoved
 * når fire på stribe kan ses som en række vertikale lister som har brikker i dem
 * @param arena er et todimensionelt array til brættet
 * @param size_of_arena er sidelængderne til arena
 */
void print_arena(cell_values** arena, int size_of_arena);

/**
 * tjekker om spillet er uafgjort
 * @param arena er et todimensionelt array til brættet
 * @param size_of_arena er sidelængderne til arena
 * @return returnerer 1 hvis spillet er uafgjort, ellers returneres 0
 */
int check_draw(cell_values** arena, int size_of_arena);

/**
 * tjekker om den seneste spiller vandt
 * @param arena er et todimensionelt array til brættet
 * @param size_of_arena er sidelængderne til arena
 * @param prev_column er indeks til den kolonne som skal tjekkes
 * @param prev_row er indeks til den række som skal tjekkes
 * @param size_of_win_line er længden på en vindende linje
 * @param player er den spiller som der tjekkes har vundet
 * @return returnerer hvem der vandt
 */
int winner(cell_values** arena, int size_of_arena, int prev_column, int prev_row, int size_of_win_line, int player);

/**
 * tjekker om en spiller har vundet på en kolonne
 * @param column er den kolonne som skal tjekkes
 * @param size_of_arena er sidelængderne til arena
 * @param size_of_win_line er længden på en vindende linje
 * @param player er den spiller som der tjekkes har vundet
 * @return om den aktive spiller vandt på en kolonne
 */
int check_column(cell_values* column, int size_of_arena, int size_of_win_line, int player);

/**
 * tjekker igennem hele kolonnen hvor den sidst placerede brik blev sat i for at se om det var et vindende træk
 * @param arena er et todimensionelt array til brættet
 * @param size_of_arena er sidelængderne til arena
 * @param row er indeks til den række som skal tjekkes
 * @param size_of_win_line er længden på en vindende linje
 * @param player er den spiller som der tjekkes har vundet
 * @return om den aktive spiller vandt på en række
 */
int check_row(cell_values** arena, int size_of_arena, int row, int size_of_win_line, int player);

/**
 * tjekker i et kryds som går henover den sidst placerede brik for at se om det var et vindende træk
 * @param arena er et todimensionelt array til brættet
 * @param size_of_arena er sidelængderne til arena
 * @param column er indeks til den kolonne som skal tjekkes
 * @param row er indeks til den række som skal tjekkes
 * @param size_of_win_line er længden på en vindende linje
 * @param player er den spiller som der tjekkes har vundet
 * @return om den aktive spiller vandt på en diagonal linje
 */
int check_diagonals(cell_values** arena, int size_of_arena, int column, int row, int size_of_win_line, int player);
