#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


const int gameWidth = 100;
const int gameHeight = 100;




void Load() {

}


void Reset() {

}

sf::CircleShape circle;

void Update(RenderWindow& window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();

	circle = sf::CircleShape(10.f);
	circle.setPosition(10, 10);
	circle.setFillColor(sf::Color(255, 255, 0));
}


void Render(RenderWindow& window) {
	// Draw everything
	//window.draw(paddles[0]);
	window.draw(circle);
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