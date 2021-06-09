#include "Engine.h"

int main() {
	//PreLoad();

	bool gameOver = false;

	ChessEngine engine;
	//engine.draw();
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Chess");// , sf::Style::None);

	sf::RectangleShape temp(sf::Vector2f(75, 75));

	std::vector<sf::RectangleShape> boardVis;
	std::vector<sf::RectangleShape> tmp;
	boardVis.reserve(64);

	

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			temp.setFillColor(((i + j) % 2 != 0) ? sf::Color(64, 36, 6) : sf::Color(211, 211, 211));
			temp.setPosition(i * 75, j * 75);
			boardVis.push_back(temp);
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			temp.setFillColor(sf::Color(0, 255, 0, 128));
			temp.setPosition(i * 75, j * 75);
			tmp.push_back(temp);
		}
		std::cout << std::endl;
	}

	while (!gameOver) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				gameOver = true;
				//window.close();
			}
		}

		window.clear();
		for (int i = 0; i < 64; ++i) {
			window.draw(boardVis.at(i));
		}
		for (int i = 0; i < 64; ++i) {
			//window.draw(tmp.at(i));
		}

		//window.draw(s);
		//foo(&window);
		engine.draw(&window);

		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			gameOver = true;
			//window.close();
		}
	}
}