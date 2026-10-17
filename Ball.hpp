#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Ball {
public:
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& centerBall);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollidable() const;
    // #Создаём конструктор
    Ball(const Point& centerBall, const Velocity& ballV, const Color& ballC, const double rad, bool Collidable); 

private: // #Объявляем переменные
    Point centerBall;
    Velocity ballV;
    Color ballC;
    const double rad;
    bool Collidable;
    const double mass;
};
