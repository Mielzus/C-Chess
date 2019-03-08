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
    (board[0][0])->setPiece(new Rook(black));
    (board[0][7])->setPiece(new Rook(black));
    // Knights
    (board[0][1])->setPiece(new Knight(black));
    (board[0][6])->setPiece(new Knight(black));
    // Bishops
    (board[0][5])->setPiece(new Bishop(black));
    (board[0][2])->setPiece(new Bishop(black));
    // Queen
    (board[0][3])->setPiece(new Queen(black));
    // King
    (board[0][4])->setPiece(new King(black));
    // Pawns
    (board[1][1])->setPiece(new Pawn(black));
    (board[1][0])->setPiece(new Pawn(black));
    (board[1][2])->setPiece(new Pawn(black));
    (board[1][3])->setPiece(new Pawn(black));
    (board[1][4])->setPiece(new Pawn(black));
    (board[1][5])->setPiece(new Pawn(black));
    (board[1][6])->setPiece(new Pawn(black));
    (board[1][7])->setPiece(new Pawn(black));

    // Set up White pieces
    // Rooks
    (board[7][0])->setPiece(new Rook(white));
    (board[7][7])->setPiece(new Rook(white));
    // Knights
    (board[7][1])->setPiece(new Knight(white));
    (board[7][6])->setPiece(new Knight(white));
    // Bishops
    (board[7][2])->setPiece(new Bishop(white));
    (board[7][5])->setPiece(new Bishop(white));
    // Queen
    (board[7][3])->setPiece(new Queen(white));
    // King
    (board[7][4])->setPiece(new King(white));
    // Pawns
    (board[6][0])->setPiece(new Pawn(white));
    (board[6][1])->setPiece(new Pawn(white));
    (board[6][2])->setPiece(new Pawn(white));
    (board[6][3])->setPiece(new Pawn(white));
    (board[6][4])->setPiece(new Pawn(white));
    (board[6][5])->setPiece(new Pawn(white));
    (board[6][6])->setPiece(new Pawn(white));
    (board[6][7])->setPiece(new Pawn(white));
}

// TODO:
// Add check each time the king moves to ensure it is not in check
// If the piece is a pawn check if it is at the end for a promotion
//
// - check
// - checkmate
// - Pawn promotion
// - en passant
// - castling
void Board::movePiece(Player *player, char *move, int *status_code)
{
    int src_y = move[0] - 'a';
    int src_x = 7 - (move[1] - '0' - 1);
    int dst_y = move[2] - 'a';
    int dst_x = 7 - (move[3] - '0' - 1);
    Square *src_square, *dst_square;
    Piece *piece;

    // Check if the source square is valid
    if (src_x < 0 || src_x > 7 || src_y < 0 || src_y > 7) {
        *status_code = INVALID_SOURCE_ERROR;
        return;
    }
    src_square = board[src_x][src_y];

    // Check if the destination square is valid
    if (dst_x < 0 || dst_x > 7 || dst_y < 0 || dst_y > 7) {
        *status_code = INVALID_DESTINATION_ERROR;
        return;
    }
    dst_square = board[dst_x][dst_y];

    // Check if the source square contains a piece
    piece = src_square->getPiece();
    if (src_square->getPiece() == nullptr) {
        *status_code = INVALID_SOURCE_PIECE_ERROR;
        return;
    }

    // Check if the source square contains a valid piece for the current player
    if (src_square->getPiece()->getColour().getColour() != player->getColour().getColour()) {
        *status_code = INVALID_COLOUR_ERROR;
        return;
    }

    // Check if there is a piece on the destination squre
    if (dst_square->getPiece() == nullptr) {
        // Check if the piece is allowed to move to the destination
        if (!piece->checkMove(src_square->getX(), src_square->getY(), dst_square->getX(), dst_square->getY())) {
            *status_code = INVALID_MOVE_ERROR;
            return;
        }
    } else {
        // Don't allow friendly capture
        if (dst_square->getPiece()->getColour().getColour() == src_square->getPiece()->getColour().getColour()){
            *status_code = INVALID_MOVE_ERROR;
            return;
        }
        // Check if the piece is allowed to move to and capture the target piece
        if (!piece->checkCapture(src_square->getX(), src_square->getY(), dst_square->getX(), dst_square->getY())) {
            *status_code = INVALID_MOVE_ERROR;
            return;
        } else {
            // TODO: At the captured piece to a list somewhere
            player->addScore(dst_square->getPiece()->getValue());
            player->addPiece(dst_square->getPiece()->getName());
            delete dst_square->getPiece();
        }
    }

    // Check if the path to the destination is clear
    if (!this->checkPath(piece, src_square->getX(), src_square->getY(), dst_square->getX(), dst_square->getY())) {
        *status_code = INVALID_MOVE_ERROR;
        return;
    }

    *status_code = SUCCESS;
    piece->incrementMoveCount();
    dst_square->setPiece(piece);
    src_square->setPiece(nullptr);
}

int Board::checkPath(Piece *piece, int src_x, int src_y, int dst_x, int dst_y)
{
    // Check if the path to the destination is clear
    int **path;
    int pathCount, pathX, pathY;
    int invalidPath = 0;
    Square *pathSquare;

    path = piece->generatePath(src_x, src_y, dst_x, dst_y, &pathCount);

    for (int i = 0; i < pathCount; i++) {
        pathX = path[i][0];
        pathY = path[i][1];
        free(path[i]);

        pathSquare = this->board[pathY][pathX];
        if (pathSquare->getPiece() != nullptr) {
            invalidPath = 1;
        }
    }

    // Free path array
    free(path);

    return !invalidPath;
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
