#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
	public:
		// Updates bullets in the pool
		static void Update(const float& dt);
		// Renders bullets in the pool
		static void Render(sf::RenderWindow& window);
		// Uses the oldest bullet
		static void Fire(const sf::Vector2f& pos, const bool enemyBullet);
		// Set all bullets to -100, -100, set the spritesheet, set the origin
		//	(Common setup steps for all bullets - we don't need to specify position, direction or the specific sprite yet)
		static void Init();
		Bullet(const sf::Vector2f& pos, const bool enemyBullet);
		~Bullet() = default;
	protected:
		static unsigned char bulletPointer;
		static Bullet bullets[256];
		// Called by static Update()
		void _Update(const float& dt);
		// Never called by our code
		Bullet();
		// False = player, true = enemy
		bool _enemyBullet;
};