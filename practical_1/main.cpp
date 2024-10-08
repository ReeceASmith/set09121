#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A,	// Player1 Up
	Keyboard::Z,	// Player1 Down
	Keyboard::Up,	// Player2 Up
	Keyboard::Down	// Player2 Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;

CircleShape ball;
RectangleShape paddles[2];


void Load() {
	// Set size and origin of paddles
	for (auto& p : paddles) {
		p.setSize(paddleSize);
		p.setOrigin(paddleSize / 2.f);
	}
	// Set size and origin of balls
	ball.setRadius(ballRadius);
	ball.setOrigin(Vector2f(ballRadius / 2.f, ballRadius / 2.f));
	// Reset paddle position
	paddles[0].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
	paddles[1].setPosition(Vector2f(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f));
	// Reset ball position
	ball.setPosition(gameHeight / 2.f, gameWidth / 2.f);
}