#ifndef VECTORMATH_H
#define VECTORMATH_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>

class VectorMath
{
    public:
        VectorMath();
        virtual ~VectorMath();
        static float lenght(const sf::Vector2f vec);
        static sf::Vector2f normalize(sf::Vector2f vec);
        static float dot(sf::Vector2f point1, sf::Vector2f point2);
        float angle();
        sf::Vector2f getVector2f();
        void setVector2f(sf::Vector2f vec);
        void rotateVec(double radianAngle);
    protected:
    private:
    sf::Vector2f vectorWrapped;

};

#endif // VECTORMATH_H
