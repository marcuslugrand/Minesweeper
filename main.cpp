#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TileBomb.h"
#include "Test.h"
using namespace sf;
using namespace std;

int main(){
	int numColMain = 0;
	int numRowMain = 0;
	int numBombMain = 0;
	int widthMain = 0;
	int heightMain = 0;
	int tileCountMain = 0;
	fstream File;
	string line;
	File.open("boards/config.cfg");
	if (File.is_open()) {
		while (!File.eof()){
			getline(File, line);
			numColMain = stoi(line);
			getline(File, line);
			numRowMain = stoi(line);
			getline(File, line);
			numBombMain = stoi(line);
		}
	}
	File.close();

	widthMain = numColMain * 32;
	heightMain = (numRowMain * 32) + 88;
	tileCountMain = numColMain * numRowMain;
	sf::RenderWindow game(sf::VideoMode(widthMain, heightMain), "Minesweeper");
	Test developer;

	while (game.isOpen()){
		sf::Event start;
		while (game.pollEvent(start)){
			if (start.type == sf::Event::Closed) {
				game.close();
			}
			game.clear(Color(255, 255, 255, 255));
			developer.update(game);
			game.display();
		}
	}
	return 0;
}