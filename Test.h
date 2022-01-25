#pragma once
#include "TileBomb.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;

class Test
{
	int numCol;
	int numRow;
	int bombCount;
	int width;
	int height;
	int tileCount;
	int bombCounter;
	int posTest3;
	int posTest2;
	int posTest1;
	int posDebug;
	int flags;
	int numberBombs;
	int tilesReveal;
	map<string, Texture> sprites;
	vector<bool> tileBool;
	vector<int> testcase1;
	vector<int> testcase2;
	vector<int> testcase3;
	vector<int> lots_o_mines;
	vector<int> recursion_test;
	Sprite debugSprite;
	Sprite test1;
	Sprite test2;
	Sprite test3;
	Sprite smile;
	Sprite neg;
	Sprite firstNum;
	Sprite secondNum;
	Sprite thirdNum;
	bool gameLost;
	bool gameOver;

public:
	vector<TileBomb> allTiles;
	Test();
	void setRandom();
	void tileMarker(vector<int>& binary);
	void setTiles();
	void setBombs();
	void setIcons();
	void update(RenderWindow& game);
	void debug();
	void draw(RenderWindow& game);
	void restartCount();
	void restartSmile();
};

Test::Test(){
	srand(time(NULL));

	fstream File;
	string data;
	File.open("boards/config.cfg");
	if (File.is_open()) {
		while (!File.eof()) {
			getline(File, data);
			numCol = stoi(data);
			getline(File, data);
			numRow = stoi(data);
			getline(File, data);
			bombCount = stoi(data);
		}
	}
	File.close();

	fstream mainFile;
	mainFile.open("boards/testboard1.brd");
	if (mainFile.is_open()){
		while (getline(mainFile, data)){
			auto iter = data.begin();
			while (iter != data.end()){
				int holder = (*iter) - 48;
				testcase1.push_back(holder);
				iter++;
			}
		}
	}
	mainFile.close();

	mainFile.open("boards/testboard2.brd");
	if (mainFile.is_open()){
		while (getline(mainFile, data)){
			auto iter = data.begin();
			while (iter != data.end()){
				int holder = (*iter) - 48;
				testcase2.push_back(holder);
				iter++;
			}
		}
	}
	mainFile.close();

	mainFile.open("boards/testboard3.brd");
	if (mainFile.is_open()){
		while (getline(mainFile, data)){
			auto iter = data.begin();
			while (iter != data.end()){
				int holder = (*iter) - 48;
				testcase3.push_back(holder);
				iter++;
			}
		}
	}
	mainFile.close();

	mainFile.open("boards/lots_o_mines.brd");
	if (mainFile.is_open()){
		while (getline(mainFile, data)){
			auto iter = data.begin();
			while (iter != data.end()){
				int holder = (*iter) - 48;
				lots_o_mines.push_back(holder);
				iter++;
			}
		}
	}
	mainFile.close();

	mainFile.open("boards/recursion_test.brd");
	if (mainFile.is_open()){
		while (getline(mainFile, data)){
			auto iter = data.begin();
			while (iter != data.end()){
				int holder = (*iter) - 48;
				recursion_test.push_back(holder);
				iter++;
			}
		}
	}
	mainFile.close();

	width = numCol * 32;
	height = (numRow * 32) + 88;
	tileCount = numCol * numRow;
	posTest3 = width - 64;
	posTest2 = posTest3 - 64;
	posTest1 = posTest2 - 64;
	posDebug = posTest1 - 64;
	Texture loader;
	
	loader.loadFromFile("images/debug.png");
	sprites.emplace("debug", loader);
	loader.loadFromFile("images/test_1.png");
	sprites.emplace("testone", loader);
	loader.loadFromFile("images/test_2.png");
	sprites.emplace("testtwo", loader);
	loader.loadFromFile("images/test_3.png");
	sprites.emplace("testthree", loader);
	loader.loadFromFile("images/digits.png");
	sprites.emplace("digits", loader);
	loader.loadFromFile("images/face_happy.png");
	sprites.emplace("happy", loader);
	loader.loadFromFile("images/face_lose.png");
	sprites.emplace("lose", loader);
	loader.loadFromFile("images/face_win.png");
	sprites.emplace("win", loader);
	loader.loadFromFile("images/flag.png");
	sprites.emplace("flag", loader);
	loader.loadFromFile("images/mine.png");
	sprites.emplace("bomb", loader);
	loader.loadFromFile("images/number_1.png");
	sprites.emplace("one", loader);
	loader.loadFromFile("images/number_2.png");
	sprites.emplace("two", loader);
	loader.loadFromFile("images/number_3.png");
	sprites.emplace("three", loader);
	loader.loadFromFile("images/number_4.png");
	sprites.emplace("four", loader);
	loader.loadFromFile("images/number_5.png");
	sprites.emplace("five", loader);
	loader.loadFromFile("images/number_6.png");
	sprites.emplace("six", loader);
	loader.loadFromFile("images/number_7.png");
	sprites.emplace("seven", loader);
	loader.loadFromFile("images/number_8.png");
	sprites.emplace("eight", loader);
	loader.loadFromFile("images/tile_hidden.png");
	sprites.emplace("hidden", loader);
	loader.loadFromFile("images/tile_revealed.png");
	sprites.emplace("revealed", loader);

	debugSprite.setTexture(sprites["debug"]);
	debugSprite.setPosition(posDebug, numRow * 32);
	test1.setTexture(sprites["testone"]);
	test1.setPosition(posTest1, numRow * 32);
	test2.setTexture(sprites["testtwo"]);
	test2.setPosition(posTest2, numRow * 32);
	test3.setTexture(sprites["testthree"]);
	test3.setPosition(posTest3, numRow * 32);
	smile.setTexture(sprites["happy"]);
	smile.setPosition((width / 2) - 32, numRow * 32);
	firstNum.setTexture(sprites["digits"]);
	firstNum.setTextureRect(Rect<int>(0, 0, 21, 32));
	firstNum.setPosition(21, numRow * 32);
	secondNum.setTexture(sprites["digits"]);
	secondNum.setTextureRect(Rect<int>(21 * 5, 0, 21, 32));
	secondNum.setPosition(42, numRow * 32);
	thirdNum.setTexture(sprites["digits"]);
	thirdNum.setTextureRect(Rect<int>(0, 0, 21, 32));
	thirdNum.setPosition(63, numRow * 32);

	setTiles();
	numberBombs = 0;
	flags = bombCount;
	bombCounter = flags - numberBombs;
	setRandom();
}

void Test::setTiles() {
	float x = 0;
	float y = 0;
	for (int i = 0; i < numRow; i++) {
		for (int j = 0; j < numCol; j++) {
			TileBomb t = TileBomb(sprites, x, y);
			allTiles.push_back(t);
			x = x + 32.f;
		}
		x = 0;
		y = y + 32.f;
	}
}

void Test::setRandom(){
	tileBool.clear();
	vector<int> binary;
	int randomnum;
	bool getfree = false;

	for (int i = 0; i < bombCount; i++){
		while (!getfree){
			randomnum = rand() % tileCount;
			if (find(binary.begin(), binary.end(), randomnum) == binary.end()){
				binary.push_back(randomnum);
				getfree = true;
			}
		}
		getfree = false;
	}

	auto iter = binary.begin();
	for (int j = 0; j < tileCount; j++){
		iter = find(binary.begin(), binary.end(), j);
		if (iter == binary.end()){
			tileBool.push_back(false);
		}
		else{
			tileBool.push_back(true);
		}
	}
	setBombs();
	setIcons();
	//numbombs = 0;
	//flags = bombCount;
	//bombCounter = flags - numberBombs;
	//bombCounter = numberBombs - flags;

	restartCount();
	tilesReveal = 0;

	gameLost = false;
	gameOver = false;
}

void Test::setBombs() {
	for (int i = 0; i < tileCount; i++) {
		allTiles[i].setBomb1(tileBool[i]);
	}
}

void Test::setIcons() {
	for (int i = 0; i < tileCount; i++) {
		allTiles[i].neighbors.clear();
		for (int j = 0; j < 8; j++) {
			allTiles[i].neighbors.push_back(nullptr);
		}
		if (i == 0) {
			allTiles[i].neighbors[4] = &(allTiles[i + 1]);
			allTiles[i].neighbors[6] = &(allTiles[i + numCol]);
			allTiles[i].neighbors[7] = &(allTiles[i + (numCol + 1)]);
		}
		else if (i == (numCol - 1)) {
			allTiles[i].neighbors[3] = &(allTiles[i - 1]);
			allTiles[i].neighbors[5] = &(allTiles[i + (numCol - 1)]);
			allTiles[i].neighbors[6] = &(allTiles[i + numCol]);
		}
		else if (i == (tileCount - numCol)) {
			allTiles[i].neighbors[4] = &(allTiles[i + 1]);
			allTiles[i].neighbors[1] = &(allTiles[i - numCol]);
			allTiles[i].neighbors[2] = &(allTiles[i - (numCol - 1)]);
		}
		else if (i == (tileCount - 1)) {
			allTiles[i].neighbors[3] = &(allTiles[i - 1]);
			allTiles[i].neighbors[1] = &(allTiles[i - numCol]);
			allTiles[i].neighbors[0] = &(allTiles[i - (numCol + 1)]);
		}
		else if (i < (numCol - 1)) {
			allTiles[i].neighbors[3] = &(allTiles[i - 1]);
			allTiles[i].neighbors[4] = &(allTiles[i + 1]);
			allTiles[i].neighbors[5] = &(allTiles[i + (numCol - 1)]);
			allTiles[i].neighbors[6] = &(allTiles[i + numCol]);
			allTiles[i].neighbors[7] = &(allTiles[i + (numCol + 1)]);
		}
		else if (i > (tileCount - numCol)) {
			allTiles[i].neighbors[3] = &(allTiles[i - 1]);
			allTiles[i].neighbors[4] = &(allTiles[i + 1]);
			allTiles[i].neighbors[2] = &(allTiles[i - (numCol - 1)]);
			allTiles[i].neighbors[1] = &(allTiles[i - numCol]);
			allTiles[i].neighbors[0] = &(allTiles[i - (numCol + 1)]);
		}
		else if ((i % numCol) == 0) {
			allTiles[i].neighbors[4] = &(allTiles[i + 1]);
			allTiles[i].neighbors[6] = &(allTiles[i + numCol]);
			allTiles[i].neighbors[7] = &(allTiles[i + (numCol + 1)]);
			allTiles[i].neighbors[1] = &(allTiles[i - numCol]);
			allTiles[i].neighbors[2] = &(allTiles[i - (numCol - 1)]);
		}
		else if (((i - (numCol - 1)) % numCol) == 0) {
			allTiles[i].neighbors[3] = &(allTiles[i - 1]);
			allTiles[i].neighbors[0] = &(allTiles[i - (numCol + 1)]);
			allTiles[i].neighbors[1] = &(allTiles[i - numCol]);
			allTiles[i].neighbors[5] = &(allTiles[i + (numCol - 1)]);
			allTiles[i].neighbors[6] = &(allTiles[i + numCol]);
		}
		else {
			allTiles[i].neighbors[3] = &(allTiles[i - 1]);
			allTiles[i].neighbors[4] = &(allTiles[i + 1]);
			allTiles[i].neighbors[5] = &(allTiles[i + (numCol - 1)]);
			allTiles[i].neighbors[6] = &(allTiles[i + numCol]);
			allTiles[i].neighbors[7] = &(allTiles[i + (numCol + 1)]);
			allTiles[i].neighbors[2] = &(allTiles[i - (numCol - 1)]);
			allTiles[i].neighbors[1] = &(allTiles[i - numCol]);
			allTiles[i].neighbors[0] = &(allTiles[i - (numCol + 1)]);
		}
		allTiles[i].updateSprite(sprites);
	}
}

void Test::restartCount() {
	int copy = bombCounter;
	if (copy >= 0 && copy <= 100) {
		int onesplace = copy % 10;
		copy /= 10;
		int tensplace = copy % 10;
		int hundredsplace = 0;
		neg.setTextureRect(Rect<int>(0, 0, 21, 32));
		neg.setColor(Color(255, 255, 255, 255));
		firstNum.setTextureRect(Rect<int>(21 * hundredsplace, 0, 21, 32));
		secondNum.setTextureRect(Rect<int>(21 * tensplace, 0, 21, 32));
		thirdNum.setTextureRect(Rect<int>(21 * onesplace, 0, 21, 32));
	}
	else if (copy > 100) {
		int onesplace = copy % 10;
		copy /= 10;
		int tensplace = copy % 10;
		copy /= 10;
		int hundredsplace = copy % 10;
		neg.setTextureRect(Rect<int>(0, 0, 21, 32));
		firstNum.setTextureRect(Rect<int>(21 * hundredsplace, 0, 21, 32));
		secondNum.setTextureRect(Rect<int>(21 * tensplace, 0, 21, 32));
		thirdNum.setTextureRect(Rect<int>(21 * onesplace, 0, 21, 32));
	}
	else {
		neg.setTexture(sprites["digits"]);
		neg.setPosition(0, numRow * 32);
		copy = copy * -1;
		if (copy > 99) {
			int onesplace = copy % 10;
			copy /= 10;
			int tensplace = copy % 10;
			copy /= 10;
			int hundredsplace = copy % 10;
			neg.setTextureRect(Rect<int>(21 * 10, 0, 21, 32));
			firstNum.setTextureRect(Rect<int>(21 * hundredsplace, 0, 21, 32));
			secondNum.setTextureRect(Rect<int>(21 * tensplace, 0, 21, 32));
			thirdNum.setTextureRect(Rect<int>(21 * onesplace, 0, 21, 32));
		}
		else {
			int onesplace = copy % 10;
			copy /= 10;
			int tensplace = copy % 10;
			int hundredsplace = 0;
			neg.setTextureRect(Rect<int>(21 * 10, 0, 21, 32));
			firstNum.setTextureRect(Rect<int>(21 * hundredsplace, 0, 21, 32));
			secondNum.setTextureRect(Rect<int>(21 * tensplace, 0, 21, 32));
			thirdNum.setTextureRect(Rect<int>(21 * onesplace, 0, 21, 32));
		}
	}
}

void Test::update(RenderWindow& game){
	if (Mouse::isButtonPressed(Mouse::Left)){
		Vector2i loc = Mouse::getPosition(game);
		if (loc.y >= 0 && loc.y < (numRow * 32) && !gameOver){
			if (loc.x >= 0 && loc.x <= width){
				int x = (loc.x / 32);
				int y = (loc.y / 32);
				int pos = (y * numCol) + x;
				int count = 0;
				if (allTiles[pos].reveal(count)){
					gameLost = true;
					gameOver = true;
					int count2 = 0;
					for (int i = 0; i < tileCount; i++){
						if (allTiles[i].flagConfirm && allTiles[i].bombConfirm){
							allTiles[i].pressFlag();
						}
						else if (allTiles[i].bombConfirm){
							allTiles[i].reveal(count2);
						}
					}
				}
				else {
					tilesReveal += count;
				}
			}
		}
		else if (loc.y >= (numRow * 32) && loc.y < ((numRow * 32) + 64)){
			if (loc.x >= ((width / 2) - 32) && loc.x < (((width / 2) - 32)) + 64){
				bombCounter = bombCount;
				restartCount();
				setRandom();
			}
			if (loc.x >= posDebug && loc.x < posTest1 && !gameOver){
				debug();
			}
			if (loc.x >= posTest1 && loc.x < posTest2 && !gameOver){
				bombCounter = 0;
				tileMarker(testcase1);
			}
			if (loc.x >= posTest2 && loc.x < posTest3 && !gameOver){
				bombCounter = 0;
				tileMarker(testcase2);
			}
			if (loc.x >= posTest3 && loc.x < width && !gameOver){
				bombCounter = 0;
				tileMarker(testcase3);
			}
		}
	}
	if (Mouse::isButtonPressed(Mouse::Right) && !gameOver){
		Vector2i loc = Mouse::getPosition(game);
		if (loc.x >= 0 && loc.x <= width){
			if (loc.y >= 0 && loc.y <= (numRow * 32)){
				int x = (loc.x / 32);
				int y = (loc.y / 32);
				int pos = (y * numCol) + x;
				if (!allTiles[pos].flagConfirm && !allTiles[pos].revealConfirm){
					allTiles[pos].pressFlag();
					bombCounter--;
				}
				else if (!allTiles[pos].revealConfirm && allTiles[pos].flagConfirm){
					allTiles[pos].pressFlag();
					bombCounter++;
				}
				restartCount();
			}
		}
	}
	if (tilesReveal == (tileCount - numberBombs) && !gameLost){
		gameOver = true;
		for (int k = 0; k < tileCount; k++){
			if (allTiles[k].bombConfirm && !allTiles[k].flagConfirm){
				allTiles[k].pressFlag();
			}
		}
	}
	restartSmile();
	draw(game);
}

void Test::tileMarker(vector<int>& binary) {
	tileBool.clear();
	for (int i = 0; i < tileCount; i++) {
		if (binary[i] == 0) {
			tileBool.push_back(false);
		}
		else if (binary[i] == 1) {
			tileBool.push_back(true);
		}
	}
	setBombs();
	setIcons();
	numberBombs = 0;
	flags = 0;
	for (int j = 0; j < tileCount; j++) {
		for (int k = 0; k < binary[j]; k++) {
			if (binary[j] == 0) {
				numberBombs = numberBombs;
			}
			else {
				numberBombs++;
			}
		}
	}
	bombCounter = numberBombs - flags;
	restartCount();
	gameLost = false;
	gameOver = false;
}

void Test::debug(){
	for (int i = 0; i < tileCount; i++){
		allTiles[i].pressDebug();
	}
}

void Test::draw(RenderWindow& game){
	for (int i = 0; i < tileCount; i++) {
		allTiles[i].draw(game);
	}
	game.draw(smile);
	game.draw(debugSprite);
	game.draw(test1);
	game.draw(test2);
	game.draw(test3);
	game.draw(firstNum);
	game.draw(secondNum);
	game.draw(thirdNum);
	if (bombCounter < 0) {
		game.draw(neg);
	}
}

void Test::restartSmile(){
	if (gameOver){
		if (gameLost){
			smile.setTexture(sprites["lose"]);
		}
		else{
			smile.setTexture(sprites["win"]);
		}
	}
	else{
		smile.setTexture(sprites["happy"]);
	}
}