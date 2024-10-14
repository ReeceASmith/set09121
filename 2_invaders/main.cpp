#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


const int gameWidth = 100;
const int gameHeight = 100;


sf::Texture spritesheet;
sf::Sprite invader;



void Load() {
	cout << std::filesystem::current_path() << endl;
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));
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