// GigoiChessEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Bitboard.h"
#include "Moves.h"
#include "Utilities.h"

using namespace std;

int main()
{

    char startingBoard[8][8] =
    {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    };
    char testBoard[8][8] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };


    Bitboard gb;
    Moves mvs;
    Utilities u;
    string possibleMovesW, possibleMovesB;

    //gb.drawBoard(startingBoard);
    gb.convertArrToBitboard(startingBoard);
    //gb.convertBitBoardToArr();

    u.perfTRoot(gb, true, 0);





    return 0;
}

