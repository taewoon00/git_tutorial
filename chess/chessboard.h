#pragma once
/*
 * board.h
 */
#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cctype>

#include "utils.h"
#include "chesspiece.h"

using namespace std;


class ChessBoard
{
public:
    void initialize_board();
    
    ChessBoard(int width, int height): width(width), height(height) { initialize_board(); }

    ChessBoard& operator=(const ChessBoard& other);
    
    friend ostream& operator<<(ostream& os, const ChessBoard& board);
    ChessPiece* operator[](string s);

    ChessBoard(const ChessBoard& other);

    // NOTE: YOU CAN ADD MORE MEMBER FUNCTIONS HERE
    friend class Game;
    

private: 
    int width, height;
    ChessPiece*** tiles;
    set<ChessPiece*> white_pieces;
    set<ChessPiece*> black_pieces;

    // NOTE: YOU CAN ADD MORE MEMBER VARIABLESS HERE

};

// NOTE: YOU CAN ADD MORE FUNCTIONS HERE

#endif /* CHESSBOARD_H_ */