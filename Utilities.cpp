#include "Utilities.h"
#include <iostream>

void Utilities::perfTRoot(Bitboard bb, bool whiteToMove, int depth) {
	Moves m;
	bb.convertBitBoardToArr();
	if (whiteToMove) {
		m.possibleMovesW(bb);
		//cout << "Possible White Moves-" << moveString << endl;
		//cout << "MoveList size: " << m.numMoves << endl;
	}
	else {
		m.possibleMovesB(bb);
		//cout << "Possible Black Moves-" << moveString << endl;
		//cout << "MoveList size: " << m.numMoves << endl;
	}
	Bitboard tBoard;
	for (int i = 0; i < m.numMoves; i++)
	{
		//cout << m.moveList[i].start << "-" << m.moveList[i].dest << "-" << m.moveList[i].t << endl;
		tBoard.WP = m.makeMove(bb.WP, m.moveList[i], 'P');
		tBoard.WN = m.makeMove(bb.WN, m.moveList[i], 'N');
		tBoard.WB = m.makeMove(bb.WB, m.moveList[i], 'B');
		tBoard.WR = m.makeMove(bb.WR, m.moveList[i], 'R');
		tBoard.WQ = m.makeMove(bb.WQ, m.moveList[i], 'Q');
		tBoard.WK = m.makeMove(bb.WK, m.moveList[i], 'K');
		tBoard.BP = m.makeMove(bb.BP, m.moveList[i], 'p');
		tBoard.BN = m.makeMove(bb.BN, m.moveList[i], 'n');
		tBoard.BB = m.makeMove(bb.BB, m.moveList[i], 'b');
		tBoard.BR = m.makeMove(bb.BR, m.moveList[i], 'r');
		tBoard.BQ = m.makeMove(bb.BQ, m.moveList[i], 'q');
		tBoard.BK = m.makeMove(bb.BK, m.moveList[i], 'k');

		//tBoard.convertBitBoardToArr();
		perfT(tBoard, !whiteToMove, depth + 1);
		totalMoveCounter += moveCounter;
		moveCounter = 0;
	}
	cout << "Move Counter: " << totalMoveCounter << endl;
}

void Utilities::perfT(Bitboard bb, bool whiteToMove, int depth) {
	Moves m;
	if (depth < maxPerfTDepth)
	{

		if (whiteToMove) {
			m.possibleMovesW(bb);
			//ut << "Possible White Moves-" << moveString << endl;
			//ut << "MoveList size: " << m.numMoves << endl;
		}
		else {
			m.possibleMovesB(bb);
			//cout << "Possible Black Moves-" << moveString << endl;
			//cout << "MoveList size: " << m.numMoves << endl;
		}

		Bitboard tBoard;
		for (int i = 0; i < m.numMoves; i++)
		{
			//cout << m.moveList[i].start << "-" << m.moveList[i].dest << "-" << m.moveList[i].t << endl;
			tBoard.WP = m.makeMove(bb.WP, m.moveList[i], 'P');
			tBoard.WN = m.makeMove(bb.WN, m.moveList[i], 'N');
			tBoard.WB = m.makeMove(bb.WB, m.moveList[i], 'B');
			tBoard.WR = m.makeMove(bb.WR, m.moveList[i], 'R');
			tBoard.WQ = m.makeMove(bb.WQ, m.moveList[i], 'Q');
			tBoard.WK = m.makeMove(bb.WK, m.moveList[i], 'K');
			tBoard.BP = m.makeMove(bb.BP, m.moveList[i], 'p');
			tBoard.BN = m.makeMove(bb.BN, m.moveList[i], 'n');
			tBoard.BB = m.makeMove(bb.BB, m.moveList[i], 'b');
			tBoard.BR = m.makeMove(bb.BR, m.moveList[i], 'r');
			tBoard.BQ = m.makeMove(bb.BQ, m.moveList[i], 'q');
			tBoard.BK = m.makeMove(bb.BK, m.moveList[i], 'k');

			//tBoard.convertBitBoardToArr();
			if (depth + 1 == maxPerfTDepth) {
				moveCounter++;

			}
			perfT(tBoard, !whiteToMove, depth + 1);
		}
	}

}