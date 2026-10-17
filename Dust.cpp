#include "Painter.h"
#include "Point.h"
#include "Velocity.h"
#include "Color.h"
#include "Dust.h"

Dust::Dust(const Point& centerDust, const Velocity& dustV, const Color& dustC,double radD, double lifetime):
centerDust(centerDust), dustV(dustV), dustC(dustC), radD(radD), lifetime(lifetime){}

bool Dust::isAlive() const{
    return lifetime>0;
}

void Dust::update(double time){
    centerDust = centerDust + dustV.vector() * time;
    lifetime -= time;
}

void Dust::draw(Painter& painter) const{
    painter.draw(centerDust, radD, dustC);
}