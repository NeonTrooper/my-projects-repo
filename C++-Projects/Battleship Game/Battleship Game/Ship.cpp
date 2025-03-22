#include "Ship.h"
#include <iostream>

Ship::Ship(std::string type, unsigned size, int x, int y)
    : type(type), size(size), x(x), y(y), alive(true) {}

Ship::~Ship() {}

void Ship::setType(std::string type) {
    this->type = type;
}

std::string Ship::getType() const {
    return type;
}

void Ship::setSize(unsigned size) {
    this->size = size;
}

unsigned Ship::getSize() const {
    return size;
}

void Ship::setX(int x) {
    this->x = x;
}

int Ship::getX() const {
    return x;
}

void Ship::setY(int y) {
    this->y = y;
}

int Ship::getY() const {
    return y;
}

void Ship::setAlive(bool alive) {
    this->alive = alive;
}

bool Ship::isAlive() const {
    return alive;
}

void Ship::print() const {
    std::cout << "Ship type: " << type << ", Size: " << size << ", Position: (" << x << ", " << y << "), Alive: " << (alive ? "Yes" : "No") << std::endl;
}

bool Ship::checkHit(int hitX, int hitY) const {
    if (hitX >= x && hitX < x + size && hitY == y) {
        return true;
    }
    return false;
}
