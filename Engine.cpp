#include <fstream>

#include "Engine.h"

ChessEngine::ChessEngine() :
	white(true),
	black(false),
	activePiece(nullptr) {
	board.reserve(8);
	boardVis.reserve(32);
	for (int i = 0; i < 8; ++i) {
		std::vector<Piece*> t;
		t.reserve(8);
		for (int j = 0; j < 8; ++j) {
			t.push_back(nullptr);
		}
		board.push_back(t);
	}
	
	Load();
	
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
	for (auto iter : boardVis) {
		iter->Update();
	}
}

void ChessEngine::CheckVictory(){

}

void ChessEngine::draw(sf::RenderWindow* w){
	if (activePiece != nullptr) 
		w->draw(actPieceLight);
	for (auto iter : boardVis) {
		iter->Draw(w);
	}
}

void ChessEngine::Load(std::string fileName){// = "satrtState.txt"){
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
	for (auto iter : *white.GetPieces()) {
		boardVis.push_back(new PieceVis(iter));
	}
	for (auto iter : *black.GetPieces()) {
		boardVis.push_back(new PieceVis(iter));
	}

	fin.close();
}

void ChessEngine::Save(std::string fileName){
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

void ChessEngine::DeletePiece(Piece* p){
	int i = 0;
	for (auto iter : boardVis) {
		if (iter->isSamePiece(p)) {
			boardVis.erase(boardVis.begin() + i);
			break;
		}
		++i;
	}
}

Player* ChessEngine::GetWhite(){
	return &white;
}

Player* ChessEngine::GetBlack(){
	return &black;
}

void ChessEngine::LmbInput(sf::Vector2i clickPos, Player* player){
	int x = clickPos.x / FIELD_SIZE;
	int y = clickPos.y / FIELD_SIZE;

	if (activePiece == nullptr) {
		if (board[x][y] != nullptr) {
			if (board[x][y]->white == player->isWhite()) {
				activePiece = board[x][y];
				actPieceLight.setPosition(sf::Vector2f(x * FIELD_SIZE, y * FIELD_SIZE));
			}
		}
	}
	else {
		if (activePiece->CanMoveHere(sf::Vector2i(x, y))||activePiece->CanAttackHere(sf::Vector2i(x, y))) {
			board[activePiece->pos.x][activePiece->pos.y] = nullptr;
			if (board[x][y] != nullptr) {
				DeletePiece(board[x][y]);
			}
			board[x][y] = activePiece;
			activePiece->Move(sf::Vector2i(x, y));
			activePiece = nullptr;
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
