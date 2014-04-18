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

Intersect VectorMath::getLineIntersect(sf::VertexArray ray, sf::VertexArray segment)
{
    // parametric line intersection
    //p1 + (p2-p1)T
    float r_px= ray[0].position.x;
    float r_py = ray[0].position.y;
    float r_dx = ray[1].position.x - ray[0].position.x;
    float r_dy = ray[1].position.y - ray[0].position.y;

    float s_px = segment[0].position.x;
    float s_py =segment[0].position.y;
    float s_dx = segment[1].position.x - segment[0].position.x;
    float s_dy =segment[1].position.y - segment[0].position.y;

    //parallel check

    sf::Vector2f normalRay = VectorMath::normalize(sf::Vector2f(r_dx, r_dy));
    sf::Vector2f normalSeg = VectorMath::normalize(sf::Vector2f(s_dx, s_dy));
    float dot = VectorMath::dot(normalRay, normalSeg);

    if(dot == 0)  // if they point in same direction, then theres no intersection
    {
        return  Intersect(sf::Vector2f(0,0), 0);
    }

    //get constant params
    float T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx);
    float T1 = (s_px+s_dx*T2-r_px)/r_dx;

    if(T1<0)
    {
        return Intersect(sf::Vector2f(0,0), 0);
    }
    if(T2<0 || T2>1)
    {
        return Intersect(sf::Vector2f(0,0), 0);
    }

    return Intersect(sf::Vector2f(r_px+r_dx*T1,r_py+r_dy*T1),T1);
}
