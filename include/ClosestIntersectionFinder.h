#ifndef CLOSESTINTERSECTIONFINDER_H
#define CLOSESTINTERSECTIONFINDER_H

#include "IntersectFinder.h"
#include "VectorMath.h"

class ClosestIntersectionFinder : public IntersectFinder
{
    public:
        ClosestIntersectionFinder();
        virtual ~ClosestIntersectionFinder();
        std::vector<Intersect> findClosestIntersection(const sf::VertexArray &ray,  std::vector<sf::Vector2f> &shapeVectors, const float angle);


    protected:
    private:
};

#endif // CLOSESTINTERSECTIONFINDER_H
