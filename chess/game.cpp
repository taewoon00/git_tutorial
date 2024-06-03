#include "game.h"

using namespace std;


void Game::read_file(string filename)
{
    ifstream ifs(filename);
    if (!ifs)
    {
        cerr << "Error: file open failed" << endl;
        exit(1);
    }
    
    ifs >> problem_id;
    ifs.ignore();
    getline(ifs, problem_specification);

    cout << "problem_id: [" << problem_id << "]" << endl;
    cout << "problem_specification: [" << problem_specification << "]" << endl;

    // TODO: CREATE CHESSBOARD
    int width, height;
    ifs >> width >> height;
    board = new ChessBoard(width, height);

    string row;
    for (int y = 0; y < height; ++y) {
        ifs >> row;
        for (int x = 0; x < width; ++x) {
            if (row[x] != '.') {
                string color = isupper(row[x]) ? "White" : "Black";
                string type = char_to_piece[toupper(row[x])];
                ChessPiece* piece = create_piece(color, type, x, y);
                board->tiles[x][y] = piece;
                if (color == "White") {
                    board->white_pieces.insert(piece);
                } else {
                    board->black_pieces.insert(piece);
                }
            }
        }
    }

}

void Game::open_output_file(string filename)
{
    ofs.open(filename);
    if (!ofs)
    {
        cerr << "Error: file open failed" << endl;
        exit(1);
    }
}

void Game::solve()
{
    switch (problem_id)
    {
    case 0:
        solve_print_board();
        break;
    case 1:
        solve_print_possible_moves();
        break;
    case 2:
        solve_check();
        break;
    case 3:
        solve_checkmate();
        break;
    case 4:
        solve_checkmate_in_one_move();
        break;
    default:
        cout << "Invalid problem_id" << endl;
        break;
    }
    return;
}

void Game::solve_print_board()
{
    ofs << *board;
}

void Game::solve_print_possible_moves()
{
    string color = isupper(problem_specification[0]) ? "White" : "Black";
    string type = char_to_piece[toupper(problem_specification[0])];
    int x = problem_specification[1] - 'a';
    int y = problem_specification[2] - '1';
    
    ChessPiece* piece = board->tiles[x][y];

    if (!piece) {
        cerr << "Error: No piece found at the specified position." << endl;
        return;
    }

    if (piece->get_color() != color || piece->get_type() != type) {
        cerr << "Error: Mismatch in piece type or color at the specified position." << endl;
        return;
    }

    vector<tuple<MoveType, Direction, int>> possible_moves = piece->get_possible_moves();

    ChessBoard* display_board = new ChessBoard(board->width, board->height);
    *display_board = *board;  // Ensure the board is copied properly

    for (auto& move : possible_moves) {
        MoveType move_type = get<0>(move);
        Direction dir = get<1>(move);
        int distance = get<2>(move);

        int dx = direction_to_pair[dir].first * distance;
        int dy = direction_to_pair[dir].second * distance;
        int nx = x + dx;
        int ny = y + dy;

        if (nx >= 0 && nx < board->width && ny >= 0 && ny < board->height) {
            if (move_type == MOVE) {
                if (board->tiles[nx][ny] == nullptr) {
                    display_board->tiles[nx][ny] = create_piece("White", "King", nx, ny, 1);  // Mark as possible move
                }
            } else if (move_type == ATTACK) {
                if (board->tiles[nx][ny] != nullptr && board->tiles[nx][ny]->get_color() != piece->get_color()) {
                    display_board->tiles[nx][ny] = create_piece("White", "King", nx, ny, 2);  // Mark as possible attack
                }
            }
        }
    }

    ofs << *display_board;

    // Clean up dynamically allocated memory
    for (int i = 0; i < display_board->width; ++i) {
        for (int j = 0; j < display_board->height; ++j) {
            delete display_board->tiles[i][j];
        }
        delete[] display_board->tiles[i];
    }
    delete[] display_board->tiles;
    delete display_board;
}





int Game::solve_check()
{
    // TODO
    // EXAMPLE: "Black king is in check"
    //          "White king is not in check"

    return 0;
}

int Game::solve_checkmate()
{
    // TODO 
    // EXAMPLE: "Black king is checkmated"
    //          "White king is not checkmated"


    return 0;
}

int Game::solve_checkmate_in_one_move()
{
    // TODO
    // EXAMPLE: "Black king is checkmated in one move"
    //          "White king is not checkmated in one move"

    return 0;
}