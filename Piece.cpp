#include "Piece.h"

bool isFieldFree(std::vector<std::vector<Piece*>>& board, int x, int y) {
	if (x < 0 || x > 7) return false;
	if (y < 0 || y > 7) return false;
	if (board[x][y] == nullptr) {
		return true;
	}
	return false;
}

bool isEnemyInField(std::vector<std::vector<Piece*>>& board, int x, int y, bool white) {
	if (x < 0 || x > 7) return false;
	if (y < 0 || y > 7) return false;
	if (board[x][y] != nullptr) {
		if (board[x][y]->white != white) {
			return true;
		}
	}
	return false;
}

void ContinuousMoving(Piece* p, int xDir, int yDir, std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack){
	int x = p->pos.x + xDir;
	int y = p->pos.y + yDir;
	while ((x >= 0) && (x <= 7) && (y >= 0) && (y <= 7)) {
		if (isFieldFree(board, x, y)) {
			//if (!ProverkaNaShah(p, x, y, board)) {
				p->avaliableMoves.push_back(sf::Vector2i(x, y));
				std::cout << "free" << x << ' ' << y << std::endl;
				x += xDir;
				y += yDir;
			//}
		}
		else if (isEnemyInField(board, x, y, p->white)) {
			//if (!ProverkaNaShah(p, x, y, board)) {
				p->avaliableMoves.push_back(sf::Vector2i(x, y));
				std::cout << "enemy" << x << ' ' << y << std::endl;
				fieldsUnderAttack.push_back(sf::Vector2i(x, y));
				break;
			//}
		}
		else {
			std::cout << "ally" << x << ' ' << y << std::endl;
			break;
		}
	}
}

bool ProverkaNaShah(Piece* p, int x, int y, std::vector<std::vector<Piece*>> board){
	board[p->pos.x][p->pos.y] == nullptr;
	board[x][y] = p;
	std::vector<sf::Vector2i> attack;
	for (auto vec : board) {
		for (auto iter : vec) {
			if (iter != nullptr) {
				iter->GenerateMoves(board, attack);
			}
		}
	}
	Piece* king = p->white ? whiteKing : blackKing;
	for (auto iter : attack) {
		if (iter == king->pos) {
			return true;
		}
	}
	return false;
}

Piece::Piece(int x, int y, bool white) : 
	pos(x, y), 
	white(white), 
	type(fType::DFLT) {
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

void Piece::Move(sf::Vector2i newPos){
	pos = newPos;
	body.setPosition(pos.x * FIELD_SIZE, pos.y * FIELD_SIZE);
	firstMove = false;
}

const std::vector<sf::Vector2i>* Piece::GetAvaliableMoves(){
	return &avaliableMoves;
}

void Pawn::GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack) {
	avaliableMoves.clear();
	int offsetY = white ? -1 : 1;
	if (isEnemyInField(board, pos.x + 1, pos.y + offsetY, white)) {
		//if (!ProverkaNaShah(this, pos.x + 1, pos.y + offsetY, board)) {
			avaliableMoves.push_back(sf::Vector2i(pos.x + 1, pos.y + offsetY));
			fieldsUnderAttack.push_back(sf::Vector2i(pos.x + 1, pos.y + offsetY));
		//}
	}
	if (isEnemyInField(board, pos.x - 1, pos.y + offsetY, white)) {
		//if (!ProverkaNaShah(this, pos.x - 1, pos.y + offsetY, board)) {
			avaliableMoves.push_back(sf::Vector2i(pos.x - 1, pos.y + offsetY));
			fieldsUnderAttack.push_back(sf::Vector2i(pos.x - 1, pos.y + offsetY));
		//}
	}
	if ((isFieldFree(board, pos.x, pos.y + offsetY*2)&&Piece::firstMove)) {
		//if (!ProverkaNaShah(this, pos.x, pos.y + offsetY * 2, board)) {
			avaliableMoves.push_back(sf::Vector2i(pos.x, pos.y + offsetY * 2));
		//}
	}
	if (isFieldFree(board, pos.x, pos.y + offsetY)) {
		//if (!ProverkaNaShah(this, pos.x, pos.y + offsetY, board)) {
			avaliableMoves.push_back(sf::Vector2i(pos.x, pos.y + offsetY));
		//}
	}
}

Pawn::Pawn(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::PAWN;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(1650, h, 260, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void Bishop::GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack){
	avaliableMoves.clear();
	ContinuousMoving(this,  1, -1, board, fieldsUnderAttack);
	ContinuousMoving(this,  1,  1, board, fieldsUnderAttack);
	ContinuousMoving(this, -1, -1, board, fieldsUnderAttack);
	ContinuousMoving(this, -1,  1, board, fieldsUnderAttack);
}

Bishop::Bishop(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::BSHP;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(660, h, 280, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void Knight::GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack){
	avaliableMoves.clear();
	if ((isFieldFree(board, pos.x + 1, pos.y - 2) || isEnemyInField(board, pos.x + 1, pos.y - 2, white))) {
		//if (!ProverkaNaShah(this, pos.x + 1, pos.y - 2, board)) {
			avaliableMoves.push_back(sf::Vector2i(pos.x + 1, pos.y - 2));
			fieldsUnderAttack.push_back(sf::Vector2i(pos.x + 1, pos.y - 2));
		//}
	}
	if ((isFieldFree(board, pos.x - 1, pos.y - 2) || isEnemyInField(board, pos.x - 1, pos.y - 2, white))) {
		//if (!ProverkaNaShah(this, pos.x - 1, pos.y - 2, board)) {
			avaliableMoves.push_back(sf::Vector2i(pos.x - 1, pos.y - 2));
			fieldsUnderAttack.push_back(sf::Vector2i(pos.x - 1, pos.y - 2));
		//}
	}
	if ((isFieldFree(board, pos.x - 2, pos.y - 1) || isEnemyInField(board, pos.x - 2, pos.y - 1, white))) {
		//if (!ProverkaNaShah(this, pos.x - 2, pos.y - 1, board)) {
			avaliableMoves.push_back(sf::Vector2i(pos.x - 2, pos.y - 1));
			fieldsUnderAttack.push_back(sf::Vector2i(pos.x - 2, pos.y - 1));
		//}
	}
	if ((isFieldFree(board, pos.x + 2, pos.y - 1) || isEnemyInField(board, pos.x + 2, pos.y - 1, white))) {
		//if (!ProverkaNaShah(this, pos.x + 2, pos.y - 1, board)) {
			avaliableMoves.push_back(sf::Vector2i(pos.x + 2, pos.y - 1));
			fieldsUnderAttack.push_back(sf::Vector2i(pos.x + 2, pos.y - 1));
		//}
	}
	if ((isFieldFree(board, pos.x - 2, pos.y + 1) || isEnemyInField(board, pos.x - 2, pos.y + 1, white))) {
		//if (!ProverkaNaShah(this, pos.x - 2, pos.y + 1, board)) {
			avaliableMoves.push_back(sf::Vector2i(pos.x - 2, pos.y + 1));
			fieldsUnderAttack.push_back(sf::Vector2i(pos.x - 2, pos.y + 1));
		//}
	}
	if ((isFieldFree(board, pos.x + 2, pos.y + 1) || isEnemyInField(board, pos.x + 2, pos.y + 1, white))) {
		//if (!ProverkaNaShah(this, pos.x + 2, pos.y + 1, board)) {
			avaliableMoves.push_back(sf::Vector2i(pos.x + 2, pos.y + 1));
			fieldsUnderAttack.push_back(sf::Vector2i(pos.x + 2, pos.y + 1));
		//}
	}
	if ((isFieldFree(board, pos.x + 1, pos.y + 2) || isEnemyInField(board, pos.x + 1, pos.y + 2, white))) {
		//if (!ProverkaNaShah(this, pos.x + 1, pos.y + 2, board)) {
			avaliableMoves.push_back(sf::Vector2i(pos.x + 1, pos.y + 2));
			fieldsUnderAttack.push_back(sf::Vector2i(pos.x + 1, pos.y + 2));
		//}
	}
	if ((isFieldFree(board, pos.x - 1, pos.y + 2) || isEnemyInField(board, pos.x - 1, pos.y + 2, white))) {
		//if (!ProverkaNaShah(this, pos.x - 1, pos.y + 2, board)) {
			avaliableMoves.push_back(sf::Vector2i(pos.x - 1, pos.y + 2));
			fieldsUnderAttack.push_back(sf::Vector2i(pos.x - 1, pos.y + 2));
		//}
	}
	
}

Knight::Knight(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::KNHT;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(990, h, 280, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void Rook::GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack){
	avaliableMoves.clear();
	ContinuousMoving(this,  1,  0, board, fieldsUnderAttack);
	ContinuousMoving(this,  0,  1, board, fieldsUnderAttack);
	ContinuousMoving(this, -1,  0, board, fieldsUnderAttack);
	ContinuousMoving(this,  0, -1, board, fieldsUnderAttack);
}

Rook::Rook(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::ROOK;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(1320, h, 260, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void Queen::GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack){
	avaliableMoves.clear();
	ContinuousMoving(this,  1, -1, board, fieldsUnderAttack);
	ContinuousMoving(this,  1,  1, board, fieldsUnderAttack);
	ContinuousMoving(this, -1, -1, board, fieldsUnderAttack);
	ContinuousMoving(this, -1,  1, board, fieldsUnderAttack);
	ContinuousMoving(this,  1,  0, board, fieldsUnderAttack);
	ContinuousMoving(this,  0,  1, board, fieldsUnderAttack);
	ContinuousMoving(this, -1,  0, board, fieldsUnderAttack);
	ContinuousMoving(this,  0, -1, board, fieldsUnderAttack);
}

Queen::Queen(int x, int y, bool white) : Piece(x, y, white) {
	Piece::type = fType::QUEN;
	int h = white ? WHITE_TEXTURE_HEIGHT : BLACK_TEXTURE_HEIGHT;
	tex.loadFromFile("piecesTexture.png", sf::IntRect(325, h, 300, 300));
	body.setTexture(tex);
	SpriteTransform(&body, pos.x, pos.y);
}

void King::GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack){
	avaliableMoves.clear();
	avaliableMoves.push_back(sf::Vector2i(pos.x + 1, pos.y - 1));
	avaliableMoves.push_back(sf::Vector2i(pos.x, pos.y - 1));
	avaliableMoves.push_back(sf::Vector2i(pos.x - 1, pos.y - 1));
	avaliableMoves.push_back(sf::Vector2i(pos.x + 1, pos.y));
	avaliableMoves.push_back(sf::Vector2i(pos.x - 1, pos.y));
	avaliableMoves.push_back(sf::Vector2i(pos.x + 1, pos.y + 1));
	avaliableMoves.push_back(sf::Vector2i(pos.x, pos.y + 1));
	avaliableMoves.push_back(sf::Vector2i(pos.x - 1, pos.y + 1));
}

King::King(int x, int y, bool white) : Piece(x, y, white) {
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
