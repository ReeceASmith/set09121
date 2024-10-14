#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;



void Load() {

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
	//window.draw(paddles[0]);
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