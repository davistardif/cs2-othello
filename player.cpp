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
// sets the player's board to a given state
void Player::setBoard(char data[]){
    this->board->setBoard(data);
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
    board->doMove(opponentsMove, OPPONENT_SIDE);
    std::list<Move> moves = board->getMoves(side);
    // TODO: calculate the heuristic of each move
    if (moves.size() == 0) {
        return nullptr;
    }
    std::list<Move>::iterator it = moves.begin();
    int minWeight = INT_MAX;
    Move move = *it;
    int weight;
    //until time is up, look for better moves
    while ((msLeft < 0 ||
           difftime(start_time, time(NULL)) > (double) (msLeft - 25) / 1000.)  &&
           it != moves.end()) {
        //weight = minimax(&(*it), board, 2, side);
        weight = board->weightMove(&(*it), side);
        if (weight < minWeight) {
            move = *it;
            minWeight = weight;
        }
        it++;
    }
    //Return the move
    Move *ret = new Move(move.getX(),move.getY());
    board->doMove(ret, side);
    return ret;
}

int Player::minimax(Move *move, Board *curr_board, int depth, Side side) {
    
    if (depth <= 0 || move == nullptr){
        return curr_board->simpleHeuristic(move, side);
    }
    int a = INT_MIN;
    Board *temp = curr_board->copy();
    temp->doMove(move, side);
    std::list<Move> moves = temp->getMoves(side);
    std::list<Move>::iterator it = moves.begin(); 
    while (it != moves.end()) {
        a = std::max(a, -minimax(&(*it), temp, depth - 1, OPPONENT_SIDE));
        it++;
    }
    delete temp;
    return a;
}
