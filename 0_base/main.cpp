#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


const int gameWidth = 800;
const int gameHeight = 600;

Font font;
sf::CircleShape circle;

void Load() {
	// Load font-face from res dir
	if (!font.loadFromFile("res/fonts/RedHatText.ttf")) {
		printf("Error loading font\n");
		return;
	}

	// Load the rest
	circle = CircleShape::CircleShape(100.f);
	circle.setOrigin(50.f, 50.f);

}


void Reset() {
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(gameWidth / 2.f, gameHeight / 2.f);
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
}


void Render(RenderWindow& window) {
	// Draw everything
	window.draw(circle);
}


int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Base Template");

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