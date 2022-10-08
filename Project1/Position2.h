#pragma once
#include<iostream>
#include<string>

/**
  * A class storing a Connect 4 position.
  * All function are relative to the current player to play.
  *
  * Position2 containing aligment are not supported by this class
  * as it simplifies implementation and there is no point solving an already won position
  */

class Position2
{
public:
    static const int WIDTH = 7;  // Width of the board
    static const int HEIGHT = 6; // Height of the board
    static_assert(WIDTH < 10, "Board's width must be less than 10");

    //default constructor to initialize position to be empty
    Position2() : board{ 0 }, height{ 0 }, moves{ 0 } {}  

    //checks if the position is playable
    bool canPlay(int col) const;

    /*
      * Plays a sequence of successive played columns, mainly used to initilize a board.
      * @param seq: a sequence of digits corresponding to the 1-based index of the column played.
      *
      * @return number of played moves. Processing will stop at first invalid move that can be:
      *           - invalid character (non digit, or digit >= WIDTH)
      *           - playing a colum the is already full
      *           - playing a column that makes an aligment (we only solve non).
      *         Caller can check if the move sequence was valid by comparing the number of
      *         processed moves to the length of the sequence.
      */
    unsigned int play(std::string seq);

    //checks if the move is the winning move
    //This function should never be called on a non-playable column.
    bool isWinningMove(int col) const;

   //just plays the column .... Different from above play
    void play(int col);

    //getter function to return moves played from the beginnin of the game
    unsigned int nbMoves() const; //getter function to return moves played from the beginnin of the game

    void try_playing(int col);

    int ht(int col);

    
    int board[WIDTH][HEIGHT]; // 0 if cell is empty, 1 for first player and 2 for second player.
    int height[WIDTH];        // number of stones per column
    unsigned int moves;       // number of moves played since the beinning of the game.

    
private:
    
};