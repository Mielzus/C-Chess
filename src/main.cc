#include <cstdio>
#include "chess/board.hh"
#include "chess/player.hh"
#include "chess/colour.hh"

#define MAX_COMMAND_L 20

int main()
{
    Board chess_board;

    chess_board = Board();
    chess_board.print();

    puts("Welcome to terminal chess!");
    puts("Moves can be entered by inputting a source piece and then its destination in the form: '<row><column> <row><column>'.");
    puts("Type 'help' for more options");

    // TODO: Set up player profile(s)
    Player *white_player = new Player(Colour(COLOUR_WHITE));
    Player *black_player = new Player(Colour(COLOUR_BLACK));
    // White player always starts first
    Player *current_player = white_player;

    int turn_count = 0;
    int status_code;
    char player_move[4];
    char command[MAX_COMMAND_L];

    // Main game loop
    while (1) {
        printf("It is %s's turn. Enter your move '(a-h)(1-8) (a-h)(1-8)':\n", current_player->getColour().getColourName());
        // TODO: Maybe input this as a string and then check it.
        // TODO: If it is `help`, `show`, or `exit` we should do those actions.
        // TODO: Otherwise, we should try and parse it as a move.
        // TODO: Maybe the user should have to type `move <src> <dst>`.
        // TODO: That way we could do `help <src> <dst>`, `show <src>`, etc..
        fgets(command, MAX_COMMAND_L, stdin);
        if (strncmp(command, "exit", 4) == 0 || strncmp(command, "quit", 4) == 0) {
            std::cout << "Thanks for playing!" << std::endl;
            return EXIT_SUCCESS;
        } else if (strncmp(command, "help", 4) == 0) {
            std::cout << std::endl << "Available command options" << std::endl;
            std::cout << "----------------------------------" << std::endl;
            std::cout << "help - List available commands" << std::endl;
            std::cout << "exit, quit - Exit the game" << std::endl;
            std::cout << "(a-h)(1-8) (a-h)(1-8) - Enter the source and destination square for your move" << std::endl << std::endl;
            continue;
        } else {
            if (sscanf(command, "\n%c%c %c%c", &player_move[0], &player_move[1], &player_move[2], &player_move[3]) != 4) {
                std::cout << "Unable to parse move" << std::endl;
                continue;
            }
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
            case KING_ENTER_CHECK_ERROR:
                std::cout << "King is in check on target square" << std::endl;
                continue;
            default:
                std::cout << "Unknown execption" << std::endl;
                continue;
        }
        turn_count++;

        // Switch to the other player
        current_player = (turn_count % 2 == 0) ? white_player : black_player;
        // Check if the player is in check
        chess_board.checkCheckMate(current_player, &status_code);

        switch(status_code) {
            case PLAYER_IN_CHECK:
                std::cout << current_player->getName() << " is currently in check." << std::endl;
                break;
            case PLAYER_IN_CHECKMATE:
                std::cout << current_player->getName() << " is in checkmate." << std::endl;
                break;
        } 
    }

    return 0;
}
