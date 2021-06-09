#include "Piece.h"

Piece::Piece(int x, int y, bool white) : 
	pos(x, y), 
	white(white), 
	type(fType::DFLT) {
}

Piece::Piece(int x, int y, bool white, fType tp) :
	pos(x, y),
	white(white),
	type(tp) {

}

char Piece::GetSymbol(){
	return char(type);
}

sf::Vector2i Piece::GetPos(){
	return pos;
}

void Piece::draw(sf::RenderWindow* w){
	//std::cout << "qwe" << std::endl;
	//sf::Texture t;
	//t.loadFromFile("piecesTexture.png", sf::IntRect(1680, 0, 260, 300));
	//sf::Sprite s;

	//s.setTexture(t);
	//s.setPosition(pos.x*75, pos.y*75);
	//s.setColor(sf::Color::Blue);
	//s.setScale(0.27, 0.27);
	w->draw(body);
}

const std::vector<sf::Vector2i>* Piece::GetAvaliableMoves(){
	return &avaliableMoves;
}

void Pawn::GenerateMoves(){

}

Pawn::Pawn(int x, int y, bool white) : Piece(x, y, white, fType::PAWN) {
	//Piece::type = fType::PAWN;
	//body.setTexture(white ? pawnTextureW : pawnTextureB);
	int h = white ? 0 : 330;
	//sf::Texture tex;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(1650, h, 260, 300));
	body.setTexture(tex);
	//body.setColor(sf::Color::Blue);
	body.setPosition(x * 75, y * 75);
	body.setScale(0.27, 0.27);
}

void Bishop::GenerateMoves(){

}

Bishop::Bishop(int x, int y, bool white) : Piece(x, y, white, fType::BSHP) {
	//Piece::type = fType::BSHP;
	//body.setTexture(white ? bishopTextureW : bishopTextureB);
	int h = white ? 0 : 330;
	//sf::Texture tex;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(660, h, 280, 300));
	body.setPosition(x * 75, y * 75);
	body.setScale(0.27, 0.27);
	body.setTexture(tex);
}

void Knight::GenerateMoves(){

}

Knight::Knight(int x, int y, bool white) : Piece(x, y, white, fType::KNHT) {
	//Piece::type = fType::KNHT;
	//body.setTexture(white ? knightTextureW : knightTextureB);
	int h = white ? 0 : 330;
	//sf::Texture tex;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(990, h, 280, 300));
	body.setTexture(tex);
	body.setPosition(x * 75, y * 75);
	body.setScale(0.27, 0.27);
}

void Rook::GenerateMoves(){

}

Rook::Rook(int x, int y, bool white) : Piece(x, y, white, fType::ROOK) {
	//Piece::type = fType::ROOK;
	//body.setTexture(white ? rookTextureW : rookTextureB);
	int h = white ? 0 : 330;
	//sf::Texture tex;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(1320, h, 260, 300));
	body.setPosition(x * 75, y * 75);
	body.setScale(0.27, 0.27);
	body.setTexture(tex);
}

void Queen::GenerateMoves(){

}

Queen::Queen(int x, int y, bool white) : Piece(x, y, white, fType::QUEN) {
	//Piece::type = fType::QUEN;
	//body.setTexture(white ? queenTextureW : queenTextureB);
	int h = white ? 0 : 330;
	//sf::Texture tex;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(325, h, 300, 300));
	body.setTexture(tex);
	body.setPosition(x * 75, y * 75);
	body.setScale(0.27, 0.27);
}

void King::GenerateMoves(){

}

King::King(int x, int y, bool white) : Piece(x, y, white, fType::KING) {
	//Piece::type = fType::KING;
	//body.setTexture(white ? kingTextureW : kingTextureB);
	int h = white ? 0 : 330;
	//sf::Texture tex;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(0, h, 260, 300));
	body.setPosition((x * 75)+2, y * 75);
	body.setScale(0.27, 0.27);
	body.setTexture(tex);
}
