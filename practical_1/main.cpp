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
const float paddleMaxY = gameHeight - paddleOffsetWall - paddleSize.y / 2.f;
const float paddleMinY = paddleOffsetWall + paddleSize.y / 2.f;

Vector2f ballVelocity;
bool isPlayer1Serving = true;
bool AIEnabled = true;
bool isPlayer1AI = true;
const float initialVelocityX = 200.f;
const float initialVelocityY = 120.f;
const float velocityMultiplier = 1.1f;
bool iKeyOn = false;
bool sKeyOn = false;

CircleShape ball;
RectangleShape paddles[2];
Font font;
Text pointsText;

int points[2] = { 0, 0 };


void Load() {
	// Set size and origin of paddles
	for (auto& p : paddles) {
		p.setSize(paddleSize);
		p.setOrigin(paddleSize / 2.f);
	}
	// Set size and origin of balls
	ball.setRadius(ballRadius);
	ball.setOrigin(sf::Vector2f(ballRadius / 2.f, ballRadius / 2.f));


	// Load font-face from res dir
	font.loadFromFile("res/fonts/RedHatText.ttf");
	// Set text element to use font
	pointsText.setFont(font);
	// Set character size to 24 pixels
	pointsText.setCharacterSize(24);
	pointsText.setColor(sf::Color(255, 255, 255, 255));

}


void Reset() {
	// Reset paddle position
	paddles[0].setPosition(sf::Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
	paddles[1].setPosition(sf::Vector2f(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f));
	// Reset ball position
	ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);
	ballVelocity = { (isPlayer1Serving ? initialVelocityX : -initialVelocityX), initialVelocityY };

	// Update score text
	pointsText.setString("Score: " + to_string(points[0]) + " | " + to_string(points[1]));
	// Keep score text centered
	pointsText.setPosition((gameWidth * .5f) - (pointsText.getLocalBounds().width * .5f), 10);
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

	// Quick via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}


	// Turn on AI
	if (Keyboard::isKeyPressed(Keyboard::I)) {
		if (!iKeyOn) {
			iKeyOn = true;
			AIEnabled = !AIEnabled;
		}
	}
	else if (iKeyOn) {
		iKeyOn = false;
	}

	// Swap AI player
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		if (!sKeyOn) {
			sKeyOn = true;
			isPlayer1AI = !isPlayer1AI;
		}
	}
	else if (sKeyOn) {
		sKeyOn = false;
	}


	// Handle paddle movement
	float direction1 = 0.f;
	float direction2 = 0.f;
	Vector2f paddlePosition[2] = { paddles[0].getPosition(), paddles[1].getPosition() };

	// If player 1 is a real person, or AI is not enabled
	if (!isPlayer1AI || !AIEnabled) {
		if (Keyboard::isKeyPressed(controls[0]))
		{
			direction1--;
		}
		if (Keyboard::isKeyPressed(controls[1]))
		{
			direction1++;
		}
	}
	if (isPlayer1AI || !AIEnabled) {
		if (Keyboard::isKeyPressed(controls[2]))
		{
			direction2--;
		}
		if (Keyboard::isKeyPressed(controls[3]))
		{
			direction2++;
		}
	}


	if (AIEnabled) {
		if (isPlayer1AI) {
			if (ball.getPosition().y < paddlePosition[0].y) {
				direction1 = -1.f;
			}
			else if (ball.getPosition().y > paddlePosition[0].y) {
				direction1 = 1.f;
			}
		}
		else {
			if (ball.getPosition().y < paddlePosition[1].y) {
				direction2 = -1.f;
			}
			else if (ball.getPosition().y > paddlePosition[1].y) {
				direction2 = 1.f;
			}
		}
	}

	paddles[0].move(sf::Vector2f(0.f, direction1 * paddleSpeed * dt));
	paddlePosition[0] = paddles[0].getPosition();
	paddles[0].setPosition(sf::Vector2f(paddlePosition[0].x, min(paddleMaxY, max(paddleMinY, paddlePosition[0].y))));

	paddles[1].move(sf::Vector2f(0.f, direction2 * paddleSpeed * dt));
	paddlePosition[1] = paddles[1].getPosition();
	paddles[1].setPosition(sf::Vector2f(paddlePosition[1].x, min(paddleMaxY, max(paddleMinY, paddlePosition[1].y))));




	// Move the ball
	ball.move(ballVelocity * dt);

	// Check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if ((by + ballRadius) > gameHeight) { // Bottom wall
		ballVelocity.x *= velocityMultiplier;
		ballVelocity.y *= -velocityMultiplier;
		ball.move(Vector2f(0.f, -10.f));
	}
	else if ((by - ballRadius) < 0) { // Top wall
		ballVelocity.x *= velocityMultiplier;
		ballVelocity.y *= -velocityMultiplier;
		ball.move(Vector2f(0.f, 10.f));
	}
	else if ((bx + ballRadius) > gameWidth) { // Right wall
		// Add point to player1 and set serve to player2
		points[0] += 1;
		isPlayer1Serving = false;
		// Reset
		Reset();
	}
	else if ((bx - ballRadius) < 0) { // Left wall
		// Add point to player2 and set serve to player1
		points[1] += 1;
		isPlayer1Serving = true;
		// Reset
		Reset();
	}
	else if (
		// Ball is inline or behind (left) paddle AND
		(bx - ballRadius) < paddleSize.x + paddleOffsetWall &&
		// Ball is below top edge of paddle AND
		by > paddlePosition[0].y - (paddleSize.y * 0.5) &&
		// Ball is above bottom edge of paddle
		by < paddlePosition[0].y + (paddleSize.y * 0.5)
		) {
		// Bounce off left paddle
		ballVelocity.x *= -1;
		ball.move(sf::Vector2f(5, 0));
	}
	else if (
		// Ball is inline or behind (right) paddle AND
		(bx + ballRadius) > gameWidth - paddleSize.x - paddleOffsetWall &&
		// Ball is below top edge of paddle AND
		by > paddlePosition[1].y - (paddleSize.y * 0.5) &&
		// Ball is above bottom edge of paddle
		by < paddlePosition[1].y + (paddleSize.y * 0.5)
		) {
		// Bounce off right paddle
		ballVelocity.x *= -1;
		ball.move(sf::Vector2f(-5, 0));
	}
}


void Render(RenderWindow& window) {
	// Draw everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(pointsText);
}


int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
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