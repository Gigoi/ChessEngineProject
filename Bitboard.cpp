#include "Bitboard.h"
#include <iostream>
#include <string>
#include <Bits.h>
#include <bitset>
#include <math.h>

using namespace std;

///////////PUBLIC FUNCTIONS:://///////////
void Bitboard::convertArrToBitboard(char boardArr[8][8]) {
	p_convertArrToBitboard(boardArr);
}
void Bitboard::convertBitBoardToArr() {
	p_convertBitBoardToArr();
}
void Bitboard::drawBoard(char boardArr[8][8]) {
	p_drawBoard(boardArr);
}

bool Bitboard::isSlider(long long b) {
	long long s;
	int i = getSqPos(b);
	s = b >> i;
	if (((s & (BP >> i)) == 1) || ((s & (WP >> i)) == 1) || ((s & (BN >> i)) == 1) || ((s & (WN >> i)) == 1)) {
		return false;
	}

	return true;
}

int Bitboard::getSqPos(long long bb) {
	for (int i = 0; i < 64; i++)
	{
		if (((bb >> i) & 1) == 1) {
			return i;
		}
	}
}

///////////PRIVATE FUNCTIONS:://///////////
void Bitboard::p_convertArrToBitboard(char boardArr[8][8]) {
	string binary;
	for (int i = 0; i < 64; i++)
	{
		//cout << "i: " << i / 8 << " k: " << i % 8 << endl;
		binary = "0000000000000000000000000000000000000000000000000000000000000000";
		binary = binary.substr(0, i) + "1" + binary.substr(i + 1);
		switch (boardArr[i / 8][i % 8]) {
		case 'p':
			BP += p_ConvertStringToBinary(binary);
			break;
		case 'r':
			BR += p_ConvertStringToBinary(binary);
			break;
		case 'b':
			BB += p_ConvertStringToBinary(binary);
			break;
		case 'q':
			BQ += p_ConvertStringToBinary(binary);
			break;
		case 'k':
			BK += p_ConvertStringToBinary(binary);
			break;
		case 'n':
			BN += p_ConvertStringToBinary(binary);
			break;
		case 'P':
			WP += p_ConvertStringToBinary(binary);
			break;
		case 'R':
			WR += p_ConvertStringToBinary(binary);
			break;
		case 'B':
			WB += p_ConvertStringToBinary(binary);
			break;
		case 'N':
			WN += p_ConvertStringToBinary(binary);
			break;
		case 'Q':
			WQ += p_ConvertStringToBinary(binary);
			break;
		case 'K':
			WK += p_ConvertStringToBinary(binary);
			break;
		}

	}
}
void Bitboard::p_convertBitBoardToArr() {
	char chessBoard[8][8];
	for (int i = 0; i < 64; i++)
	{
		chessBoard[i / 8][i % 8] = '.';
	}
	//j = Bit shift counter
	int j = 63;
	for (int i = 0; i < 64; i++)
	{
		if (((WP >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = 'P'; }
		if (((WR >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = 'R'; }
		if (((WB >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = 'B'; }
		if (((WN >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = 'N'; }
		if (((WQ >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = 'Q'; }
		if (((WK >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = 'K'; }
		if (((BP >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = 'p'; }
		if (((BR >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = 'r'; }
		if (((BB >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = 'b'; }
		if (((BN >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = 'n'; }
		if (((BQ >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = 'q'; }
		if (((BK >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = 'k'; }
		j--;
	}

	p_drawBoard(chessBoard);
}

long long Bitboard::p_ConvertStringToBinary(string b) {
	//Check if leading bit is '0', if not then continue conversion, if so handle special case
	if (b[0] == '0') {
		return strtoll(b.c_str(), nullptr, 2);
	}
	else {
		string tmp = "1" + b.substr(1);
		return strtoll(tmp.c_str(), nullptr, 2) + 1;
	}
}

void Bitboard::p_drawBoard(char boardArr[8][8]) {
	cout << "---------" << endl;
	for (int i = 0; i < 8; i++) {
		cout << '|';
		for (int k = 0; k < 8; k++)
		{
			cout << boardArr[i][k];
		}
		cout << '|' << endl;
	}
	cout << "---------" << endl;
}
