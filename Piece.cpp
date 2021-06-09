#include "Piece.h"

Piece::Piece(int x, int y, bool white) : 
	pos(x, y), 
	white(white), 
	type(fType::DFLT) {
}

char Piece::GetSymbol(){
	return char(type);
}

sf::Vector2i Piece::GetPos(){
	return pos;
}

void Piece::draw(sf::RenderWindow* w){
	w->draw(body);
}

bool Piece::CanMoveHere(sf::Vector2i dest){
	for (auto iter : avaliableMoves) {
		if (iter == dest) {
			return true;
		}
	}
	return false;
}

const std::vector<sf::Vector2i>* Piece::GetAvaliableMoves(){
	return &avaliableMoves;
}

void Pawn::GenerateMoves(){

}

Pawn::Pawn(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::PAWN;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(1650, h, 260, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void Bishop::GenerateMoves(){

}

Bishop::Bishop(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::BSHP;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(660, h, 280, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void Knight::GenerateMoves(){

}

Knight::Knight(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::KNHT;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(990, h, 280, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void Rook::GenerateMoves(){

}

Rook::Rook(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::ROOK;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(1320, h, 260, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void Queen::GenerateMoves(){

}

Queen::Queen(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::QUEN;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(325, h, 300, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void King::GenerateMoves(){

}

King::King(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::KING;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(0, h, 260, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}
