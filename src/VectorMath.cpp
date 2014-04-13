#include "VectorMath.h"

VectorMath::VectorMath()
{
    //ctor
}

VectorMath::~VectorMath()
{
    //dtor
}


float VectorMath::lenght(const sf::Vector2f vec){
   return (float) (sqrt(vec.x*vec.x) + (vec.y*vec.y));
}

sf::Vector2f VectorMath::normalize(sf::Vector2f vec){
    float length = lenght(vec);
    float invLength = 1.0f / length;
    vec.x = vec.x * invLength;
    vec.y = vec.y * invLength;
    return vec;
}

float VectorMath::dot(sf::Vector2f point1, sf::Vector2f point2){
    return point1.x * point2.x + point1.y * point2.y;

}
