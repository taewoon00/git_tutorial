#pragma once
/*
 * board.h
 */
#ifndef CHESSPIECE_H_
#define CHESSPIECE_H_

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

using namespace std;


// NOTE: DO NOT CHANGE `Chesspiece` CLASS EXCEPT THE RETURN TYPE OF `get_possible_moves()`
class ChessPiece
{
public:
    ChessPiece(string, string, int, int, int=0);
    ChessPiece(const ChessPiece& other);
    friend ostream& operator<<(ostream& os, const ChessPiece& piece);

    string get_color() { return color; }
    string get_type() { return type; }

    int get_x() { return x; }
    int get_y() { return y; }
    int get_flag() { return flag; }

    void set_x(int x) { this->x = x; }
    void set_y(int y) { this->y = y; }
    void set_flag(int flag) { this->flag = flag; }

    virtual void move(int x, int y) { this->x = x; this->y = y; };

    // NOTE: YOU CAN MODIFY THE RETURN TYPE OF THE FUNCTION BELOW
    virtual vector<tuple<MoveType, Direction, int>> get_possible_moves() = 0; 

protected:
    string color;
    string type;
    int x;
    int y;
    int flag;
};

ChessPiece* create_piece(string color, string type, int x, int y, int flag=0);

// NOTE: INHERIT ChessPiece CLASS AND IMPLEMENT CLASSES
// NOTE: FILL FREE TO ADD ANY MEMBER VARIABLES OR FUNCTIONS

class King : public ChessPiece
{
    // TODO
public:
    King(string color, int x, int y, int flag = 0) : ChessPiece(color, "King", x, y, flag) {}

    vector<tuple<MoveType, Direction, int>> get_possible_moves() override {
        vector<tuple<MoveType, Direction, int>> moves;
        for (Direction dir : {UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT}) {
            moves.push_back(make_tuple(MOVE, dir, 1));
            moves.push_back(make_tuple(ATTACK, dir, 1));
        }
        return moves;
    }
};

class Queen : public ChessPiece
{
    // TODO
public:
    Queen(string color, int x, int y, int flag = 0) : ChessPiece(color, "Queen", x, y, flag) {}

    vector<tuple<MoveType, Direction, int>> get_possible_moves() override {
        vector<tuple<MoveType, Direction, int>> moves;
        for (Direction dir : {UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT}) {
            for (int i = 1; i < MAX_BOARD_SIZE; ++i) {
                moves.push_back(make_tuple(MOVE, dir, i));
                moves.push_back(make_tuple(ATTACK, dir, i));                
            }
        }
        return moves;
    }
};

class Rook : public ChessPiece
{
    // TODO
public:
    Rook(string color, int x, int y, int flag = 0) : ChessPiece(color, "Rook", x, y, flag) {}

    vector<tuple<MoveType, Direction, int>> get_possible_moves() override {
        vector<tuple<MoveType, Direction, int>> moves;
        for (Direction dir : {UP, DOWN, LEFT, RIGHT}) {
            for (int i = 1; i < MAX_BOARD_SIZE; ++i) {
                moves.push_back(make_tuple(MOVE, dir, i));
                moves.push_back(make_tuple(ATTACK, dir, i));
            }
        }
        return moves;
    }
};

class Bishop : public ChessPiece
{
    // TODO
public:
    Bishop(string color, int x, int y, int flag = 0) : ChessPiece(color, "Bishop", x, y, flag) {}

    vector<tuple<MoveType, Direction, int>> get_possible_moves() override {
        vector<tuple<MoveType, Direction, int>> moves;
        for (Direction dir : {UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT}) {
            for (int i = 1; i < MAX_BOARD_SIZE; ++i) {
                moves.push_back(make_tuple(MOVE, dir, i));
                moves.push_back(make_tuple(ATTACK, dir, i));
            }
        }
        return moves;
    }
};

class Knight : public ChessPiece
{
    // TODO
public:
    Knight(string color, int x, int y, int flag = 0) : ChessPiece(color, "Knight", x, y, flag) {}

    vector<tuple<MoveType, Direction, int>> get_possible_moves() override {
        vector<tuple<MoveType, Direction, int>> moves;
        for (Direction dir : {UP_UP_LEFT, UP_UP_RIGHT, DOWN_DOWN_LEFT, DOWN_DOWN_RIGHT, LEFT_LEFT_UP, LEFT_LEFT_DOWN, RIGHT_RIGHT_UP, RIGHT_RIGHT_DOWN}) {
            moves.push_back(make_tuple(MOVE, dir, 1));
            moves.push_back(make_tuple(ATTACK, dir, 1));
        }
        return moves;
    }
};

class Pawn : public ChessPiece
{
    // TODO
public:
    Pawn(string color, int x, int y, int flag = 0) : ChessPiece(color, "Pawn", x, y, flag) {}

    vector<tuple<MoveType, Direction, int>> get_possible_moves() override {
        vector<tuple<MoveType, Direction, int>> moves;
        int direction = (color == "White") ? 1 : -1;

        moves.push_back(make_tuple(MOVE, static_cast<Direction>(UP * direction), 1));
        
        moves.push_back(make_tuple(ATTACK, static_cast<Direction>(UP_LEFT * direction), 1));
        moves.push_back(make_tuple(ATTACK, static_cast<Direction>(UP_RIGHT * direction), 1));

        if ((color == "White" && y == 1) || (color == "Black" && y == 6)) {
            moves.push_back(make_tuple(MOVE, static_cast<Direction>(UP * direction), 2));
        }

        return moves;
    }
};

// NOTE: YOU CAN ADD OTHER FUNCTIONS HERE

#endif /* CHESSPIECE_H_ */