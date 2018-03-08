#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.hpp"
#include <list>
#include <iostream>


using namespace std;

class Board {

private:
    bitset<64> black;
    bitset<64> taken;
    int turn_num;

    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);

public:
    Board();
    ~Board();
    Board *copy();
    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();
    void setBoard(char data[]);
    std::list<Move> getMoves(Side side);
    int weightMove(Side side);
    int simpleHeuristic(Side side);
};

#endif
