#include "Vector2fWrapper.h"

Vector2fWrapper::Vector2fWrapper(sf::Vector2f vec)
    :vectorWrapped(vec)
{
}

Vector2fWrapper::~Vector2fWrapper()
{
}

void Vector2fWrapper::normalize(){
    float length = lenght();
            float invLength = 1.0f / length;
    vectorWrapped.x = vectorWrapped.x * invLength;
    vectorWrapped.y = vectorWrapped.y * invLength;
}

float Vector2fWrapper::lenght(){
   return (float) (sqrt(vectorWrapped.x*vectorWrapped.x) + (vectorWrapped.y*vectorWrapped.y));
}

float Vector2fWrapper::dot(sf::Vector2f point2){
    return vectorWrapped.x * point2.x + vectorWrapped.y * point2.y;
}

float Vector2fWrapper::angle(){
    return atan2(vectorWrapped.y, vectorWrapped.x);
}

sf::Vector2f Vector2fWrapper::getVector2f(){
    return vectorWrapped;
}

void Vector2fWrapper::setVector2f(sf::Vector2f vec){
    vectorWrapped.x = vec.x;
        vectorWrapped.y = vec.y;

}

void Vector2fWrapper::rotateVec(double radianAngle){
    float hypo = lenght();
    if(vectorWrapped.y != 0){
        double val =vectorWrapped.y/hypo >= 1 ? 1 : vectorWrapped.y/hypo;
        radianAngle += asin(val);
    }else if(vectorWrapped.x != 0){
            double val =vectorWrapped.y/hypo > 1 ? 1 : vectorWrapped.y/hypo;

        radianAngle += (float) acos(val);
    }else{
        vectorWrapped.x = 0;
        vectorWrapped.y=0;
        return;
    }

    vectorWrapped.x = hypo * cos(radianAngle);
    vectorWrapped.y = hypo * sin(radianAngle);

}
