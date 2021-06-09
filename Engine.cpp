#include <fstream>

#include "Engine.h"

ChessEngine::ChessEngine() : 
	white(true), 
	black(false),
	activePiece(nullptr) {
	Load();
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			board[i][j] = nullptr;
		}
	}
	Save();
	actPieceLight.setSize(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));
	actPieceLight.setFillColor(sf::Color(250, 200, 25, 128));
	actPieceLight.setPosition(sf::Vector2f(-100, -100));
}

void ChessEngine::Move(int player, sf::Vector2i from, sf::Vector2i to){

}

void ChessEngine::RoundEnd(){

}

void ChessEngine::CheckVictory(){

}

void ChessEngine::draw(sf::RenderWindow* w){
	//if (activePiece != nullptr) 
		w->draw(actPieceLight);
	white.draw(w);
	black.draw(w);
}

void ChessEngine::Load(std::string fileName){// = "satrtState.txt"){
	std::cout << "load" << std::endl;
	std::ifstream fin;
	fin.open(fileName);

	if (!fin.is_open()) {
		std::cout << "not open" << std::endl;
		std::cout << fileName << std::endl;
	}

	int num;
	char symbol = 0;
	bool isWhite;
	int x = 0, y = 0;
	std::string line;

	fin >> num;

	for (int i = 0; i < num; ++i) {
		fin >> symbol >> isWhite >> x >> y;

		if (isWhite) {
			white.AddPiece(symbol, x, y);
		}
		else {
			black.AddPiece(symbol, x, y);
		}
	}

	fin.close();
}

void ChessEngine::Save(std::string fileName){
	std::cout << "save" << std::endl;
	std::ofstream fout("quickSave.txt", std::ios::out);
	if (!fout.is_open()) {
		std::cout << "not open" << std::endl;
		std::cout << fileName << std::endl;
	}

	int num = white.GetNumOfPieces() + black.GetNumOfPieces();
	fout << num << std::endl;

	Piece* temp;
	for (int i = 0; i < white.GetNumOfPieces(); ++i){
		temp = white.GetPieces()->at(i);
		fout << temp->GetSymbol() << ' ' << 1 << ' ' << temp->GetPos().x << ' ' << temp->GetPos().y << std::endl;
	}

	for (int i = 0; i < black.GetNumOfPieces(); ++i) {
		temp = black.GetPieces()->at(i);
		fout << temp->GetSymbol() << ' ' << 0 << ' ' << temp->GetPos().x << ' ' << temp->GetPos().y << std::endl;
	}

	fout.close();
}

std::vector<sf::Sprite> ChessEngine::GetPiecesToDraw(){
	std::vector<sf::Sprite> sprites;
	for (auto iter : *white.GetPieces()) {
		sprites.push_back(iter->body);
	}
	for (auto iter : *black.GetPieces()) {
		sprites.push_back(iter->body);
	}
	return sprites;
}

Player* ChessEngine::GetWhite(){
	return &white;
}

Player* ChessEngine::GetBlack(){
	return &black;
}

void ChessEngine::LmbInput(sf::Vector2i clickPos, Player* player){
	//std::cout << clickPos.x << ' ' << clickPos.y << std::endl;
	int x = clickPos.x / FIELD_SIZE;
	int y = clickPos.y / FIELD_SIZE;
	//std::cout << x << ' ' << y << std::endl;

	//if (activePiece == nullptr) {
		//if (board[x][y] != nullptr) {
			//if (board[x][y]->white == player->isWhite()) {
				activePiece = board[x][y];
				
				actPieceLight.setPosition(sf::Vector2f(x * FIELD_SIZE, y * FIELD_SIZE));
				std::cout << actPieceLight.getPosition().x << ' ' << actPieceLight.getPosition().y << std::endl;
			//}
		//}
	//}
	/*else {
		if (board[x][y] != nullptr) {
			if (board[x][y]->white == player->isWhite()) {
				activePiece = board[x][y];
			}
		}
	}*/
}
