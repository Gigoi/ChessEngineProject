#pragma once

#include <string>
#include "Bitboard.h"

using namespace std;

enum Type {
	QUIET,
	CAPTURE,
	QPROMOTION,
	NPROMOTION,
	BPROMOTION,
	RPROMOTION,
	qPROMOTION,
	nPROMOTION,
	bPROMOTION,
	rPROMOTION,
	CPROMOTION,
	CASTLE,
	ENPAS
};

struct Move {
	int start;
	int dest;
	Type t;
};

enum Color
{
	WHITE,
	BLACK
};

class Moves {
public:
	Move moveList[274];
	int numMoves = 0;

	long long FILE_A = -9187201950435737472LL;
	long long FILE_H = 72340172838076673LL;
	long long RANK_1 = 255LL;
	long long RANK_4 = 4278190080LL;
	long long RANK_5 = 1095216660480LL;
	long long RANK_8 = -72057594037927936LL;
	long long FILE_GH = 217020518514230019;
	long long FILE_AB = -4557430888798830400LL;

	long long RankMasks8[8] = {
		/*0xFFLL, 0xFF00LL, 0xFF0000LL, 0xFF000000LL, 0xFF00000000LL, 0xFF0000000000LL, 0xFF000000000000LL, 0xFF00000000000000LL*/
		255LL, 65280LL, 16711680LL, 4278190080LL, 1095216660480LL, 280375465082880LL, 71776119061217280LL, -72057594037927936LL
	};
	long long FileMask8[8] = {
		/*0x8080808080808080LL, 0x4040404040404040LL, 0x2020202020202020LL, 0x1010101010101010LL, 0x808080808080808LL, 0x404040404040404LL, 0x202020202020202LL, 0x101010101010101LL*/
		-9187201950435737472LL, 4629771061636907072LL, 2314885530818453536LL, 1157442765409226768LL, 578721382704613384LL, 289360691352306692LL, 144680345676153346LL, 72340172838076673LL
	};
	long long DiagnalMask[15] = {
		1LL, 258LL, 66052LL, 16909320LL, 4328785936LL, 1108169199648LL, 283691315109952LL, 72624976668147840LL,
		145249953336295424LL, 290499906672525312LL, 580999813328273408LL, 1161999622361579520LL, 2323998145211531264LL,
		4647714815446351872LL, (signed long long)9223372036854775808LL
	};
	long long AntiDiagnalMask[15] = {
		128LL, 32832LL, 8405024LL, 2151686160LL, 550831656968LL, 141012904183812LL, 36099303471055874LL, (signed long long)9241421688590303745LL,
		4620710844295151872LL, 2310355422147575808LL, 1155177711073755136LL, 577588855528488960LL, 288794425616760832LL,
		144396663052566528LL, 72057594037927936LL
	};

	long long KNIGHT_SPAN = 43234889994LL;
	long long KING_SPAN = 460039LL;

	int CASTLE_ROOKS[4] = { 0, 7, 56, 63 };
	long long CASTLE_LANES[4] = { 6LL, 112LL, 432345564227567616LL, 8070450532247928832LL };

	long long NOT_MY_PIECES;
	long long NOT_BLACK_PIECES;
	long long NOT_WHITE_PIECES;
	long long BLACK_PIECES;
	long long WHITE_PIECES;
	long long OCCUPIED;
	long long EMPTY;
	long long UNSAFE_FOR_BLACK;
	long long UNSAFE_FOR_WHITE;
	long long PINNED_PIECES;


	void possibleMovesW(Bitboard bb);
	void possibleMovesB(Bitboard bb);
	long long reverseBits(long long n);
	void drawBitboard(long long bb);
	long long makeMove(long long board, Move move, char type);


private:


	void p_PossibleMovesW(Bitboard bb);
	void p_PossibleMovesB(Bitboard bb);
	void p_PossiblePW(Bitboard bb, long long cMask, long long pMask, long long WP);
	void p_PossiblePB(Bitboard bb, long long cMask, long long pMask, long long BP);
	void p_PossibleN(Bitboard bb, long long cMask, long long pMask, long long N, Color side);
	void p_PossibleR(Bitboard bb, long long cMask, long long pMask, long long R, Color side);
	void p_PossibleB(Bitboard bb, long long cMask, long long pMask, long long B, Color side);
	void p_PossibleQ(Bitboard bb, long long cMask, long long pMask, long long Q, Color side);
	void p_PossibleK(long long UNSAFE, long long K);
	string possibleC(Bitboard bb, Color side);

	bool canKingSideCastle(Bitboard bb, Color side);
	bool canQueenSideCastle(Bitboard bb, Color side);

	long long isChecked(Bitboard bb, Color side);
	int countCheckers(long long checkers);
	long long genPushMask(Bitboard bb, int k, int checker);


	//Pinned functions
	long long findPinnedPieces(Bitboard bb, Color side);
	bool isPinned(int sqr, long long pinned);
	long long genPinMask(Bitboard bb, int sqr, Color side);
	string pinnedPawnMoves(Bitboard bb, long long pinnedP, long long cMask, long long pMask, Color side);

	//Returns piece attack bitboards
	//TODO:: add specific occupied parameter or make multiple in class
	long long AttacksWP(long long s);
	long long AttacksBP(long long s);
	long long AttacksN(long long s);
	long long AttacksB(long long s);
	long long AttacksR(long long s);
	long long AttacksQ(long long s);

	//Returns specific vector attack bitboards
	//Change occ depending if u want to include kings or not
	long long horAttacks(int s, long long occ);
	long long verAttacks(int s, long long occ);
	long long diagAttacks(int s, long long occ);
	long long antiAttacks(int s, long long occ);


	long long unsafeBlackBB(Bitboard bb);
	long long unsafeWhiteBB(Bitboard bb);
	long long p_HorVerMoves(int s);
	long long p_DiagAntiMoves(int s);

	//Returns true or false if a move is a capture
	bool isCapture(int sqr);





};