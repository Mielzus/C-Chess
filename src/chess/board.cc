#include "board.hh"

Board::Board()
{
    Colour white = Colour(COLOUR_WHITE);
    Colour black = Colour(COLOUR_BLACK);

    // Initialize board
    board = new Square**[BOARD_SIZE];
    for (int x = 0; x < BOARD_SIZE; x++) {
        board[x] = new Square*[BOARD_SIZE];
    }

    // Populate the board with squares
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (x % 2 == 0) {
                if (y % 2 == 0) {
                    board[x][y] = new Square(x, y, white);
                } else {
                    board[x][y] = new Square(x, y, black);
                }
            } else {
                if (y % 2 == 0) {
                    board[x][y] = new Square(x, y, black);
                } else {
                    board[x][y] = new Square(x, y, white);
                }
            }
        }
    }

    this->initializePieces();
}

void Board::initializePieces()
{
    Colour white = Colour(COLOUR_WHITE);
    Colour black = Colour(COLOUR_BLACK);

    // Set up Black pieces
    // Rooks
    (board[0][0])->setPiece(new Piece(black, 'R', vRook));
    (board[0][7])->setPiece(new Piece(black, 'R', vRook));
    // Knights
    (board[0][1])->setPiece(new Piece(black, 'N', vKnight));
    (board[0][6])->setPiece(new Piece(black, 'N', vKnight));
    // Bishops
    (board[0][5])->setPiece(new Piece(black, 'B', vBishop));
    (board[0][2])->setPiece(new Piece(black, 'B', vBishop));
    // Queen
    (board[0][3])->setPiece(new Piece(black, 'Q', vQueen));
    // King
    (board[0][4])->setPiece(new Piece(black, 'K', vKing));
    // Pawns
    (board[1][0])->setPiece(new Piece(black, 'P', vPawn));
    (board[1][1])->setPiece(new Piece(black, 'P', vPawn));
    (board[1][2])->setPiece(new Piece(black, 'P', vPawn));
    (board[1][3])->setPiece(new Piece(black, 'P', vPawn));
    (board[1][4])->setPiece(new Piece(black, 'P', vPawn));
    (board[1][5])->setPiece(new Piece(black, 'P', vPawn));
    (board[1][6])->setPiece(new Piece(black, 'P', vPawn));
    (board[1][7])->setPiece(new Piece(black, 'P', vPawn));

    // Set up White pieces
    // Rooks
    (board[7][0])->setPiece(new Piece(white, 'R', vPawn));
    (board[7][7])->setPiece(new Piece(white, 'R', vPawn));
    // Knights
    (board[7][1])->setPiece(new Piece(white, 'N', vKnight));
    (board[7][6])->setPiece(new Piece(white, 'N', vKnight));
    // Bishops
    (board[7][2])->setPiece(new Piece(white, 'B', vBishop));
    (board[7][5])->setPiece(new Piece(white, 'B', vBishop));
    // Queen
    (board[7][3])->setPiece(new Piece(white, 'Q', vQueen));
    // King
    (board[7][4])->setPiece(new Piece(white, 'K', vKing));
    // Pawns
    (board[6][0])->setPiece(new Piece(white, 'P', vPawn));
    (board[6][1])->setPiece(new Piece(white, 'P', vPawn));
    (board[6][2])->setPiece(new Piece(white, 'P', vPawn));
    (board[6][3])->setPiece(new Piece(white, 'P', vPawn));
    (board[6][4])->setPiece(new Piece(white, 'P', vPawn));
    (board[6][5])->setPiece(new Piece(white, 'P', vPawn));
    (board[6][6])->setPiece(new Piece(white, 'P', vPawn));
    (board[6][7])->setPiece(new Piece(white, 'P', vPawn));
}

void Board::movePiece(Player player, char *move, int *status_code)
{
    int src_y = move[0] - 'a';
    int src_x = 7 - (move[1] - '0' - 1);
    int dst_y = move[2] - 'a';
    int dst_x = 7 - (move[3] - '0' - 1);
    Square *src_square, *dst_square;
    Piece *piece;

    *status_code = SUCCESS;

    // Check if the source square is valid
    if (src_x < 0 || src_x > 7 || src_y < 0 || src_y > 7) {
        *status_code = INVALID_SOURCE_ERROR;
        return;
    } else {
        src_square = board[src_x][src_y];
    }

    // Check if the destination square is valid
    if (dst_x < 0 || dst_x > 7 || dst_y < 0 || dst_y > 7) {
        *status_code = INVALID_DESTINATION_ERROR;
        return;
    } else {
        dst_square = board[dst_x][dst_y];
    }

    // Check if the source square contains a piece
    if (src_square->getPiece() == nullptr) {
        *status_code = INVALID_SOURCE_PIECE_ERROR;
        return;
    } else {
        piece = src_square->getPiece();
    }

    // Check if the source square contains a valid piece for the current player
    if (src_square->getPiece()->getColour().getColour() != player.getColour().getColour()) {
        *status_code = INVALID_COLOUR_ERROR;
        return;
    } else {
        piece = src_square->getPiece();
    }

    // TODO: Check if the piece is allowed to move to the destination
    /**
     * For testing I am only checking if a square is empty before I move it
     * 
     * Future versions will check if it is a valid move for the piece
     * Another check will determine if it is capturing anything
     */
    // Check if the destination contains a piece
    if (dst_square->getPiece() != nullptr) {
        *status_code = OCCUPIED_DESTINATION_ERROR;
        return;
    } else {
        dst_square->setPiece(piece);
        src_square->setPiece(nullptr);
    }
}

void Board::print()
{
    std::cout << "\n   ";
    for (int x = 0; x < 8; x++) {
        std::cout << " " << (char) ('a' + x) << "   ";
    }
    std::cout << "\n   ";
    for (int x = 0; x < 8; x++) {
        std::cout << "---- ";
    }
    std::cout << "\n";

    for (int x = 0; x < 8; x++) {
        std::cout << (char) ('8' - x) << " |";
        for (int y = 0; y < 8; y++) {
            if (board[x][y]->getPiece() != nullptr)
                std::cout << " " << board[x][y]->getPiece()->getColour().getColour() << board[x][y]->getPiece()->getName() << " |";
            else
                std::cout << "    |";
        }
        std::cout << " " << (char) ('8' - x) << "\n";

        std::cout << "   ";
        for (int y = 0; y < 8; y++) {
            std::cout << "---- ";
        }
        std::cout << "\n";
    }

    std::cout << "   ";
    for (int x = 0; x < 8; x++) {
        std::cout << " " << (char) ('a' + x) << "   ";
    }
    std::cout << "\n";
}
