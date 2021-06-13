#pragma once

#include "Piece.h"

class PieceVis{
private:
	Piece* piecePtr;
	sf::Texture texture;
	sf::Sprite body;

public:
	PieceVis(Piece* p);
	bool isSamePiece(Piece* p);
	void Draw(sf::RenderWindow* w);
	sf::Sprite GetSprite();
	void Update();
};

