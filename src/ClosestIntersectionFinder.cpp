#include "ClosestIntersectionFinder.h"

ClosestIntersectionFinder::ClosestIntersectionFinder() : IntersectFinder()
{
}

ClosestIntersectionFinder::~ClosestIntersectionFinder()
{
}

std::vector<Intersect> ClosestIntersectionFinder::findClosestIntersection(const sf::VertexArray &ray,  std::vector<sf::Vector2f> &shapeVectors, const float angle){

    Intersect closestInterect(sf::Vector2f(799,799), 1000);
    std::vector<Intersect> intersects;
    for(int i = 0 ;  i < shapeVectors.size(); i+=2)
    {
        sf::Vector2f seg1 =shapeVectors[i];
        sf::Vector2f seg2 =shapeVectors[i+1];
        sf::VertexArray segLine(sf::Lines);
        segLine.append(seg1);
        segLine.append(seg2);
        Intersect intersect =  VectorMath::getLineIntersect(ray, segLine);

        if(intersect.getIntersectPoint().x > 0 && intersect.getIntersectPoint().y > 0)
        {
            if(intersect.getParam() < closestInterect.getParam())
            {
                closestInterect = intersect;
            }
        }
    }

    if(closestInterect.getParam() < 1000)
    {
        closestInterect.setAngle(angle);
        intersects.push_back(closestInterect);
    }

    return intersects;
}

