#include "Player.h"

Player::Player(bool isWhite) : white(isWhite) {

}

void Player::AddPiece(char type, int x, int y){
	static Piece* piece;
	

	switch (type)
	{
	case 'p':
		//piece = &Pawn(x, y, white);
		pieces.push_back(new Pawn(x, y, white));
		break;
	case 'b':
		//piece = &Bishop(x, y, white);
		pieces.push_back(new Bishop(x, y, white));
		break;
	case 'k':
		//piece = &Knight(x, y, white);
		pieces.push_back(new Knight(x, y, white));
		break;
	case 'r':
		//piece = &Rook(x, y, white);
		pieces.push_back(new Rook(x, y, white));
		break;
	case 'q':
		//piece = &Queen(x, y, white);
		pieces.push_back(new Queen(x, y, white));
		break;
	case 'K':
		//piece = &King(x, y, white);
		pieces.push_back(new King(x, y, white));
		break;
	default:
		break;
	}

	//pieces.push_back(piece);
	//Piece* temp = pieces.

	//std::cout << char(type) << ' ' << x << ' ' << y << std::endl;


	//pieces.push_back(piece);
	//pieces.push_back(new Pawn(1, 2, 0));
	//int x = 1, y = 2;
	//Pawn p(1, 2, true);
	//pieces.push_back(&p);
}

const std::vector<Piece*>* Player::GetPieces(){
	return &pieces;
}

const int Player::GetNumOfPieces() const{
	//Piece* temp;
	//for (int i = 0; i < pieces.size() - 1; ++i) {
	//	temp = pieces.at(i);
	//	std::cout << temp->GetSymbol() << 1 << temp->GetPos().x << temp->GetPos().y << std::endl;
	//}
	return pieces.size();
}

void Player::draw(sf::RenderWindow* w){
	for (auto iter : pieces) {
		iter->draw(w);
	}
}
