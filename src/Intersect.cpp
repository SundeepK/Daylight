#include "Intersect.h"

Intersect::Intersect(sf::Vector2f intersect, float parameter)
    : intersectVec(intersect), param(parameter), isValid(true)
{
}

Intersect::Intersect()
{
}


Intersect::~Intersect()
{
}

bool Intersect::isValidIntersect(){
    std::cout << isValid << std::endl;
    return isValid;
}

sf::Vector2f Intersect::getIntersectPoint(){
    return intersectVec;
}

float Intersect::getParam(){
    return param;
}

float Intersect::getAngle(){
    return angle;
}

void Intersect::setAngle(float angleIn){
    angle = angleIn;
}
