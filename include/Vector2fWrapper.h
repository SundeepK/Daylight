#ifndef VECTOR2FWRAPPER_H
#define VECTOR2FWRAPPER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>

class Vector2fWrapper
{
    public:
        Vector2fWrapper(sf::Vector2f vec);
        virtual ~Vector2fWrapper();

        float lenght();
        void normalize();
        float dot(sf::Vector2f point2);
        float angle();
        sf::Vector2f getVector2f();
        void setVector2f(sf::Vector2f vec);
        void rotateVec(double radianAngle);
    protected:
    private:
    sf::Vector2f vectorWrapped;
};

#endif // VECTOR2FWRAPPER_H
