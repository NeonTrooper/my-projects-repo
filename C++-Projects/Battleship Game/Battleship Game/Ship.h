#ifndef SHIP_H
#define SHIP_H

#include <string>

class Ship {
private:
    std::string type;
    unsigned size;
    int x;
    int y;
    bool alive;

public:
    Ship(std::string type, unsigned size, int x, int y);
    ~Ship();

    void setType(std::string type);
    std::string getType() const;

    void setSize(unsigned size);
    unsigned getSize() const;

    void setX(int x);
    int getX() const;

    void setY(int y);
    int getY() const;

    void setAlive(bool alive);
    bool isAlive() const;

    void print() const;
    bool checkHit(int hitX, int hitY) const;
};

#endif
