#include "Engine.h"
#include <fstream>

int main() {
	ChessEngine engine;
	engine.draw();
	//std::cin.get();
	std::ofstream fout("quickSave.txt");
	if (!fout.is_open()) {
		std::cout << "blyaaat";
	}
	fout << "ebal rot";
	fout.close();
}