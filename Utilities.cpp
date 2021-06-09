#include "Utilities.h"

void PreLoad(){
	if (pawnTextureW.loadFromFile("piecesTexture.png", sf::IntRect(1680, 0, 260, 300))) {
		std::cout << "fuck you";
	}
	bishopTextureW.loadFromFile("piecesTexture.png",	sf::IntRect(650,	0,	 260, 300));
	knightTextureW.loadFromFile("piecesTexture.png",	sf::IntRect(980,	0,	 260, 300));
	rookTextureW.loadFromFile("piecesTexture.png",		sf::IntRect(1340,	0,	 260, 300));
	queenTextureW.loadFromFile("piecesTexture.png",		sf::IntRect(300,	0,	 260, 300));
	kingTextureW.loadFromFile("piecesTexture.png",		sf::IntRect(0,		0,	 260, 300));

	pawnTextureB.loadFromFile("piecesTexture.png",		sf::IntRect(1680,	300, 260, 300));
	bishopTextureB.loadFromFile("piecesTexture.png",	sf::IntRect(650,	300, 260, 300));
	knightTextureB.loadFromFile("piecesTexture.png",	sf::IntRect(980,	300, 260, 300));
	rookTextureB.loadFromFile("piecesTexture.png",		sf::IntRect(1340,	300, 260, 300));
	queenTextureB.loadFromFile("piecesTexture.png",		sf::IntRect(300,	300, 260, 300));
	kingTextureB.loadFromFile("piecesTexture.png",		sf::IntRect(0,		300, 260, 300));
}

void foo(sf::RenderWindow* w)
{
	sf::Texture t;
	t.loadFromFile("piecesTexture.png", sf::IntRect(1680, 0, 260, 300));
	sf::Sprite s;

	s.setTexture(t);
	s.setPosition(100, 100);
	s.setColor(sf::Color::Blue);
	s.setScale(0.27, 0.27);

	w->draw(s);
}
