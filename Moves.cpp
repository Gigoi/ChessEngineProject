#include <iostream>
#include "Moves.h"

using namespace std;

//PUBLIC: FUNCTIONS
void Moves::possibleMovesW(Bitboard bb) {
	p_PossibleMovesW(bb);
}

void Moves::possibleMovesB(Bitboard bb) {
	p_PossibleMovesB(bb);
}

long long Moves::makeMove(long long board, Move move, char type) {
	int start = move.start;
	int dest = move.dest;


	if (move.t == QUIET && ((board >> start) & 1) == 1) {
		board &= ~(1LL << start);
		board |= (1LL << dest);
	}
	else if (move.t == CAPTURE) {
		if (((board >> start) & 1) == 1) {
			board |= (1LL << dest);
			board &= ~(1LL << start);
		}
		else {
			board &= ~(1LL << dest);
		}
	}
	else if (move.t == QPROMOTION)
	{
		board &= ~(1LL << dest);
		if (type == 'Q') {
			board |= (1LL << dest);
		}
		else {
			board &= ~(1LL << start);
		}
	}
	else if (move.t == RPROMOTION) {
		board &= ~(1LL << dest);
		if (type == 'R') {
			board |= (1LL << dest);
		}
		else {
			board &= ~(1LL << start);
		}
	}
	else if (move.t == BPROMOTION)
	{
		board &= ~(1LL << dest);
		if (type == 'B') {
			board |= (1LL << dest);
		}
		else {
			board &= ~(1LL << start);
		}
	}
	else if (move.t == NPROMOTION)
	{
		board &= ~(1LL << dest);
		if (type == 'N') {
			board |= (1LL << dest);
		}
		else {
			board &= ~(1LL << start);
		}
	}
	else if (move.t == qPROMOTION)
	{
		board &= ~(1LL << dest);
		if (type == 'q') {
			board |= (1LL << dest);
		}
		else {
			board &= ~(1LL << start);
		}
	}
	else if (move.t == rPROMOTION) {
		board &= ~(1LL << dest);
		if (type == 'r') {
			board |= (1LL << dest);
		}
		else {
			board &= ~(1LL << start);
		}
	}
	else if (move.t == bPROMOTION)
	{
		board &= ~(1LL << dest);
		if (type == 'b') {
			board |= (1LL << dest);
		}
		else {
			board &= ~(1LL << start);
		}
	}
	else if (move.t == nPROMOTION)
	{
		board &= ~(1LL << dest);
		if (type == 'n') {
			board |= (1LL << dest);
		}
		else {
			board &= ~(1LL << start);
		}
	}

	return board;
}



//PRIVATE: FUNCTIONS
void Moves::p_PossibleMovesW(Bitboard bb) {
	numMoves = 0;
	NOT_MY_PIECES = ~(bb.WP | bb.WN | bb.WB | bb.WR | bb.WQ | bb.WK | bb.BK);
	WHITE_PIECES = (bb.WP | bb.WN | bb.WB | bb.WR | bb.WQ);
	BLACK_PIECES = (bb.BP | bb.BN | bb.BB | bb.BR | bb.BQ);
	UNSAFE_FOR_WHITE = unsafeWhiteBB(bb);
	OCCUPIED = (bb.WP | bb.WN | bb.WB | bb.WR | bb.WQ | bb.WK | bb.BP | bb.BN | bb.BB | bb.BR | bb.BQ | bb.BK);
	EMPTY = ~(bb.WP | bb.WN | bb.WB | bb.WR | bb.WQ | bb.WK | bb.BP | bb.BN | bb.BB | bb.BR | bb.BQ | bb.BK);
	long long CHECKERS = isChecked(bb, WHITE);
	int num_Checkers = countCheckers(CHECKERS);
	long long capture_mask = 0xFFFFFFFFFFFFFFFF;
	long long push_mask = 0xFFFFFFFFFFFFFFFF;


	if (num_Checkers == 0) {
		//cout << "White is not in CHECK!!!!!" << endl;
	}
	else if (num_Checkers == 1) {
		//cout << "White is in ONE-CHECK!!!!" << endl;
		capture_mask = CHECKERS;
		push_mask = 0LL;

		if (bb.isSlider(CHECKERS)) {
			push_mask = genPushMask(bb, bb.getSqPos(bb.WK), bb.getSqPos(CHECKERS));
		}
		else {
			push_mask = 0LL;
		}
	}
	else if (num_Checkers == 2) {
		//cout << "WHITE is in DOUBLE-CHECK!" << endl;
		capture_mask = 0LL;
		push_mask = 0LL;
	}

	PINNED_PIECES = findPinnedPieces(bb, WHITE);

	p_PossiblePW(bb, capture_mask, push_mask, bb.WP);
	p_PossibleN(bb, capture_mask, push_mask, bb.WN, WHITE);
	p_PossibleR(bb, capture_mask, push_mask, bb.WR, WHITE);
	p_PossibleB(bb, capture_mask, push_mask, bb.WB, WHITE);
	p_PossibleQ(bb, capture_mask, push_mask, bb.WQ, WHITE);
	p_PossibleK(UNSAFE_FOR_WHITE, bb.WK);
	possibleC(bb, WHITE);
}

void Moves::p_PossibleMovesB(Bitboard bb) {
	numMoves = 0;
	NOT_MY_PIECES = ~(bb.BP | bb.BN | bb.BB | bb.BR | bb.BQ | bb.BK | bb.WK);
	WHITE_PIECES = (bb.WP | bb.WN | bb.WB | bb.WR | bb.WQ);
	BLACK_PIECES = (bb.BP | bb.BN | bb.BB | bb.BR | bb.BQ);
	UNSAFE_FOR_BLACK = unsafeBlackBB(bb);
	OCCUPIED = (bb.WP | bb.WN | bb.WB | bb.WR | bb.WQ | bb.WK | bb.BP | bb.BN | bb.BB | bb.BR | bb.BQ | bb.BK);
	EMPTY = ~(bb.WP | bb.WN | bb.WB | bb.WR | bb.WQ | bb.WK | bb.BP | bb.BN | bb.BB | bb.BR | bb.BQ | bb.BK);
	long long CHECKERS = isChecked(bb, BLACK);
	int num_Checkers = countCheckers(CHECKERS);
	long long capture_mask = 0xFFFFFFFFFFFFFFFF;
	long long push_mask = 0xFFFFFFFFFFFFFFFF;

	if (num_Checkers == 0) {
		//cout << "Black is not in CHECK!!!!!" << endl;
	}
	else if (num_Checkers == 1) {
		//cout << "Black is in ONE-CHECK!!!!" << endl;
		capture_mask = CHECKERS;
		push_mask = 0LL;
		if (bb.isSlider(CHECKERS)) {
			push_mask = genPushMask(bb, bb.getSqPos(bb.BK), bb.getSqPos(CHECKERS));
		}
		else {
			push_mask = 0LL;
		}
	}
	else if (num_Checkers == 2) {
		//cout << "Black is in DOUBLE-CHECK!" << endl;
		capture_mask = 0LL;
		push_mask = 0LL;
	}

	PINNED_PIECES = findPinnedPieces(bb, BLACK);

	p_PossiblePB(bb, capture_mask, push_mask, bb.BP);
	p_PossibleN(bb, capture_mask, push_mask, bb.BN, BLACK);
	p_PossibleR(bb, capture_mask, push_mask, bb.BR, BLACK);
	p_PossibleB(bb, capture_mask, push_mask, bb.BB, BLACK);
	p_PossibleQ(bb, capture_mask, push_mask, bb.BQ, BLACK);
	p_PossibleK(UNSAFE_FOR_BLACK, bb.BK);
	possibleC(bb, BLACK);
}

void Moves::p_PossiblePW(Bitboard bb, long long cMask, long long pMask, long long WP) {
	string list = "";
	Move tMove;

	long long PAWN_MOVES = ((WP & ~PINNED_PIECES) << 9) & BLACK_PIECES & ~(RANK_8) & ~(FILE_H) & (cMask | pMask); //Capture left
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" ").append(to_string(x2+1)).append(to_string(y2-1)).append("C").append(to_string(x2)).append(to_string(y2));

			tMove.start = i - 9;
			tMove.dest = i;
			tMove.t = CAPTURE;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}

	PAWN_MOVES = ((WP & ~PINNED_PIECES) << 7) & BLACK_PIECES & ~(RANK_8) & ~(FILE_A) & (cMask | pMask); //Capture right
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" ").append(to_string(x2 - 1)).append(to_string(y2 - 1)).append("C").append(to_string(x2)).append(to_string(y2));

			tMove.start = i - 7;
			tMove.dest = i;
			tMove.t = CAPTURE;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}

	PAWN_MOVES = ((WP & ~PINNED_PIECES) << 8) & EMPTY & ~(RANK_8) & (cMask | pMask); //Move one forward
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" ").append(to_string(x2)).append(to_string(y2 - 1)).append(to_string(x2)).append(to_string(y2));

			tMove.start = i - 8;
			tMove.dest = i;
			tMove.t = QUIET;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}

	PAWN_MOVES = ((WP & ~PINNED_PIECES) << 16) & EMPTY & (EMPTY << 8) & (RANK_4) & (cMask | pMask); //Move two forward
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" ").append(to_string(x2)).append(to_string(y2 - 2)).append(to_string(x2)).append(to_string(y2));

			tMove.start = i - 16;
			tMove.dest = i;
			tMove.t = QUIET;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}

	PAWN_MOVES = ((WP & ~PINNED_PIECES) << 9) & BLACK_PIECES & (RANK_8) & ~(FILE_H) & (cMask | pMask); //Capture left Promo
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" ").append(to_string(x2 + 1)).append(to_string(y2 - 1)).append("QP").append(to_string(x2)).append(to_string(y2));

			tMove.start = i - 9;
			tMove.dest = i;
			tMove.t = QPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i - 9;
			tMove.dest = i;
			tMove.t = RPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i - 9;
			tMove.dest = i;
			tMove.t = BPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i - 9;
			tMove.dest = i;
			tMove.t = NPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}
	PAWN_MOVES = ((WP & ~PINNED_PIECES) << 7) & BLACK_PIECES & (RANK_8) & ~(FILE_A) & (cMask | pMask); //Capture right Promo
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" ").append(to_string(x2 - 1)).append(to_string(y2 - 1)).append("QP").append(to_string(x2)).append(to_string(y2));

			tMove.start = i - 7;
			tMove.dest = i;
			tMove.t = QPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i - 7;
			tMove.dest = i;
			tMove.t = RPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i - 7;
			tMove.dest = i;
			tMove.t = BPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i - 7;
			tMove.dest = i;
			tMove.t = NPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}
	PAWN_MOVES = ((WP & ~PINNED_PIECES) << 8) & EMPTY & (RANK_8) & (cMask | pMask); //move forward Promo
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" ").append(to_string(x2)).append(to_string(y2 - 1)).append("QP").append(to_string(x2)).append(to_string(y2));

			tMove.start = i - 8;
			tMove.dest = i;
			tMove.t = QPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i - 8;
			tMove.dest = i;
			tMove.t = RPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i - 8;
			tMove.dest = i;
			tMove.t = BPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i - 8;
			tMove.dest = i;
			tMove.t = NPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

		}
	}

	//Generate Pinned Pawn Moves seperately
	if ((WP & PINNED_PIECES) != 0) {
		long long pinnedWP = (WP & PINNED_PIECES);

		pinnedPawnMoves(bb, pinnedWP, cMask, pMask, WHITE);
	}

}

void Moves::p_PossiblePB(Bitboard bb, long long cMask, long long pMask, long long BP) {
	Move tMove;

	long long PAWN_MOVES = ((BP & ~PINNED_PIECES) >> 9) & WHITE_PIECES & ~(RANK_1) & ~(FILE_A) & (cMask | pMask); //Capture left
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" C").append(to_string(x2 - 1)).append(to_string(y2 + 1)).append(to_string(x2)).append(to_string(y2));

			tMove.start = i + 9;
			tMove.dest = i;
			tMove.t = CAPTURE;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}

	PAWN_MOVES = ((BP & ~PINNED_PIECES) >> 7) & WHITE_PIECES & ~(RANK_1) & ~(FILE_H) & (cMask | pMask); //Capture right
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" C").append(to_string(x2 + 1)).append(to_string(y2 + 1)).append(to_string(x2)).append(to_string(y2));

			tMove.start = i + 7;
			tMove.dest = i;
			tMove.t = CAPTURE;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}

	PAWN_MOVES = ((BP & ~PINNED_PIECES) >> 8) & EMPTY & ~(RANK_1) & (cMask | pMask); //Move one forward
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" ").append(to_string(x2)).append(to_string(y2 + 1)).append(to_string(x2)).append(to_string(y2));

			tMove.start = i + 8;
			tMove.dest = i;
			tMove.t = QUIET;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}

	PAWN_MOVES = ((BP & ~PINNED_PIECES) >> 16) & EMPTY & (EMPTY >> 8) & (RANK_5) & (cMask | pMask); //Move two forward
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" ").append(to_string(x2)).append(to_string(y2 + 2)).append(to_string(x2)).append(to_string(y2));

			tMove.start = i + 16;
			tMove.dest = i;
			tMove.t = QUIET;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}

	PAWN_MOVES = ((BP & ~PINNED_PIECES) >> 9) & WHITE_PIECES & (RANK_1) & ~(FILE_A) & (cMask | pMask); //Capture left Promo
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" ").append(to_string(x2 - 1)).append(to_string(y2 + 1)).append("QP").append(to_string(x2)).append(to_string(y2));

			tMove.start = i + 9;
			tMove.dest = i;
			tMove.t = qPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i + 9;
			tMove.dest = i;
			tMove.t = rPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i + 9;
			tMove.dest = i;
			tMove.t = bPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i + 9;
			tMove.dest = i;
			tMove.t = nPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}
	PAWN_MOVES = ((BP & ~PINNED_PIECES) >> 7) & WHITE_PIECES & (RANK_1) & ~(FILE_H) & (cMask | pMask); //Capture right Promo
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" ").append(to_string(x2 + 1)).append(to_string(y2 + 1)).append("QP").append(to_string(x2)).append(to_string(y2));

			tMove.start = i + 7;
			tMove.dest = i;
			tMove.t = qPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i + 7;
			tMove.dest = i;
			tMove.t = rPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i + 7;
			tMove.dest = i;
			tMove.t = bPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i + 7;
			tMove.dest = i;
			tMove.t = nPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}
	PAWN_MOVES = ((BP & ~PINNED_PIECES) >> 8) & EMPTY & (RANK_1) & (cMask | pMask); //move forward Promo
	for (int i = 0; i < 64; i++)
	{
		if (((PAWN_MOVES >> i) & 1) == 1) {
			int x2 = (8 - (i % 8)); int y2 = ((i / 8) + 1);
			//list.append(" ").append(to_string(x2)).append(to_string(y2 + 1)).append("QP").append(to_string(x2)).append(to_string(y2));

			tMove.start = i + 16;
			tMove.dest = i;
			tMove.t = qPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i + 16;
			tMove.dest = i;
			tMove.t = rPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i + 16;
			tMove.dest = i;
			tMove.t = bPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;

			tMove.start = i + 16;
			tMove.dest = i;
			tMove.t = nPROMOTION;
			moveList[numMoves] = tMove;
			numMoves++;
		}
	}

	//Generate Pinned Pawn Moves seperately
	if ((BP & PINNED_PIECES) != 0) {
		long long pinnedBP = (BP & PINNED_PIECES);

	}

}

void Moves::p_PossibleN(Bitboard bb, long long cMask, long long pMask, long long N, Color side) {
	//TODO:: Write helper function that allow for quicker search of ROOKS (LOOK at logic chess vid)
	Move tMove;
	long long KNIGHT_MOVES;
	long long PIN_MASK = 0xFFFFFFFFFFFFFFFF;

	for (int i = 0; i < 64; i++)
	{
		if (((N >> i) & 1) == 1) {
			if (i > 18) {
				KNIGHT_MOVES = KNIGHT_SPAN << (i - 18);
			}
			else {
				KNIGHT_MOVES = KNIGHT_SPAN >> (18 - i);
			}
			if (i % 8 < 4) {
				KNIGHT_MOVES &= ~FILE_AB & NOT_MY_PIECES;
			}
			else {
				KNIGHT_MOVES &= ~FILE_GH & NOT_MY_PIECES;
			}
			//drawBitboard(KNIGHT_MOVES);
			KNIGHT_MOVES &= (cMask | pMask);
			if (isPinned(i, PINNED_PIECES)) {
				KNIGHT_MOVES &= genPinMask(bb, i, side);
			}
			for (int j = 0; j < 64; j++)
			{
				if (((KNIGHT_MOVES >> j) & 1) == 1) {
					//int x2 = (8 - (j % 8)); int y2 = ((j / 8) + 1);
					//int x1 = (8 - (i % 8)); int y1 = ((i / 8) + 1);
					//list.append(" N").append(to_string(x1)).append(to_string(y1)).append(to_string(x2)).append(to_string(y2));

					tMove.start = i;
					tMove.dest = j;
					if (isCapture(j)) {
						tMove.t = CAPTURE;
					}
					else {
						tMove.t = QUIET;
					}
					moveList[numMoves] = tMove;
					numMoves++;
				}
			}
		}
	}
}

void Moves::p_PossibleR(Bitboard bb, long long cMask, long long pMask, long long R, Color side) {
	//TODO:: Write helper function that allow for quicker search of ROOKS (LOOK at logic chess vid)
	Move tMove;
	long long ROOK_MOVES;

	for (int i = 0; i < 64; i++)
	{
		if (((R >> i) & 1) == 1) {
			ROOK_MOVES = p_HorVerMoves(i) & NOT_MY_PIECES & (cMask | pMask);
			if (isPinned(i, PINNED_PIECES)) {
				ROOK_MOVES &= genPinMask(bb, i, side);
			}

			//cout << "Rook BB" << endl;
			//drawBitboard(ROOK_MOVES);
			for (int j = 0; j < 64; j++)
			{
				if (((ROOK_MOVES >> j) & 1) == 1) {
					//int x2 = (8 - (j % 8)); int y2 = ((j / 8) + 1);
					//int x1 = (8 - (i % 8)); int y1 = ((i / 8) + 1);
					//list.append(" R").append(to_string(x1)).append(to_string(y1)).append(to_string(x2)).append(to_string(y2));

					tMove.start = i;
					tMove.dest = j;
					if (isCapture(j)) {
						tMove.t = CAPTURE;
					}
					else {
						tMove.t = QUIET;
					}
					moveList[numMoves] = tMove;
					numMoves++;
				}
			}
		}
	}
}

void Moves::p_PossibleB(Bitboard bb, long long cMask, long long pMask, long long B, Color side) {
	//TODO:: Write helper function that allow for quicker search of ROOKS (LOOK at logic chess vid)
	Move tMove;
	long long BISHOP_MOVES;

	for (int i = 0; i < 64; i++)
	{
		if (((B >> i) & 1) == 1) {
			BISHOP_MOVES = p_DiagAntiMoves(i) & NOT_MY_PIECES & (cMask | pMask);
			if (isPinned(i, PINNED_PIECES)) {
				BISHOP_MOVES &= genPinMask(bb, i, side);
			}
			//cout << "Bishop Moves" << endl;
			//drawBitboard(BISHOP_MOVES);
			for (int j = 0; j < 64; j++)
			{
				if (((BISHOP_MOVES >> j) & 1) == 1) {
					//int x2 = (8 - (j % 8)); int y2 = ((j / 8) + 1);
					//int x1 = (8 - (i % 8)); int y1 = ((i / 8) + 1);
					//list.append(" B").append(to_string(x1)).append(to_string(y1)).append(to_string(x2)).append(to_string(y2));

					tMove.start = i;
					tMove.dest = j;
					if (isCapture(j)) {
						tMove.t = CAPTURE;
					}
					else {
						tMove.t = QUIET;
					}
					moveList[numMoves] = tMove;
					numMoves++;
				}
			}
		}
	}
}

void Moves::p_PossibleQ(Bitboard bb, long long cMask, long long pMask, long long Q, Color side) {
	//TODO:: Write helper function that allow for quicker search of ROOKS (LOOK at logic chess vid)
	Move tMove;
	long long QUEEN_MOVES;

	for (int i = 0; i < 64; i++)
	{
		if (((Q >> i) & 1) == 1) {
			QUEEN_MOVES = (p_HorVerMoves(i) | p_DiagAntiMoves(i)) & NOT_MY_PIECES & (cMask | pMask);
			if (isPinned(i, PINNED_PIECES)) {
				QUEEN_MOVES &= genPinMask(bb, i, side);
			}
			//cout << "Queen bb" << endl;
			//drawBitboard(QUEEN_MOVES);
			for (int j = 0; j < 64; j++)
			{
				if (((QUEEN_MOVES >> j) & 1) == 1) {
					//int x2 = (8 - (j % 8)); int y2 = ((j / 8) + 1);
					//int x1 = (8 - (i % 8)); int y1 = ((i / 8) + 1);
					//list.append(" Q").append(to_string(x1)).append(to_string(y1)).append(to_string(x2)).append(to_string(y2));

					tMove.start = i;
					tMove.dest = j;
					if (isCapture(j)) {
						tMove.t = CAPTURE;
					}
					else {
						tMove.t = QUIET;
					}
					moveList[numMoves] = tMove;
					numMoves++;
				}
			}
		}
	}
}

void Moves::p_PossibleK(long long UNSAFE, long long K) {
	//TODO:: Write helper function that allow for quicker search of ROOKS (LOOK at logic chess vid)
	Move tMove;
	long long KING_MOVES;

	for (int i = 0; i < 64; i++)
	{
		if (((K >> i) & 1) == 1) {
			if (i > 9) {
				KING_MOVES = KING_SPAN << (i - 9);
			}
			else {
				KING_MOVES = KING_SPAN >> (9 - i);
			}
			if (i % 8 < 4) {
				KING_MOVES &= ~FILE_AB & NOT_MY_PIECES;
			}
			else {
				KING_MOVES &= ~FILE_GH & NOT_MY_PIECES;
			}
			KING_MOVES &= ~UNSAFE;
			//cout << "King BB" << endl;
			//drawBitboard(KING_MOVES);
			for (int j = 0; j < 64; j++)
			{
				if (((KING_MOVES >> j) & 1) == 1) {
					//int x2 = (8 - (j % 8)); int y2 = ((j / 8) + 1);
					//int x1 = (8 - (i % 8)); int y1 = ((i / 8) + 1);
					//list.append(" K").append(to_string(x1)).append(to_string(y1)).append(to_string(x2)).append(to_string(y2));

					tMove.start = i;
					tMove.dest = j;
					if (isCapture(j)) {
						tMove.t = CAPTURE;
					}
					else {
						tMove.t = QUIET;
					}
					moveList[numMoves] = tMove;
					numMoves++;
				}
			}
		}
	}
}

string Moves::possibleC(Bitboard bb, Color side) {
	string ret = "";
	if (side == WHITE) {
		if (bb.WCR == false || isChecked(bb, side) != 0) {
			return ret;
		}
		else {
			if (canKingSideCastle(bb, WHITE)) {
				ret.append(" 0-0");
			}
			if (canQueenSideCastle(bb, WHITE)) {
				ret.append(" 0-0-0");
			}
			return ret;
		}
	}
	else
	{
		if (bb.BCR == false || isChecked(bb, side) != 0) {
			return ret;
		}
		else {
			if (canKingSideCastle(bb, BLACK)) {
				ret.append(" 0-0");
			}
			if (canQueenSideCastle(bb, BLACK)) {
				ret.append(" 0-0-0");
			}
			return ret;
		}
	}

}

long long Moves::AttacksWP(long long s) {
	long long PAWN_MOVES = (s << 9) & BLACK_PIECES & ~(RANK_8) & ~(FILE_H);
	PAWN_MOVES |= (s << 7) & BLACK_PIECES & ~(RANK_8) & ~(FILE_A);

	return PAWN_MOVES;
}

long long Moves::AttacksBP(long long s) {
	long long PAWN_MOVES = (s >> 9) & WHITE_PIECES & ~(RANK_1) & ~(FILE_A);
	PAWN_MOVES |= (s >> 7) & WHITE_PIECES & ~(RANK_1) & ~(FILE_H);

	return PAWN_MOVES;
}

long long Moves::AttacksN(long long s) {
	long long KNIGHT_MOVES = 0LL;

	for (int i = 0; i < 64; i++)
	{
		if (((s >> i) & 1) == 1) {
			if (i > 18) {
				KNIGHT_MOVES = KNIGHT_SPAN << (i - 18);
			}
			else {
				KNIGHT_MOVES = KNIGHT_SPAN >> (18 - i);
			}
			if (i % 8 < 4) {
				KNIGHT_MOVES &= ~FILE_AB;
			}
			else {
				KNIGHT_MOVES &= ~FILE_GH;
			}

		}
	}
	return KNIGHT_MOVES;
}

long long Moves::AttacksB(long long s) {
	long long BISHOP_MOVES = 0LL;

	for (int i = 0; i < 64; i++)
	{
		if (((s >> i) & 1) == 1) {
			BISHOP_MOVES = p_DiagAntiMoves(i);
		}
	}
	return BISHOP_MOVES;
}

long long Moves::AttacksR(long long s) {
	long long ROOK_MOVES = 0LL;

	for (int i = 0; i < 64; i++)
	{
		if (((s >> i) & 1) == 1) {
			ROOK_MOVES = p_HorVerMoves(i);

		}
	}
	return ROOK_MOVES;
}

long long Moves::AttacksQ(long long s) {
	long long QUEEN_MOVES = 0LL;

	for (int i = 0; i < 64; i++)
	{
		if (((s >> i) & 1) == 1) {
			QUEEN_MOVES = (p_HorVerMoves(i) | p_DiagAntiMoves(i));
		}
	}
	return QUEEN_MOVES;
}

long long Moves::horAttacks(int s, long long occ) {
	long long bSquare = 1LL << s;
	int rankIndex = s / 8;

	long long possibleHorizontal = (occ - 2 * bSquare) ^ (reverseBits(reverseBits(occ) - (2 * reverseBits(bSquare))));

	return (possibleHorizontal & RankMasks8[rankIndex]);
}

long long Moves::verAttacks(int s, long long occ) {
	long long bSquare = 1LL << s;
	int fileIndex = (8 - (s % 8)) - 1;


	long long possibleVertical = ((occ & FileMask8[fileIndex]) - (2 * bSquare)) ^ (reverseBits(reverseBits(occ & FileMask8[fileIndex]) - (2 * reverseBits(bSquare))));
	return (possibleVertical & FileMask8[fileIndex]);
}

long long Moves::diagAttacks(int s, long long occ) {
	long long bSquare = 1LL << s;
	int diagnalIndex = (s / 8) + (s % 8);

	long long possibleDiagnal = ((occ & DiagnalMask[diagnalIndex]) - 2 * bSquare) ^ (reverseBits(reverseBits(occ & DiagnalMask[diagnalIndex]) - (2 * reverseBits(bSquare))));

	return (possibleDiagnal & DiagnalMask[diagnalIndex]);
}

long long Moves::antiAttacks(int s, long long occ) {
	long long bSquare = 1LL << s;
	int antiDiagnalIndex = (s / 8) + 7 - (s % 8);

	long long possibleAntiDiagnal = ((occ & AntiDiagnalMask[antiDiagnalIndex]) - (2 * bSquare)) ^ (reverseBits(reverseBits(occ & AntiDiagnalMask[antiDiagnalIndex]) - (2 * reverseBits(bSquare))));

	return (possibleAntiDiagnal & AntiDiagnalMask[antiDiagnalIndex]);
}

long long Moves::isChecked(Bitboard bb, Color side) {
	long long checkers = 0LL;
	long long k;
	long long p, n, b, r, q;
	if (side == WHITE) {
		k = bb.WK; p = bb.BP; n = bb.BN; b = bb.BB; r = bb.BR; q = bb.BQ;
		checkers |= AttacksWP(k) & p;
	}
	else {
		k = bb.BK; p = bb.WP; n = bb.WN; b = bb.WB; r = bb.WR; q = bb.WQ;
		checkers |= AttacksBP(k) & p;
	}

	checkers |= (AttacksN(k) & NOT_MY_PIECES) & n;
	checkers |= (AttacksB(k) & NOT_MY_PIECES) & b;
	checkers |= (AttacksR(k) & NOT_MY_PIECES) & r;
	checkers |= (AttacksQ(k) & NOT_MY_PIECES) & q;



	return checkers;
}

int Moves::countCheckers(long long checkers) {
	int n = 0;
	for (int i = 0; i < 64; i++)
	{
		if (((checkers >> i) & 1) == 1) {
			n++;
		}
	}
	return n;
}

long long Moves::genPushMask(Bitboard bb, int k, int checker) {
	long long occ = (bb.WP | bb.WN | bb.WB | bb.WR | bb.WQ | bb.BP | bb.BN | bb.BB | bb.BR | bb.BQ | bb.WK | bb.BK);
	if ((horAttacks(k, occ) & horAttacks(checker, occ)) != 0) {
		return horAttacks(k, occ) & horAttacks(checker, occ);
	}
	else if ((verAttacks(k, occ) & verAttacks(checker, occ)) != 0)
	{
		return verAttacks(k, occ) & verAttacks(checker, occ);
	}
	else if ((diagAttacks(k, occ) & diagAttacks(checker, occ)) != 0)
	{
		return diagAttacks(k, occ) & diagAttacks(checker, occ);
	}
	else if ((antiAttacks(k, occ) & antiAttacks(checker, occ)) != 0)
	{
		return antiAttacks(k, occ) & antiAttacks(checker, occ);
	}
	else {
		cout << "WARNING: COULD NOT GENERATE PUSH MASK!" << endl;
		return 0LL;
	}
}

long long Moves::unsafeBlackBB(Bitboard bb) {
	long long unsafe = 0LL;
	long long MOVES;
	OCCUPIED = (bb.WP | bb.WN | bb.WB | bb.WR | bb.WQ | bb.BP | bb.BN | bb.BB | bb.BR | bb.BQ);

	//PAWN//
	unsafe = ((bb.WP << 7) & ~FILE_A);
	unsafe |= ((bb.WP << 9) & ~FILE_H);

	//KNIGHT//
	for (int i = 0; i < 64; i++)
	{
		if (((bb.WN >> i) & 1) == 1) {
			if (i > 18) {
				MOVES = KNIGHT_SPAN << (i - 18);
			}
			else {
				MOVES = KNIGHT_SPAN >> (18 - i);
			}
			if (i % 8 < 4) {
				MOVES &= ~FILE_AB & NOT_MY_PIECES;
			}
			else {
				MOVES &= ~FILE_GH & NOT_MY_PIECES;
			}
			unsafe |= MOVES;
		}
	}

	//QUEEEN&BISHOP//
	long long QB = bb.WQ | bb.WB;
	for (int i = 0; i < 64; i++)
	{
		if (((QB >> i) & 1) == 1) {
			MOVES = p_DiagAntiMoves(i) & NOT_MY_PIECES;
			unsafe |= MOVES;
		}
	}

	//QUEEN&ROOK//
	long long QR = bb.WQ | bb.WR;
	for (int i = 0; i < 64; i++)
	{
		if (((QR >> i) & 1) == 1) {
			MOVES = p_HorVerMoves(i) & NOT_MY_PIECES;
			//cout << "WHITE Q R attacks" << endl;
			//drawBitboard(MOVES);
			;			unsafe |= MOVES;
		}
	}
	//KING//
	for (int i = 0; i < 64; i++)
	{
		if (((bb.WK >> i) & 1) == 1) {
			if (i > 9) {
				MOVES = KING_SPAN << (i - 9);
			}
			else {
				MOVES = KING_SPAN >> (9 - i);
			}
			if (i % 8 < 4) {
				MOVES &= ~FILE_AB & NOT_MY_PIECES;
			}
			else {
				MOVES &= ~FILE_GH & NOT_MY_PIECES;
			}
			unsafe |= MOVES;
		}
	}
	//cout << "Unsafe Black BB" << endl;
	//drawBitboard(unsafe);
	return unsafe;
}

long long Moves::unsafeWhiteBB(Bitboard bb) {
	long long unsafe = 0LL;
	long long MOVES;
	OCCUPIED = (bb.WP | bb.WN | bb.WB | bb.WR | bb.WQ | bb.BP | bb.BN | bb.BB | bb.BR | bb.BQ);

	//PAWN//
	unsafe = ((bb.BP >> 9) & ~FILE_A);
	unsafe |= ((bb.BP >> 7) & ~FILE_H);

	//KNIGHT//
	for (int i = 0; i < 64; i++)
	{
		if (((bb.BN >> i) & 1) == 1) {
			if (i > 18) {
				MOVES = KNIGHT_SPAN << (i - 18);
			}
			else {
				MOVES = KNIGHT_SPAN >> (18 - i);
			}
			if (i % 8 < 4) {
				MOVES &= ~FILE_AB & NOT_MY_PIECES;
			}
			else {
				MOVES &= ~FILE_GH & NOT_MY_PIECES;
			}
			unsafe |= MOVES;
		}
	}

	//QUEEEN&BISHOP//
	long long QB = bb.BQ | bb.BB;
	for (int i = 0; i < 64; i++)
	{
		if (((QB >> i) & 1) == 1) {
			MOVES = p_DiagAntiMoves(i) & NOT_MY_PIECES;
			unsafe |= MOVES;
		}
	}

	//QUEEN&ROOK//
	long long QR = bb.BQ | bb.BR;
	for (int i = 0; i < 64; i++)
	{
		if (((QR >> i) & 1) == 1) {
			MOVES = p_HorVerMoves(i) & NOT_MY_PIECES;
			//cout << "BLACK QUEEN ROOK ATTACKS" << endl;
			//drawBitboard(MOVES);
			unsafe |= MOVES;
		}
	}
	//KING//
	for (int i = 0; i < 64; i++)
	{
		if (((bb.BK >> i) & 1) == 1) {
			if (i > 9) {
				MOVES = KING_SPAN << (i - 9);
			}
			else {
				MOVES = KING_SPAN >> (9 - i);
			}
			if (i % 8 < 4) {
				MOVES &= ~FILE_AB & NOT_MY_PIECES;
			}
			else {
				MOVES &= ~FILE_GH & NOT_MY_PIECES;
			}
			unsafe |= MOVES;
		}
	}
	//cout << "--UNSAFE WHITE BB--" << endl;
	//drawBitboard(unsafe);
	return unsafe;
}

long long Moves::findPinnedPieces(Bitboard bb, Color side) {
	long long occ = (bb.WP | bb.WN | bb.WB | bb.WR | bb.WQ | bb.BP | bb.BN | bb.BB | bb.BR | bb.BQ | bb.WK | bb.BK);
	long long pin = 0LL;
	long long NOT_OPP_PIECES;

	long long k;
	long long p, n, b, r, q;
	if (side == WHITE) {
		k = bb.WK; p = bb.BP; n = bb.BN; b = bb.BB; r = bb.BR; q = bb.BQ;
		NOT_OPP_PIECES = ~(BLACK_PIECES);
	}
	else {
		k = bb.BK; p = bb.WP; n = bb.WN; b = bb.WB; r = bb.WR; q = bb.WQ;
		NOT_OPP_PIECES = ~(WHITE_PIECES);
	}

	//BISHOP n QUEEN
	long long QB = q | b;
	for (int i = 0; i < 64; i++)
	{
		if (((QB >> i) & 1) == 1) {
			pin |= diagAttacks(bb.getSqPos(k), occ) & (diagAttacks(i, occ) & NOT_OPP_PIECES);
			pin |= antiAttacks(bb.getSqPos(k), occ) & (antiAttacks(i, occ) & NOT_OPP_PIECES);
		}
	}

	//ROOK n QUEEN
	long long QR = q | r;
	for (int i = 0; i < 64; i++)
	{
		if (((QR >> i) & 1) == 1) {
			pin |= horAttacks(bb.getSqPos(k), occ) & (horAttacks(i, occ) & NOT_OPP_PIECES);
			pin |= verAttacks(bb.getSqPos(k), occ) & (verAttacks(i, occ) & NOT_OPP_PIECES);
		}
	}

	pin &= ~EMPTY;
	return pin;
}

bool Moves::isPinned(int sqr, long long pinned) {
	if (((pinned >> sqr) & 1) == 1) {
		return true;
	}
	else {
		return false;
	}
}

long long Moves::genPinMask(Bitboard bb, int sqr, Color side) {
	long long occ = (bb.WP | bb.WN | bb.WB | bb.WR | bb.WQ | bb.BP | bb.BN | bb.BB | bb.BR | bb.BQ | bb.WK | bb.BK);
	long long k;
	if (side == WHITE) {
		k = bb.WK;
	}
	else
	{
		k = bb.BK;
	}


	if ((k & horAttacks(sqr, occ)) != 0) {
		return horAttacks(sqr, occ) & NOT_MY_PIECES;
	}
	else if ((k & verAttacks(sqr, occ)) != 0)
	{
		return verAttacks(sqr, occ) & NOT_MY_PIECES;
	}
	else if ((k & diagAttacks(sqr, occ)) != 0)
	{
		return diagAttacks(sqr, occ) & NOT_MY_PIECES;
	}
	else if ((k & antiAttacks(sqr, occ)) != 0)
	{
		return antiAttacks(sqr, occ) & NOT_MY_PIECES;
	}
}

void Moves::pinnedPawnMoves(Bitboard bb, long long pinnedP, long long cMask, long long pMask, Color side) {
	long long PINNED_PAWN_MOVES = 0LL;
	Move tMove;
	if (side == WHITE) {
		for (int i = 0; i < 64; i++)
		{
			if (((pinnedP >> i) & 1) == 1) {
				long long curPawn = 1LL << i;
				long long pinMask = genPinMask(bb, i, WHITE);
				int x1 = (8 - (i % 8));
				int y1 = ((i / 8) + 1);

				PINNED_PAWN_MOVES = (curPawn << 9) & BLACK_PIECES & ~(RANK_8) & ~(FILE_H) & (cMask | pMask) & pinMask; //Capture left
				PINNED_PAWN_MOVES |= (curPawn << 7) & BLACK_PIECES & ~(RANK_8) & ~(FILE_A) & (cMask | pMask) & pinMask; //Capture right
				PINNED_PAWN_MOVES |= (curPawn << 8) & EMPTY & ~(RANK_8) & (cMask | pMask) & pinMask;					//Move one forward
				PINNED_PAWN_MOVES |= (curPawn << 16) & EMPTY & (EMPTY << 8) & (RANK_4) & (cMask | pMask) & pinMask;		//Move two forward
				PINNED_PAWN_MOVES |= (curPawn << 9) & BLACK_PIECES & (RANK_8) & ~(FILE_H) & (cMask | pMask) & pinMask;	//Capture left Promo
				PINNED_PAWN_MOVES |= (curPawn << 7) & BLACK_PIECES & (RANK_8) & ~(FILE_A) & (cMask | pMask) & pinMask;	//Capture right Promo
				PINNED_PAWN_MOVES |= (curPawn << 8) & EMPTY & (RANK_8) & (cMask | pMask) & pinMask;						//move forward Promo

				int x2, y2;
				for (int j = 0; j < 64; j++) {
					if (((PINNED_PAWN_MOVES >> j) & 1) == 1) {
						x2 = (8 - (j % 8));
						y2 = ((j / 8) + 1);

						tMove.start = i;
						tMove.dest = j;
						//Found pinned-pawn promotion
						if (((1LL << j) & (RANK_8)) == 1) {
							tMove.t = QPROMOTION;
							moveList[numMoves] = tMove;
							numMoves++;

							tMove.t = NPROMOTION;
							moveList[numMoves] = tMove;
							numMoves++;

							tMove.t = BPROMOTION;
							moveList[numMoves] = tMove;
							numMoves++;

							tMove.t = RPROMOTION;
							moveList[numMoves] = tMove;
							numMoves++;
						}
						else if (isCapture(j)) {
							tMove.t = CAPTURE;
							moveList[numMoves] = tMove;
							numMoves++;
						}
						else {
							tMove.t = QUIET;
							moveList[numMoves] = tMove;
							numMoves++;
						}
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < 64; i++)
		{
			if (((pinnedP >> i) & 1) == 1) {
				long long curPawn = 1LL << i;
				long long pinMask = genPinMask(bb, i, BLACK);
				int x1 = (8 - (i % 8));
				int y1 = ((i / 8) + 1);

				PINNED_PAWN_MOVES = (curPawn >> 9) & WHITE_PIECES & ~(RANK_1) & ~(FILE_A) & (cMask | pMask) & pinMask; //Capture left
				PINNED_PAWN_MOVES |= (curPawn >> 7) & WHITE_PIECES & ~(RANK_1) & ~(FILE_H) & (cMask | pMask) & pinMask; //Capture right
				PINNED_PAWN_MOVES |= (curPawn >> 8) & EMPTY & ~(RANK_1) & (cMask | pMask) & pinMask;					//Move one forward
				PINNED_PAWN_MOVES |= (curPawn >> 16) & EMPTY & (EMPTY >> 8) & (RANK_5) & (cMask | pMask) & pinMask;		//Move two forward
				PINNED_PAWN_MOVES |= (curPawn >> 9) & WHITE_PIECES & (RANK_1) & ~(FILE_A) & (cMask | pMask) & pinMask;	//Capture left Promo
				PINNED_PAWN_MOVES |= (curPawn >> 7) & WHITE_PIECES & (RANK_1) & ~(FILE_H) & (cMask | pMask) & pinMask;	//Capture right Promo
				PINNED_PAWN_MOVES |= (curPawn >> 8) & EMPTY & (RANK_1) & (cMask | pMask) & pinMask;						//move forward Promo

				int x2, y2;
				for (int j = 0; j < 64; j++) {
					if (((PINNED_PAWN_MOVES >> j) & 1) == 1) {
						x2 = (8 - (j % 8));
						y2 = ((j / 8) + 1);

						tMove.start = i;
						tMove.dest = j;
						//Found pinned-pawn promotion
						if (((1LL << j) & (RANK_8)) == 1) {
							tMove.t = qPROMOTION;
							moveList[numMoves] = tMove;
							numMoves++;

							tMove.t = nPROMOTION;
							moveList[numMoves] = tMove;
							numMoves++;

							tMove.t = bPROMOTION;
							moveList[numMoves] = tMove;
							numMoves++;

							tMove.t = rPROMOTION;
							moveList[numMoves] = tMove;
							numMoves++;
						}
						else if (isCapture(j)) {
							tMove.t = CAPTURE;
							moveList[numMoves] = tMove;
							numMoves++;
						}
						else {
							tMove.t = QUIET;
							moveList[numMoves] = tMove;
							numMoves++;
						}
					}
				}
			}
		}
	}
}

long long Moves::p_HorVerMoves(int s) {
	long long bSquare = 1LL << s;
	int fileIndex = (8 - (s % 8)) - 1;
	int rankIndex = s / 8;

	long long possibleHorizontal = (OCCUPIED - 2 * bSquare) ^ (reverseBits(reverseBits(OCCUPIED) - (2 * reverseBits(bSquare))));
	long long possibleVertical = ((OCCUPIED & FileMask8[fileIndex]) - (2 * bSquare)) ^ (reverseBits(reverseBits(OCCUPIED & FileMask8[fileIndex]) - (2 * reverseBits(bSquare))));

	return (possibleHorizontal & RankMasks8[rankIndex]) | (possibleVertical & FileMask8[fileIndex]);
}

long long Moves::p_DiagAntiMoves(int s) {
	long long bSquare = 1LL << s;
	int diagnalIndex = (s / 8) + (s % 8);
	int antiDiagnalIndex = (s / 8) + 7 - (s % 8);

	long long possibleDiagnal = ((OCCUPIED & DiagnalMask[diagnalIndex]) - 2 * bSquare) ^ (reverseBits(reverseBits(OCCUPIED & DiagnalMask[diagnalIndex]) - (2 * reverseBits(bSquare))));
	long long possibleAntiDiagnal = ((OCCUPIED & AntiDiagnalMask[antiDiagnalIndex]) - (2 * bSquare)) ^ (reverseBits(reverseBits(OCCUPIED & AntiDiagnalMask[antiDiagnalIndex]) - (2 * reverseBits(bSquare))));

	return (possibleDiagnal & DiagnalMask[diagnalIndex]) | (possibleAntiDiagnal & AntiDiagnalMask[antiDiagnalIndex]);
}

bool Moves::canKingSideCastle(Bitboard bb, Color side) {
	if (side == WHITE) {
		if (((1LL << CASTLE_ROOKS[0]) & bb.WR) != 0 && (CASTLE_LANES[0] & EMPTY & ~(UNSAFE_FOR_WHITE)) == CASTLE_LANES[0]) {
			return true;
		}
		else {
			return false;
		}
	}
	else
	{
		if (((1LL << CASTLE_ROOKS[2]) & bb.BR) != 0 && (CASTLE_LANES[2] & EMPTY & ~(UNSAFE_FOR_BLACK)) == CASTLE_LANES[2]) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool Moves::canQueenSideCastle(Bitboard bb, Color side) {
	if (side == WHITE) {
		if (((1LL << CASTLE_ROOKS[1]) & bb.WR) != 0 && (CASTLE_LANES[1] & EMPTY & ~(UNSAFE_FOR_WHITE)) == CASTLE_LANES[1]) {
			return true;
		}
		else {
			return false;
		}
	}
	else
	{
		if (((1LL << CASTLE_ROOKS[3]) & bb.BR) != 0 && (CASTLE_LANES[3] & EMPTY & ~(UNSAFE_FOR_BLACK)) == CASTLE_LANES[3]) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool Moves::isCapture(int sqr) {
	if (((OCCUPIED >> sqr) & 1) == 1) {
		return true;
	}
	else {
		return false;
	}
}

long long Moves::reverseBits(long long n) {

	long long  NO_OF_BITS = sizeof(n) * 8;
	long long reverse_num = 0;
	long long i;
	for (i = 0; i < NO_OF_BITS; i++)
	{
		if ((n & ((long long)1 << i)))
			reverse_num |= (long long)1 << ((NO_OF_BITS - 1) - i);
	}
	//cout << "Reversing: " << n << " TO - " << reverse_num << endl;
	return reverse_num;
}
void Moves::drawBitboard(long long bb) {
	char chessBoard[8][8];
	for (int i = 0; i < 64; i++)
	{
		chessBoard[i / 8][i % 8] = '.';
	}

	int j = 63;
	for (int i = 0; i < 64; i++)
	{
		if (((bb >> j) & 1) == 1) { chessBoard[i / 8][i % 8] = '1'; }
		j--;
	}

	cout << "----------" << endl;
	for (int i = 0; i < 8; i++) {
		cout << '|';
		for (int k = 0; k < 8; k++)
		{
			cout << chessBoard[i][k];
		}
		cout << '|' << endl;
	}
	cout << "----------" << endl;
}