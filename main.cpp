#include "Engine.h"

int main() {
	bool gameOver = false;

	ChessEngine engine;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Chess");// , sf::Style::None);

	sf::RectangleShape temp(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));

	std::vector<sf::RectangleShape> boardVis;
	std::vector<sf::RectangleShape> tmp;
	boardVis.reserve(64);

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			temp.setFillColor(((i + j) % 2 != 0) ? sf::Color(64, 36, 6) : sf::Color(211, 211, 211));
			temp.setPosition(i * FIELD_SIZE, j * FIELD_SIZE);
			boardVis.push_back(temp);
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			temp.setFillColor(sf::Color(0, 255, 0, 128));
			temp.setPosition(i * FIELD_SIZE, j * FIELD_SIZE);
			tmp.push_back(temp);
		}
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
					engine.LmbInput(sf::Mouse::getPosition(window), engine.GetWhite());
				}
			}
		}

		window.clear();
		for (int i = 0; i < 64; ++i) {
			window.draw(boardVis.at(i));
		}
		for (int i = 0; i < 64; ++i) {
			//window.draw(tmp.at(i));
		}

		engine.draw(&window);

		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			gameOver = true;
		}
	}
}