#ifndef INTERSECTFINDER_H
#define INTERSECTFINDER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Intersect.h"


class IntersectFinder
{
    public:
        IntersectFinder();
        virtual ~IntersectFinder();
        virtual std::vector<Intersect> findClosestIntersection(const sf::VertexArray &ray,  std::vector<sf::Vector2f> &shapeVectors, const float angle)  = 0;

    protected:
    private:
};

#endif // INTERSECTFINDER_H
