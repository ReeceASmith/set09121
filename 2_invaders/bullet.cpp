#include "bullet.h"
#include "game.h"

using namespace sf;
using namespace std;

unsigned char Bullet::bulletPointer = 0;
Bullet Bullet::bullets[256];


// Updates bullets in the pool
void Bullet::Update(const float& dt) {
	for (Bullet &b : bullets) {
		b._Update(dt);
	}
}

void Bullet::_Update(const float &dt) {
	if (getPosition().y < -32.f || getPosition().y > gameHeight + 32) {
		return;
	}
	else {
		move(Vector2f(0, dt * 200.f * (_enemyBullet ? 1.f : -1.f)));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			// Player/Invader bullets don't collide with players/invaders
			if ((s == player) == !_enemyBullet) {
				continue;
			}

			if (!s->is_exploded()
				&& s->getGlobalBounds().intersects(boundingBox))
			{
				s->Explode();
				setPosition(-100.f, -100.f);
				return;
			}
		}
	}


}

// Renders bullets in the pool
void Bullet::Render(sf::RenderWindow& window) {
	for (const auto& b : bullets) {
		window.draw(b);
	}
}

// Uses the oldest bullet
void Bullet::Fire(const sf::Vector2f& pos, const bool enemyBullet) {
	printf("Fire\n");
	Bullet& bullet = Bullet::bullets[++Bullet::bulletPointer];
	bullet.setPosition(Vector2f(pos.x + 26.f, pos.y));
	bullet.setTextureRect(IntRect((32 + 32*(enemyBullet ? 0 : 1))+10, 32, 10, 32));
	bullet._enemyBullet = enemyBullet;
}

// Set all bullets to -100, -100, set the spritesheet, set the origin
//	(Common setup steps for all bullets - we don't need to specify position, direction or the specific sprite yet)
void Bullet::Init() {
	for (auto& bullet : bullets) {
		bullet.setPosition(-100.f, -100.f);
		bullet.setTexture(spritesheet);
		bullet.setOrigin(16.f, 16.f);
	}
}

// Define the default constructor
Bullet::Bullet() : _enemyBullet(false) {
	// Initialize the bullet position to off-screen
	setPosition(-100.f, -100.f);
}

Bullet::Bullet(const sf::Vector2f& pos, const bool enemyBullet) {
	IntRect _sprite;
	if (enemyBullet) {
		_sprite = IntRect(32, 32, 32, 32);
	}
	else {
		_sprite = IntRect(64, 32, 32, 32);
	}
	setTexture(spritesheet);
	setTextureRect(_sprite);

	_enemyBullet = enemyBullet;
}