#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;
using namespace std;


const int gameWidth = 800;
const int gameHeight = 600;

Font font;
unique_ptr<Player> player;


void Load() {
	// Load font-face from res dir
	if (!font.loadFromFile("res/fonts/RedHatText.ttf")) {
		printf("Error loading font\n");
		return;
	}

	// Load the rest
	player = make_unique<Player>();
}


void Reset() {
	player.get()->setPosition(Vector2f(gameWidth / 2.f, gameHeight / 2.f));
}


void Update(RenderWindow& window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();

	// Check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	player.get()->Update(dt);
}


void Render(RenderWindow& window) {
	// Draw everything
	player.get()->Render(window);
}


int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Tile Engine");

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