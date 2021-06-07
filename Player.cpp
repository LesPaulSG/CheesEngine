#include "Player.h"

Player::Player(bool isWhite) : white(isWhite) {

}

void Player::AddPiece(Piece* piece){
	pieces.push_back(piece);
	//pieces.push_back(std::move(Pawn(1, 2, 0)));
	int x = 1, y = 2;
	Pawn p();
}
