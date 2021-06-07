#include "Piece.h"

Piece::Piece(int x, int y, bool white) : pos(x, y), white(white), type(fType::DFLT) {
	
}

void Pawn::GenerateMoves(){

}

Pawn::Pawn(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::PAWN;
}

void Bishop::GenerateMoves(){

}

Bishop::Bishop(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::BSHP;
}

void Knight::GenerateMoves(){

}

Knight::Knight(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::KNHT;
}

void Rook::GenerateMoves(){

}

Rook::Rook(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::ROOK;
}

void Queen::GenerateMoves(){

}

Queen::Queen(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::QUEN;
}

void King::GenerateMoves(){

}

King::King(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::KING;
}
