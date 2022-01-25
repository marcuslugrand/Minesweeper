#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class TileBomb{
	bool debugConfirm;
	Sprite sprite;
	Sprite flagSprite;
	Sprite foreground;
	Sprite background;

public:
	TileBomb(map<string, Texture>& sprites, int x, int y);
	vector<TileBomb*> neighbors;
	int numberBombs = 0;
	bool bombConfirm;
	bool flagConfirm;
	bool revealConfirm;
	bool reveal(int& countBack);
	bool pressFlag();
	void pressDebug();
	void setBomb1(bool bombActive);
	void updateSprite(map<string, Texture>& sprites);
	void draw(RenderWindow& gameCheck);
};

TileBomb::TileBomb(map<string, Texture>& sprites, int x, int y){
	background.setPosition(x, y);
	foreground.setPosition(x, y);
	flagSprite.setPosition(x, y);
	sprite.setPosition(x, y);
	background.setTexture(sprites["revealed"]);
	foreground.setTexture(sprites["hidden"]);
	flagSprite.setTexture(sprites["flag"]);
	flagSprite.setColor(Color(255, 255, 255, 0));
	bombConfirm = false;
	revealConfirm = false;
	flagConfirm = false;
	debugConfirm = false;
}

void TileBomb::draw(RenderWindow& gameCheck) {
	gameCheck.draw(background);
	gameCheck.draw(foreground);
	gameCheck.draw(sprite);
	gameCheck.draw(flagSprite);
}

void TileBomb::updateSprite(map<string, Texture>& textures){
	numberBombs = 0;
	for (int i = 0; i < 8; i++){
		if (neighbors[i] != nullptr && neighbors[i]->bombConfirm){
			numberBombs++;
		}
	}
	if (bombConfirm) {
		sprite.setTexture(textures["bomb"]);
		flagSprite.setColor(Color(255, 255, 255, 0));
	}
	else{
		switch (numberBombs){
		case 1: sprite.setTexture(textures["one"]); break;
		case 2: sprite.setTexture(textures["two"]); break;
		case 3: sprite.setTexture(textures["three"]); break;
		case 4: sprite.setTexture(textures["four"]); break;
		case 5: sprite.setTexture(textures["five"]); break;
		case 6: sprite.setTexture(textures["six"]); break;
		case 7: sprite.setTexture(textures["seven"]); break;
		case 8: sprite.setTexture(textures["eight"]); break;
		default: sprite.setTexture(textures["revealed"]); break;
		}
	}
	foreground.setColor(Color(255, 255, 255, 255));
	sprite.setColor(Color(255, 255, 255, 0));
	flagSprite.setColor(Color(255, 255, 255, 0));
	revealConfirm = false;
	flagConfirm = false;
	debugConfirm = false;
}

bool TileBomb::reveal(int& countBack) {
	if (!revealConfirm && !flagConfirm) {
		revealConfirm = true;
		countBack++;
		foreground.setColor(Color(255, 255, 255, 0));
		sprite.setColor(Color(255, 255, 255, 255));
		if (numberBombs == 0 && !bombConfirm) {
			for (int i = 0; i < 8; i++) {
				if (neighbors[i] != nullptr && !(neighbors[i]->bombConfirm)) {
					neighbors[i]->reveal(countBack);
				}
			}
		}
	}
	return bombConfirm;
}

void TileBomb::setBomb1(bool bombActive) {
	bombConfirm = bombActive;
}

bool TileBomb::pressFlag(){
	if (!revealConfirm){
		if (flagConfirm){
			flagConfirm = false;
			flagSprite.setColor(Color(255, 255, 255, 0));
		}
		else{
			flagConfirm = true;
			flagSprite.setColor(Color(255, 255, 255, 255));
		}
	}
	return flagConfirm;
}

void TileBomb::pressDebug(){
	if (bombConfirm && !revealConfirm){
		if (debugConfirm){
			debugConfirm = false;
			sprite.setColor(Color(255, 255, 255, 0));
		}
		else{
			debugConfirm = true;
			sprite.setColor(Color(255, 255, 255, 255));
		}
	}
}