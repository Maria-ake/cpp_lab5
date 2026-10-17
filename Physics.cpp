#include "Physics.h"
#include <random>

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::update(std::vector<Ball>& balls,std::vector<Dust>& dusts, const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        collideWithBox(balls);
        collideBalls(balls, dusts);
    }
    // Обновляем каждую частицу пыли на каждом тике:
    // смещаем её координаты и уменьшаем время жизни
    for (Dust& dust : dusts) {
        dust.update(timePerTick);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust>& dusts) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        for (auto b = std::next(a); b != balls.end(); ++b) {
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if ((distanceBetweenCenters2 < collisionDistance2)&&a->isCollidable()&&b->isCollidable()){ //# Добавили сравнение
                processCollision(*a, *b, distanceBetweenCenters2, dusts);
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {

    for (Ball& ball : balls) {
        if (!ball.isCollidable()) continue; // #Пррверяем
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
        }
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2, std::vector<Dust>& dusts) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
    for (int i = 0; i < 20; ++i) {

        double lower = -100.0;
        double upper = 100.0;

    // Инициализируем криптографически нестойкий, но быстрый генератор случайных чисел
        std::random_device rd;
        std::mt19937 gen(rd());

    // Создаем равномерное распределение для вещественных чисел
        std::uniform_real_distribution<double> dis(lower, upper);

    // Генерируем число
        double random_x = dis(gen);
        double random_y = dis(gen);
        double random_cx = dis(gen);
        double random_cy = dis(gen);

    // Можем придумать небольшой случайный сдвиг для скорости
    Point dustCenterVector = a.getCenter() + Point(random_cx, random_cy);
    Point dustVelocityVector = a.getVelocity().vector() + Point(random_x, random_y);  
    // И вызываем push_back:
    dusts.push_back(Dust(dustCenterVector, Velocity(dustVelocityVector), Color(1, 0.8, 0), 10.0, 1));
}
}
