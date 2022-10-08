#include "Position2.h"

bool Position2::canPlay(int col) const
{
	return height[col] < HEIGHT;
}



/*
       * Plays a sequence of successive played columns, mainly used to initilize a board.
       * @param seq: a sequence of digits corresponding to the 1-based index of the column played.
       *
       * @return number of played moves. Processing will stop at first invalid move that can be:
       *           - invalid character (non digit, or digit >= WIDTH)
       *           - playing a colum that is already full
       *           - playing a column that makes an aligment (we only solve non).
       *         Caller can check if the move sequence was valid by comparing the number of
       *         processed moves to the length of the sequence.
       */
unsigned int Position2::play(std::string seq)
{
	for (unsigned int i = 0; i < seq.size(); i++) {
		int col = seq[i] - '1';
		if (col < 0 || col >= Position2::WIDTH || !canPlay(col) || isWinningMove(col)) return i; // invalid move
		play(col);
	}
	return seq.size();
}

/**
       * Indicates whether the current player wins by playing a given column.
       * This function should never be called on a non-playable column.
       * @param col: 0-based index of a playable column.
       * @return true if current player makes an alignment by playing the corresponding column col.
       */
bool Position2::isWinningMove(int col) const
{
    int current_player = 1 + moves % 2;
    // check for vertical alignments
    if (height[col] >= 3
        && board[col][height[col] - 1] == current_player
        && board[col][height[col] - 2] == current_player
        && board[col][height[col] - 3] == current_player)
        return true;

    for (int dy = -1; dy <= 1; dy++) {    // Iterate on horizontal (dy = 0) or two diagonal directions (dy = -1 or dy = 1).
        int nb = 0;                       // counter of the number of stones of current player surronding the played stone in tested direction.
        for (int dx = -1; dx <= 1; dx += 2) // count continuous stones of current player on the left, then right of the played column.
            for (int x = col + dx, y = height[col] + dx * dy; x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && board[x][y] == current_player; nb++) {
                x += dx;
                y += dx * dy;
            }
        if (nb >= 3) return true; // there is an aligment if at least 3 other stones of the current user 
                                 // are surronding the played stone in the tested direction.
    }
    return false;
}



void Position2::play(int col)
{
	board[col][height[col]] = 1 + moves % 2;    // 1 + moves % 2 gives which player's move to add to the given position 
	height[col]++;
	moves++;
}

unsigned int Position2::nbMoves() const
{
    return moves;
}

void Position2::try_playing(int col)
{
    if (canPlay(col)) {
        play(col);
    }
    else {
        std::cout << "ya you can't play that move"<<std::endl;
    }
}

int Position2::ht(int col)
{
    return height[col];
}




