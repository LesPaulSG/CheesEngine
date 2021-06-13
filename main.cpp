#include "Engine.h"

int main() {
	bool gameOver = false;

	ChessEngine engine;
	sf::RenderWindow window(sf::VideoMode(600, 600), "Chess", sf::Style::None);

	sf::RectangleShape temp(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));

	std::vector<sf::RectangleShape> boardVis;
	std::vector<std::vector<sf::RectangleShape>> greens;
	std::vector<std::vector<sf::RectangleShape>> reds;
	boardVis.reserve(64);
	greens.reserve(8);
	reds.reserve(8);

	for (int i = 0; i < 8; ++i) {
		//std::vector<sf::RectangleShape> t;
		//t.reserve(8);
		for (int j = 0; j < 8; ++j) {
			temp.setFillColor(((i + j) % 2 != 0) ? sf::Color(64, 36, 6) : sf::Color(211, 211, 211));
			temp.setPosition(i * FIELD_SIZE, j * FIELD_SIZE);
			boardVis.push_back(temp);
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < 8; ++i) {
		std::vector<sf::RectangleShape> g;
		std::vector<sf::RectangleShape> r;
		g.reserve(8);
		r.reserve(8);
		for (int j = 0; j < 8; ++j) {
			temp.setFillColor(sf::Color(0, 255, 0, 128));
			temp.setPosition(i * FIELD_SIZE, j * FIELD_SIZE);
			g.push_back(temp);
			temp.setFillColor(sf::Color(255, 0, 0, 128));
			r.push_back(temp);
		}
		greens.push_back(g);
		reds.push_back(r);
		std::cout << std::endl;
	}

	while (!gameOver) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				gameOver = true;
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (engine.isWhiteTurn()) {
						engine.LmbInput(sf::Mouse::getPosition(window), engine.GetWhite());
					}
					else {
						engine.LmbInput(sf::Mouse::getPosition(window), engine.GetBlack());
					}
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.mouseButton.button == sf::Keyboard::F6) {
					engine.Save();
				}
			}
		}

		window.clear();
		for (int i = 0; i < 64; ++i) {
			window.draw(boardVis.at(i));
		}
		if (engine.GetActivePiece() != nullptr) {
			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {
					if (engine.GetActivePiece()->CanMoveHere(sf::Vector2i(j, i))) window.draw(greens.at(j).at(i));
					if (engine.GetActivePiece()->CanAttackHere(sf::Vector2i(j, i))) window.draw(reds.at(j).at(i));
				}
			}
		}

		engine.draw(&window);

		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			gameOver = true;
		}
	}
}