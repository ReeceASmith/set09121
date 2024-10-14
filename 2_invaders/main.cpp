#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "ship.h"

using namespace sf;
using namespace std;


sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship*> ships;



void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));

	Invader* inv = new Invader(sf::IntRect(Vector2(0, 0), Vector2(32, 32)), { 100, 100 });
	ships.push_back(inv);
}


void Reset() {

}


void Update(RenderWindow& window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();


}


void Render(RenderWindow& window) {
	// Draw everything
	window.draw(invader);
}


int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	Load();
	Reset();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}