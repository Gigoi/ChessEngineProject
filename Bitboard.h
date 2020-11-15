#pragma once
#include <string>


using namespace std;

class Bitboard
{
public:

	long long WP = 0, WN = 0, WB = 0, WR = 0, WQ = 0, WK = 0, BP = 0, BN = 0, BB = 0, BR = 0, BQ = 0, BK = 0;
	long long NOT_WHITE_PIECES = ~(WP | WN | WB | WR | WQ | WK | BK);
	long long NOT_BLACK_PIECES;
	bool WCR = true, BCR = true;

	void convertArrToBitboard(char boardArr[8][8]);
	void convertBitBoardToArr();
	void drawBoard(char boardArr[8][8]);

	bool isSlider(long long b);
	int getSqPos(long long bb);

private:
	void p_convertArrToBitboard(char boardArr[8][8]);
	long long p_ConvertStringToBinary(string b);
	void p_convertBitBoardToArr();
	void p_drawBoard(char boardArr[8][8]);



};

