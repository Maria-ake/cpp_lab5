#include "Ball.hpp"
#include <cmath>
Ball::Ball(const Point& centerBall, const Velocity& ballV, const Color& ballC,
     const double rad, bool Collidable): 
     centerBall(centerBall), ballV(ballV), ballC(ballC), rad(rad), Collidable(Collidable), mass(M_PI*std::pow(rad, 3)*4./3.){}


/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    ballV = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return ballV; // #Возращаем скорость
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(centerBall, rad, ballC);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    centerBall = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
     return centerBall; // #Возращаем центр
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
     return rad; // #Возращаем радиус
}

bool Ball::isCollidable()  const {
     return Collidable; // #Возращаем радиус
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return mass; // #Возращаем массу
}
