#include <cstdio>
#include "chess/board.hh"
#include "chess/player.hh"
#include "chess/colour.hh"

int main()
{
    Board chess_board;

    chess_board = Board();
    chess_board.print();

    puts("Welcome to terminal chess!");
    puts("Moves can be entered by inputting a source piece and then its destination in the form: '<row><column> <row><column>'");

    // TODO: Set up player profile(s)
    Player *white_player = new Player(Colour(COLOUR_WHITE));
    Player *black_player = new Player(Colour(COLOUR_BLACK));
    Player *current_player;

    int turn_count = 0;
    int status_code;
    char player_move[4];

    // Main game loop
    while (1) {
        // White player always starts first
        current_player = (turn_count % 2 == 0) ? white_player : black_player;

        printf("It is %s's turn. Enter your move '(a-h)(1-8) (a-h)(1-8)':\n", current_player->getColour().getColourName());
        // TODO: Maybe input this as a string and then check it.
        // TODO: If it is `help`, `show`, or `exit` we should do those actions.
        // TODO: Otherwise, we should try and parse it as a move.
        // TODO: Maybe the user should have to type `move <src> <dst>`.
        // TODO: That way we could do `help <src> <dst>`, `show <src>`, etc..
        if (scanf("\n%c%c %c%c", &player_move[0], &player_move[1], &player_move[2], &player_move[3]) != 4) {
            std::cout << "Unable to parse move" << std::endl;
            continue;
        }

        // TODO: Allow the player to enter show move for a piece and highlight where it can move
        chess_board.movePiece(current_player, player_move, &status_code);

        // Check for errors and prompt the user to retry if they enter an invalid move
        switch (status_code) {
            case SUCCESS:
                printf("\n%s has decided to move the piece at %c%c to %c%c\n", current_player->getName(), player_move[0], player_move[1], player_move[2], player_move[3]);
                black_player->print();
                white_player->print();
                chess_board.print();
                break;
            case INVALID_SOURCE_ERROR:
                std::cout << "Source square outside of valid range" << std::endl;
                continue;
            case INVALID_DESTINATION_ERROR:
                std::cout << "Target square outside of valid range" << std::endl;
                continue;
            case INVALID_COLOUR_ERROR:
                std::cout << "Opponent's piece selected" << std::endl;
                continue;
            case INVALID_MOVE_ERROR:
                std::cout << "This piece is unable to execute that move" << std::endl;
                continue;
            case INVALID_SOURCE_PIECE_ERROR:
                std::cout << "No valid piece on source square" << std::endl;
                continue;
            case OCCUPIED_DESTINATION_ERROR:
                std::cout << "Target square already occupied" << std::endl;
                continue;
            case BLOCKED_PATH_ERROR:
                std::cout << "Path to destination is blocked" << std::endl;
                continue;
            default:
                std::cout << "Unknown execption" << std::endl;
                continue;
        }
        turn_count++;
    }

    return 0;
}
