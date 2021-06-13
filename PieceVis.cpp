#include "PieceVis.h"

PieceVis::PieceVis(Piece* p) : piecePtr(p) {
	int h = piecePtr->white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	
	switch (piecePtr->type)
	{
	case fType::PAWN:
		texture.loadFromFile("piecesTexture.png", sf::IntRect(1650, h, 260, 300));
		break;
	case fType::BSHP:
		texture.loadFromFile("piecesTexture.png", sf::IntRect(660, h, 280, 300));
		break;
	case fType::KNHT:
		texture.loadFromFile("piecesTexture.png", sf::IntRect(990, h, 280, 300));
		break;
	case fType::ROOK:
		texture.loadFromFile("piecesTexture.png", sf::IntRect(1320, h, 260, 300));
		break;
	case fType::QUEN:
		texture.loadFromFile("piecesTexture.png", sf::IntRect(325, h, 300, 300));
		break;
	case fType::KING:
		texture.loadFromFile("piecesTexture.png", sf::IntRect(0, h, 260, 300));
		break;
	}
	
	body.setTexture(texture);
	SpriteTransform(&body, piecePtr->pos.x, piecePtr->pos.y);
}

bool PieceVis::isSamePiece(Piece* p){
	return (p == piecePtr) ? true : false;
}

void PieceVis::Draw(sf::RenderWindow* w){
	w->draw(body);
}

sf::Sprite PieceVis::GetSprite(){
	return body;
}

void PieceVis::Update(){
	if (piecePtr != nullptr) {
		body.setPosition(piecePtr->pos.x * FIELD_SIZE, piecePtr->pos.y * FIELD_SIZE);
	}
}
