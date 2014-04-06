#ifndef INTERSECT_H
#define INTERSECT_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>


class Intersect
{
    public:
        Intersect();
        Intersect(sf::Vector2f intersect, float parameter);
        virtual ~Intersect();
        sf::Vector2f getIntersectPoint();
        float getParam();
        bool isValidIntersect();
        float getAngle();
        void setAngle(float angleIn);
    protected:
    private:
    sf::Vector2f intersectVec;
    float param;
    bool isValid;
    float angle;
};

#endif // INTERSECT_H
