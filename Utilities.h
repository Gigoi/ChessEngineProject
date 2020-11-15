#pragma once
#include "Bitboard.h"
#include "Moves.h"

class Utilities
{
public:
	//Moves m;
	int maxPerfTDepth = 5;
	int totalMoveCounter = 0;
	int moveCounter = 0;
	void perfTRoot(Bitboard bb, bool whiteToMove, int depth);
	void perfT(Bitboard bb, bool whiteToMove, int depth);

private:
};

