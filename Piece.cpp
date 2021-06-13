#include "Piece.h"

bool Piece::isFieldFree(int x, int y) {
	if (x < 0 || x > 7) return false;
	if (y < 0 || y > 7) return false;
	if (boardPtr->at(x).at(y) == nullptr) {
		return true;
	}
	return false;
}

bool Piece::isEnemyInField(int x, int y, bool white) {
	if (x < 0 || x > 7) return false;
	if (y < 0 || y > 7) return false;
	if (boardPtr->at(x).at(y) != nullptr) {
		if (boardPtr->at(x).at(y)->white != white) {
			std::cout << x << ' ' << y << ' ' << boardPtr->at(x).at(y)->GetSymbol() << std::endl;
			return true;
		}
	}
	return false;
}

bool Piece::isFieldAvaliable(int x, int y, int depth) {
	if (isFieldFree(x, y)) {
		//if ((depth <= 0) || !ProverkaNaShah(x, y, depth - 1)) {
			avaliableMoves.push_back(sf::Vector2i(x, y));
			return true;
		//}
	}
	else if (isEnemyInField(x, y, white)) {
		//if ((depth <= 0) || !ProverkaNaShah(x, y, depth - 1)) {
			avaliableAttacks.push_back(sf::Vector2i(x, y));
			return false;
		//}
	}
	else {
		return false;
	}
}

void Piece::ContinuousMoving(int xDir, int yDir, int depth = 1){
	int x = pos.x + xDir;
	int y = pos.y + yDir;
	while ((x >= 0) && (x <= 7) && (y >= 0) && (y <= 7)) {
		if (!isFieldAvaliable(x, y, depth)) {
			break;
		}
		x += xDir;
		y += yDir;
	}
}

bool Piece::ProverkaNaShah(int x, int y, int depth){
	//std::vector<std::vector<Piece*>> boardCopy = *boardPtr;
	/*for (int i = 0; i < 8; ++i) {
		std::vector<Piece*> tmp;
		tmp.reserve(8);
		for (int j = 0; j < 8; ++j) {
			if (boardPtr->at(i).at(j) != nullptr) {
				tmp.push_back(new Piece(*boardPtr->at(i).at(j)));
			}
			else {
				tmp.push_back(nullptr);
			}
		}
		boardCopy.push_back(tmp);
	}*/
	int oldX = pos.x, oldY = pos.y;
	Piece* oldPtr = boardPtr->at(x).at(y);
	boardPtr->at(pos.x).at(pos.y) == nullptr;
	boardPtr->at(x).at(y) = this;
	std::vector<sf::Vector2i> attack;
	for (auto vec : *boardPtr) {
		for (auto iter : vec) {
			if (iter != nullptr) {
				iter->GenerateMoves(depth-1);
			}
		}
	}
	Piece* king = white ? whiteKing : blackKing;
	for (auto iter : attack) {
		if (iter == king->pos) {
			//boardPtr->at(oldX).at(oldY) = this;
			//boardPtr->at(pos.x).at(pos.y) = oldPtr;
			//GenerateMoves(0);
			return true;
		}
	}
	//boardPtr->at(oldX).at(oldY) = this;
	//boardPtr->at(pos.x).at(pos.y) = oldPtr;
	//GenerateMoves(0);
	return false;
}

Piece::Piece(int x, int y, bool white, std::vector<std::vector<Piece*>>& board) :
	pos(x, y), 
	white(white), 
	type(fType::DFLT),
	boardPtr(&board) {
}

void Piece::GenerateMoves(int depth){
	avaliableMoves.clear();
	avaliableAttacks.clear();
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

bool Piece::CanAttackHere(sf::Vector2i dest){
	for (auto iter : avaliableAttacks) {
		if (iter == dest) {
			return true;
		}
	}
	return false;
}

void Piece::Move(sf::Vector2i newPos){
	pos = newPos;
	body.setPosition(pos.x * FIELD_SIZE, pos.y * FIELD_SIZE);
	firstMove = false;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (boardPtr->at(j).at(i) != nullptr) {
				std::cout << boardPtr->at(j).at(i)->GetSymbol() << '|';
			}
			else {
				std::cout << '.' << '|';
			}
		}
		std::cout << std::endl;
	}
	firstMove = false;
}

const std::vector<sf::Vector2i>* Piece::GetAvaliableMoves(){
	return &avaliableMoves;
}

void Pawn::GenerateMoves(int depth) {
	Piece::GenerateMoves(0);
	int offsetY = white ? -1 : 1;
	if (isEnemyInField(pos.x + 1, pos.y + offsetY, white)) {
		//if (!ProverkaNaShah(this, pos.x + 1, pos.y + offsetY, board)) {
			avaliableAttacks.push_back(sf::Vector2i(pos.x + 1, pos.y + offsetY));
		//}
	}
	if (isEnemyInField(pos.x - 1, pos.y + offsetY, white)) {
		//if (!ProverkaNaShah(this, pos.x - 1, pos.y + offsetY, board)) {
			avaliableAttacks.push_back(sf::Vector2i(pos.x - 1, pos.y + offsetY));
		//}
	}
	isFieldAvaliable(pos.x,		pos.y + offsetY, 1);
	if (Piece::firstMove) {
		isFieldAvaliable(pos.x, pos.y + offsetY * 2, 1);
	}
}

Pawn::Pawn(int x, int y, bool white, std::vector<std::vector<Piece*>>& board) :
	Piece(x, y, white, board) {
	Piece::type = fType::PAWN;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(1650, h, 260, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void Bishop::GenerateMoves(int depth){
	Piece::GenerateMoves(0);
	ContinuousMoving(1, -1);
	ContinuousMoving(1,  1);
	ContinuousMoving(-1, -1);
	ContinuousMoving(-1,  1);
}

Bishop::Bishop(int x, int y, bool white, std::vector<std::vector<Piece*>>& board) : 
	Piece(x, y, white, board) {
	Piece::type = fType::BSHP;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(660, h, 280, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void Knight::GenerateMoves(int depth){
	Piece::GenerateMoves(0);
	isFieldAvaliable(pos.x + 1, pos.y - 2, 1);
	isFieldAvaliable(pos.x - 1, pos.y - 2, 1);
	isFieldAvaliable(pos.x - 2, pos.y - 1, 1);
	isFieldAvaliable(pos.x + 2, pos.y - 1, 1);
	isFieldAvaliable(pos.x - 2, pos.y + 1, 1);
	isFieldAvaliable(pos.x + 2, pos.y + 1, 1);
	isFieldAvaliable(pos.x + 1, pos.y + 2, 1);
	isFieldAvaliable(pos.x - 1, pos.y + 2, 1);
	
}

Knight::Knight(int x, int y, bool white, std::vector<std::vector<Piece*>>& board) : 
	Piece(x, y, white, board) {
	Piece::type = fType::KNHT;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(990, h, 280, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void Rook::GenerateMoves(int depth){
	Piece::GenerateMoves(0);
	ContinuousMoving(1,  0);
	ContinuousMoving(0,  1);
	ContinuousMoving(-1,  0);
	ContinuousMoving(0, -1);
}

Rook::Rook(int x, int y, bool white, std::vector<std::vector<Piece*>>& board) : 
	Piece(x, y, white, board) {
	Piece::type = fType::ROOK;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(1320, h, 260, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void Queen::GenerateMoves(int depth){
	Piece::GenerateMoves(0);
	ContinuousMoving(1, -1);
	ContinuousMoving(1,  1);
	ContinuousMoving(-1, -1);
	ContinuousMoving(-1,  1);
	ContinuousMoving(1,  0);
	ContinuousMoving(0,  1);
	ContinuousMoving(-1,  0);
	ContinuousMoving(0, -1);
}

Queen::Queen(int x, int y, bool white, std::vector<std::vector<Piece*>>& board) : 
	Piece(x, y, white, board) {
	Piece::type = fType::QUEN;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(325, h, 300, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void King::GenerateMoves(int depth){
	Piece::GenerateMoves(0);
	isFieldAvaliable(pos.x + 1, pos.y - 1, 1);
	isFieldAvaliable(pos.x + 0, pos.y - 1, 1);
	isFieldAvaliable(pos.x - 1, pos.y - 1, 1);
	isFieldAvaliable(pos.x + 1, pos.y + 0, 1);
	isFieldAvaliable(pos.x - 1 ,pos.y + 0, 1);
	isFieldAvaliable(pos.x + 1, pos.y + 1, 1);
	isFieldAvaliable(pos.x + 0, pos.y + 1, 1);
	isFieldAvaliable(pos.x - 1, pos.y + 1, 1);
}

King::King(int x, int y, bool white, std::vector<std::vector<Piece*>>& board) : 
	Piece(x, y, white, board) {
	Piece::type = fType::KING;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(0, h, 260, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
	if (white) {
		whiteKing = this;
	}
	else {
		blackKing = this;
	}
}
