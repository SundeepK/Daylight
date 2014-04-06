#ifndef SHADOWFIN_H
#define SHADOWFIN_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
 #include <iostream>

class ShadowFin
{
    public:
        ShadowFin(sf::Vector2f rootVec);
        virtual ~ShadowFin();
        void setOut(sf::Vector2f point);
        void setInner(sf::Vector2f point);
        void setPenumberaIntensity(float value);
        void setUmberaIntensity(float value);
        void setIndex(int value);
        int getIndex();
        sf::Vector2f getOuter();
        sf::Vector2f getInner();
        void draw(sf::RenderTarget *App);

    protected:
    private:
    sf::Vector2f rootVector;
    sf::Vector2f innerVector;
    sf::Vector2f outerVector;
    float penumberIntensity;
    float outerUmbra;
    float depth;
    int index;



};

#endif // SHADOWFIN_H
