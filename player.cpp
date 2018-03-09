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
    auto start = std::chrono::high_resolution_clock::now();
    board->doMove(opponentsMove, OPPONENT_SIDE);
    std::list<Move> moves = board->getMoves(side);
    // TODO: calculate the heuristic of each move
    if (moves.size() == 0) {
        return nullptr;
    }
    std::list<Move>::iterator it = moves.begin();
    int maxWeight = INT_MIN;
    Move move = *it;
    int weight;
    int depth = (testingMinimax? 2 : 5);
    Board *temp;
    //until time is up, look for better moves
    auto end = std::chrono::high_resolution_clock::now();
    while ((msLeft <= 0 ||
            (end - start).count() * 1000 >  (msLeft - 25))  &&
           it != moves.end()) {
        temp = this->board->copy();
        temp->doMove(&(*it), side);
        weight = minimax(temp, depth, OPPONENT_SIDE, INT_MIN, INT_MAX);
        //weight = temp->weightMove(side);
        if (weight > maxWeight) {
            move = *it;
            maxWeight = weight;
        }
        delete temp;
        it++;
        end = std::chrono::high_resolution_clock::now();
    }
    //Return the move
    Move *ret = new Move(move.getX(),move.getY());
    board->doMove(ret, side);
    return ret;
}

int Player::minimax(Board *curr_board, int depth, Side side, int alpha, int beta) {
    if (depth <= 1 || curr_board->isDone()){
        if (testingMinimax) {
            return curr_board->simpleHeuristic(this->side);
        }
        return curr_board->weightMove(this->side);
    }
    int a = (side == this->side ? INT_MIN : INT_MAX);
    Board *temp;
    std::list<Move> moves = curr_board->getMoves(side);
    std::list<Move>::iterator it = moves.begin(); 
    while (it != moves.end()) {
        temp = curr_board->copy();
        temp->doMove(&(*it), side);
        int res = minimax(temp, depth - 1, OPPONENT_SIDE, alpha, beta);
        a = (side == this->side ? std::max(a, res) : std::min(a, res));
        delete temp;
        //pruning
        if (side == this->side && a >= beta) return a;
        else if (side != this->side && a <= alpha) return a;
        if (side == this->side && a > alpha) alpha = a;
        else if (side != this->side && a < beta) beta = a;
        it++;
    }
    return a;
}
