//enum til celle værdierne, empty kommer til sidst fordi når player1_piece = 0 og player2_piece = 1 kan man
//bare skifte frem og tilbage med !whose_turn
typedef enum {player1_piece, player2_piece, empty} cell_values;

int scan_move(cell_values** arena, int size_of_arena, int player);

int ai_move(cell_values** arena, int size_of_arena);

void update_arena(cell_values* column, int size_of_arena, int* row, int player);

void print_arena(cell_values** arena, int size_of_arena);

int check_draw(cell_values** arena, int size_of_arena);

int winner(cell_values** arena, int size_of_arena, int prev_column, int prev_row, int size_of_win_line, int player);

int check_column(cell_values* prev_column, int size_of_arena, int size_of_win_line, int player);

int check_row(cell_values** arena, int size_of_arena, int prev_row, int size_of_win_line, int player);

int check_diagonals(cell_values** arena, int size_of_arena, int prev_column, int prev_row, int size_of_win_line, int player);
