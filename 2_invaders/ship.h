#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
	protected:
		sf::IntRect _sprite;
		bool _exploded = false;
		bool _alive = true;
		// Default constructor is hidden
		Ship();
	public:
		static float ExplodeTime;
		float sinceExploded = 0.f;
		// Constructor that takes a sprite
		explicit Ship(sf::IntRect ir);
		// Pure virtual deconstructor - makes this an abstract class and avoid undefined behaviour!
		virtual ~Ship() = 0;
		// Explode bool
		bool is_exploded() const;
		bool is_alive() const;
		void kill();
		// Explode - virtual so it can be overridden per player/invader
		virtual void Explode();
		// Update - virtual so it can be overridden, but not pure virtual
		virtual void Update(const float& dt);
};


class Invader : public Ship {
	public:
		static bool direction;
		static float speed;
		static float bulletCooldownSeconds;
		static float dtSinceLastFired;

		Invader(sf::IntRect ir, sf::Vector2f pos);
		Invader();
		void Update(const float& dt) override;
};


class Player : public Ship {
	private:
		float playerSpeed = 120.f;
		static float bulletCooldownSeconds;
		float dtSinceLastFired;
	public:
		Player();
		void Update(const float& dt) override;
};