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
int invaderGridColumns = static_cast<int>(invaders_columns * gridScale);
int minWidthHeight = static_cast<int>(gridScale * fmin(gameWidth / invaders_columns, gameHeight / 2 / invaders_rows));


sf::Texture spritesheet;
std::vector<Ship*> ships;
Player* player;



void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	int randomInvaderSprite;



	for (int i = 0; i < invaders_rows * invaders_columns; i++) {
		randomInvaderSprite = static_cast<int>(rand() / scaledRAND_MAX);
		pair<int, int> thisInvaderSprite = invaderSprites[randomInvaderSprite];

		thisInvaderSprite.first *= spriteSizeSquarePx;
		thisInvaderSprite.second *= spriteSizeSquarePx;


		float posx = i % invaders_columns;
		posx *= minWidthHeight;
		float posy = floor(i / invaders_columns);
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
	player = new Player();
	ships.push_back(player);
	Bullet::Init();
}


void Reset() {
	Invader::speed = 40.f;
	Invader::direction = true;
	for (auto& s : ships) {
		s->Reset();
	}
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
		if (s->is_alive()) { window.draw(*s); }
	}
	Bullet::Render(window);
}


// True if the game is over
bool display_game_over(RenderWindow& window) {
	// Display game over
	Text gameOverText;
	Text continueText;
	Font font;
	if (!font.loadFromFile("res/fonts/RedHatText.ttf")) {
		cerr << "Failed to load font!" << std::endl;
	}
	gameOverText.setFont(font);
	gameOverText.setString("Game Over!");
	gameOverText.setCharacterSize(28);
	gameOverText.setFillColor(Color::White);
	gameOverText.setPosition(gameWidth / 2 - gameOverText.getGlobalBounds().width / 2, gameHeight / 2 - gameOverText.getGlobalBounds().height - 20);

	continueText.setFont(font);
	continueText.setString("Press [R] to restart, or [Q] to quit");
	continueText.setCharacterSize(20);
	continueText.setFillColor(Color::White);
	continueText.setPosition(gameWidth / 2 - continueText.getGlobalBounds().width / 2, gameHeight / 2 - continueText.getGlobalBounds().height + 20);

	bool ret = false;
	while (true) {
		window.clear();
		window.draw(gameOverText);
		window.draw(continueText);
		window.display();

		if (Keyboard::isKeyPressed(Keyboard::Q)) {
			ret = true;
			break;
		}
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			ret = false;
			break;
		}
	}
	printf("Reached\n");

	return ret;
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

		while (player->is_alive()) {
			window.clear();
			Update(window);
			Render(window);
			window.display();
		}

		if (!display_game_over(window)) {
			Reset();
		}
		else { break; }
	}



	return 0;
}