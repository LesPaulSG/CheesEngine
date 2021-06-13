#include "Player.h"

Player::Player(bool isWhite) : white(isWhite) {

}

void Player::AddPiece(char type, int x, int y, std::vector<std::vector<Piece*>>& board){
	static Piece* piece;
	
	switch (type)
	{
	case 'p':
		pieces.push_back(new Pawn(x, y, white, board));
		break;
	case 'b':
		pieces.push_back(new Bishop(x, y, white, board));
		break;
	case 'k':
		pieces.push_back(new Knight(x, y, white, board));
		break;
	case 'r':
		pieces.push_back(new Rook(x, y, white, board));
		break;
	case 'q':
		pieces.push_back(new Queen(x, y, white, board));
		break;
	case 'K':
		pieces.push_back(new King(x, y, white, board));
		break;
	//default:
	//	break;
	}
}

const std::vector<Piece*>* Player::GetPieces(){
	return &pieces;
}

const int Player::GetNumOfPieces() const{
	return pieces.size();
}

bool Player::isWhite(){
	return white;
}

void Player::DeletePiece(Piece* toDelete){
	int i = 0;
	for (auto iter : pieces) {
		if (iter == toDelete) {
			pieces.erase(pieces.begin()+i);
			break;
		}
		++i;
	}
}
