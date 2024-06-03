#include "chessboard.h"

using namespace std;

void ChessBoard::initialize_board()
{
    // TODO: implement initialize_board
    tiles = new ChessPiece **[width];
    for (int i = 0; i < width; ++i)
    {
        tiles[i] = new ChessPiece *[height];
        for (int j = 0; j < height; ++j)
        {
            tiles[i][j] = nullptr;
        }
    }
}

ostream& operator<<(ostream& os, const ChessBoard& board)
{
    // TODO: implement operator<<
    for (int y = 0; y < board.height; ++y) {
        for (int x = 0; x < board.width; ++x) {
            if (board.tiles[x][y] == nullptr) {
                os << '.';
            } else {
                os << *(board.tiles[x][y]);
            }
        }
        os << '\n';
    }
    return os;
}

ChessPiece* ChessBoard::operator[](string s)
{
    // TODO: implement operator[]
    int x = s[0] - 'a';
    int y = s[1] - '1';
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[x][y];
    }
    return nullptr;
}

ChessBoard& ChessBoard::operator=(const ChessBoard& other)
{
    // TODO: implement operator=
    if (this == &other) return *this;
    
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            delete tiles[i][j];
        }
        delete[] tiles[i];
    }
    delete[] tiles;
    
    width = other.width;
    height = other.height;
    initialize_board();
    
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (other.tiles[i][j] != nullptr) {
                tiles[i][j] = create_piece(other.tiles[i][j]->get_color(), other.tiles[i][j]->get_type(), i, j, other.tiles[i][j]->get_flag());
            }
        }
    }
    white_pieces = other.white_pieces;
    black_pieces = other.black_pieces;
    
    return *this;
}

ChessBoard::ChessBoard(const ChessBoard& other)
{
    // TODO: implement copy constructor
    width = other.width;
    height = other.height;
    initialize_board();
    
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (other.tiles[i][j] != nullptr) {
                tiles[i][j] = create_piece(other.tiles[i][j]->get_color(), other.tiles[i][j]->get_type(), i, j, other.tiles[i][j]->get_flag());
            }
        }
    }
    white_pieces = other.white_pieces;
    black_pieces = other.black_pieces;
}

// NOTE: YOU CAN ADD MORE FUNCTIONS HERE