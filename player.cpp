#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    board = new Board();
    this->side = side;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's move before calculating your own move
     */
    time_t start_time;
    time(&start_time);
    // if we are out of time, return
    /* if (msLeft > 0 &&
        difftime(start_time, time(NULL)) > (double) msLeft / 1000.0) {
        return nullptr;
        } */
    board->doMove(opponentsMove, OPPONENT_SIDE);
    std::list<Move> moves = board->getMoves(side);
    // TODO: calculate the heuristic of each move
    if (moves.size() == 0) {
        return nullptr;
    }
    //For now, return any old move
    Move first = *(moves.begin());
    Move *move = new Move(first.getX(),first.getY());
    board->doMove(move, side);
    return move;
}

int *Player::minimax(Board board, int depth, Side side) {
    if (depth == 0 || node == nullptr){
        return board;
    }
}
    
