#include "Player.h"

Player::Player(bool isWhite) : white(isWhite) {

}

void Player::AddPiece(char type, int x, int y){
	static Piece* piece;
	
	switch (type)
	{
	case 'p':
		pieces.push_back(new Pawn(x, y, white));
		break;
	case 'b':
		pieces.push_back(new Bishop(x, y, white));
		break;
	case 'k':
		pieces.push_back(new Knight(x, y, white));
		break;
	case 'r':
		pieces.push_back(new Rook(x, y, white));
		break;
	case 'q':
		pieces.push_back(new Queen(x, y, white));
		break;
	case 'K':
		pieces.push_back(new King(x, y, white));
		break;
	default:
		break;
	}
}

const std::vector<Piece*>* Player::GetPieces(){
	return &pieces;
}

const int Player::GetNumOfPieces() const{
	return pieces.size();
}

void Player::draw(sf::RenderWindow* w){
	for (auto iter : pieces) iter->draw(w);
}

bool Player::isWhite(){
	return white;
}
