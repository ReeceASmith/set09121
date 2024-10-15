#include "ship.h"
#include "game.h"
using namespace sf;
using namespace std;

bool Invader::direction;
float Invader::speed;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

// Define the ship deconstructor
// Although we set this to pure virtual, we still have to define it
Ship::~Ship() = default;


Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(Vector2f(16.f, 16.f));
	setPosition(pos);
}

void Invader::Update(const float& dt) {
	Ship::Update(dt);

	move(Vector2f(
		dt
		* (direction ? 1.f : -1.f)
		* speed,
		0.f)
	);

	int thisSize = this->getGlobalBounds().getSize().x;
	if ((direction && getPosition().x > gameWidth - (thisSize / 3))
		|| (!direction && getPosition().x < (thisSize / 3)))
	{
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i) {
			if (auto invader = dynamic_cast<Invader*>(ships[i])) {
				invader->move(Vector2f(0.f, (thisSize / 3)));
			}
		}
	}
}


Player::Player() : Ship(IntRect(Vector2(160, 32), Vector2(32, 32))) {
	setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {
	Ship::Update(dt);


	// Move left
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		move(Vector2f(-playerSpeed * dt, 0));
	}
	// Move right
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		move(Vector2f(playerSpeed * dt, 0));
	}
}