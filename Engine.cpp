#include <fstream>

#include "Engine.h"

ChessEngine::ChessEngine() :
	white(true),
	black(false),
	activePiece(nullptr) {
	board.reserve(8);
	for (int i = 0; i < 8; ++i) {
		std::vector<Piece*> t;
		t.reserve(8);
		for (int i = 0; i < 8; ++i) {
			t.push_back(nullptr);
		}
		board.push_back(t);
	}
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
	for (auto iter : *white.GetPieces()) {
		int x = iter->pos.x;
		int y = iter->pos.y;
		board[x][y] = iter;
	}
	for (auto iter : *black.GetPieces()) {
		int x = iter->pos.x;
		int y = iter->pos.y;
		board[x][y] = iter;
	}
	/*for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[j][i] != nullptr) {
				std::cout << board[j][i]->GetSymbol() << '|';
			}
			else {
				std::cout << '0' << '|';
			}
		}
		std::cout << std::endl;
	}*/

	RoundEnd();
	whiteTurn = true;
}

void ChessEngine::Move(int player, sf::Vector2i from, sf::Vector2i to){

}

void ChessEngine::RoundEnd(){
	whiteTurn = !whiteTurn;
	for (auto iter : *white.GetPieces()) {
		iter->GenerateMoves(1);
	}
	for (auto iter : *black.GetPieces()) {
		iter->GenerateMoves(1);
	}
}

void ChessEngine::CheckVictory(){

}

void ChessEngine::draw(sf::RenderWindow* w){
	if (activePiece != nullptr) 
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
			white.AddPiece(symbol, x, y, board);
		}
		else {
			black.AddPiece(symbol, x, y, board);
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

	if (activePiece == nullptr) {
		if (board[x][y] != nullptr) {
			if (board[x][y]->white == player->isWhite()) {
				activePiece = board[x][y];
				//activePiece->GenerateMoves(board, *GetAttackFields(player->isWhite()), 0);
				//std::cout << board[x][y]->GetSymbol() << std::endl;
				actPieceLight.setPosition(sf::Vector2f(x * FIELD_SIZE, y * FIELD_SIZE));
				//std::cout << actPieceLight.getPosition().x << ' ' << actPieceLight.getPosition().y << std::endl;
				for (auto iter : activePiece->avaliableAttacks) {
					std::cout << iter.x << ' ' << iter.y << std::endl;
				}
			}
		}
	}
	else {
		if (activePiece->CanMoveHere(sf::Vector2i(x, y))||activePiece->CanAttackHere(sf::Vector2i(x, y))) {
			board[activePiece->pos.x][activePiece->pos.y] = nullptr;
			if (board[x][y] != nullptr) {
				if (player->isWhite()) {
					black.DeletePiece(board[x][y]);
				}
				else {
					white.DeletePiece(board[x][y]);
				}
			}
			board[x][y] = activePiece;
			activePiece->Move(sf::Vector2i(x, y));
			activePiece = nullptr;
		//	if (board[x][y]->white == player->isWhite()) {
		//		activePiece = board[x][y];
		//	}
			//whiteTurn = !whiteTurn;
			RoundEnd();
		}
		else {
			activePiece = nullptr;
		}
	}
}

Piece* ChessEngine::GetActivePiece(){
	if (activePiece != nullptr) {
		return activePiece;
	}
	return nullptr;
}

bool ChessEngine::isWhiteTurn(){
	return whiteTurn;
}

std::vector<sf::Vector2i>* ChessEngine::GetAttackFields(bool white){
	if (white) {
		return &whiteAttackFields;
	}
	return &blackAttackFields;
}
