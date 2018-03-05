#ifndef __PLAYER_H__
#define __PLAYER_H__



#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <climits>
#include <algorithm>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    void setBoard(char *data);
    Board *board;
    Side side;
    Move *doMove(Move *opponentsMove, int msLeft);
    int minimax(Move *move, Board *curr_board, int depth, Side side);
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
