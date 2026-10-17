#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"
#include "Color.h"

class Dust{
public:
    void draw(Painter& painter) const;
    void update(double time);
    bool isAlive() const;
    // #Создаём конструктор
    Dust(const Point& centerDust, const Velocity& dustV, const Color& dustC, const double radD, double lifetime); 

private: // #Объявляем переменные
    Point centerDust;
    Velocity dustV;
    Color dustC;
    double radD;
    double lifetime;
};