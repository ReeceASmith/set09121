#include "game.h"
#include "ship.h"
#include "bullet.h"
using namespace sf;
using namespace std;

bool Invader::direction;
float Invader::speed;
float Player::bulletCooldownSeconds = 0.8f;
float Invader::bulletCooldownSeconds = 1.f;
float Ship::ExplodeTime = .2f;
float Invader::dtSinceLastFired = 0.f;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

bool Ship::is_exploded() const {
	return _exploded;
}

bool Ship::is_alive() const {
	return _alive;
}

void Ship::Kill() {
	_exploded = true;
	_alive = false;
}

void Ship::Reset() {
	_exploded = false;
	_alive = true;
}

void Ship::Explode() {
	setTextureRect(IntRect(Vector2(128, 32), Vector2(32, 32)));
	_exploded = true;
}

void Ship::Update(const float& dt) {
	if (is_exploded()) {
		sinceExploded += dt;
		if (sinceExploded >= Ship::ExplodeTime) {
			Kill();
		}
	}
}

// Define the ship deconstructor
// Although we set this to pure virtual, we still have to define it
Ship::~Ship() = default;


Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	textureIntRect = Vector2(ir.getPosition().x, ir.getPosition().y);
	setOrigin(Vector2f(16.f, 16.f));
	setPosition(pos);
}

void Invader::Reset() {
	Ship::Reset();

	setTextureRect(IntRect(textureIntRect, Vector2(32, 32)));
	dtSinceLastFired = 0.f;
}

void Invader::Update(const float& dt) {
	Ship::Update(dt);

	Invader::dtSinceLastFired += dt / (invaders_columns * invaders_rows);


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

	if (Invader::dtSinceLastFired >= (Invader::bulletCooldownSeconds) && rand() % (invaders_rows * invaders_columns * 10000000000000000) == 0) {
		Bullet::Fire(getPosition(), true);
		Invader::dtSinceLastFired = 0.f;
	}
}


Player::Player() : Ship(IntRect(Vector2(160, 32), Vector2(32, 32))) {
	Player::Reset();
}

void Player::Reset() {
	Ship::Reset();

	setTextureRect(IntRect(Vector2(160, 32), Vector2(32, 32)));
	setPosition({ gameWidth * .5f, gameHeight - 32.f });
	dtSinceLastFired = 0.f;
}

void Player::Update(const float& dt) {
	Ship::Update(dt);
	
	static vector<Bullet*> bullets;
	dtSinceLastFired += dt;


	// Move left
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		move(Vector2f(-playerSpeed * dt, 0));
	}
	// Move right
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		move(Vector2f(playerSpeed * dt, 0));
	}

	// Check we are trying to fire and the cooldown time has passed
	if (Keyboard::isKeyPressed(Keyboard::Space)
		&& dtSinceLastFired >= Player::bulletCooldownSeconds)
	{
		// Reset cooldown
		Bullet::Fire(getPosition(), false);
		dtSinceLastFired = 0.f;
	}

	for (const auto b : bullets) {
		b->Update(dt);
	}
}