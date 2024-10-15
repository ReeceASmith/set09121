#include <iostream>
#include <array>
#include <utility>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "ship.h"
#include "bullet.h"

using namespace sf;
using namespace std;

const int spriteSizeSquarePx = 32;
int invaderRows = 6;
const int invaderColumns = 20;

const array<pair<int, int>, 6> invaderSprites = {{
	make_pair(0, 0),
	make_pair(1, 0),
	make_pair(2, 0),
	make_pair(3, 0),
	make_pair(4, 0),
	make_pair(5, 0)
}};


int numInvaderSprites = sizeof(invaderSprites) / sizeof(invaderSprites[0]);
float scaledRAND_MAX = RAND_MAX / numInvaderSprites;

// Grid needs to be larger than the number of sprites in a row
const float gridScale = .9f;
int invaderGridColumns = static_cast<int>(invaderColumns * gridScale);
int minWidthHeight = static_cast<int>(gridScale * fmin(gameWidth / invaderColumns, gameHeight / 2 / invaderRows));


sf::Texture spritesheet;
std::vector<Ship*> ships;



void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	int randomInvaderSprite;



	for (int i = 0; i < invaderRows * invaderColumns; i++) {
		randomInvaderSprite = static_cast<int>(rand() / scaledRAND_MAX);
		pair<int, int> thisInvaderSprite = invaderSprites[randomInvaderSprite];

		thisInvaderSprite.first *= spriteSizeSquarePx;
		thisInvaderSprite.second *= spriteSizeSquarePx;


		float posx = i % invaderColumns;
		posx *= minWidthHeight;
		float posy = floor(i / invaderColumns);
		posy *= minWidthHeight;

		posx += static_cast<int>(minWidthHeight / 2);
		posy += static_cast<int>(minWidthHeight / 2);


		Invader* toPushBack = new Invader(
			sf::IntRect(
				thisInvaderSprite.first,
				thisInvaderSprite.second,
				spriteSizeSquarePx,
				spriteSizeSquarePx
			),
			Vector2f(posx, posy)
		);


		toPushBack->setScale(minWidthHeight / static_cast<float>(spriteSizeSquarePx), minWidthHeight / static_cast<float>(spriteSizeSquarePx));

		ships.push_back(toPushBack);
	}


	// Load player
	ships.push_back(new Player());
	Bullet::Init();
}


void Reset() {
	Invader::speed = 40.f;
	Invader::direction = true;
}


void Update(RenderWindow& window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();


	for (auto& s : ships) {
		s->Update(dt);
	}

	Bullet::Update(dt);
}


void Render(RenderWindow& window) {
	// Draw everything
	for (const auto s : ships) {
		window.draw(*s);
	}
	Bullet::Render(window);
}


int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	Load();
	Reset();
	while (window.isOpen()) {
		// Event loop to handle closing and window focus, and game running
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close(); // Close window when "X" button is pressed
			}
		}
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}