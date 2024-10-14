#include "ship.h"
#include "game.h"
using namespace sf;
using namespace std;

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