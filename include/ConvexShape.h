#ifndef CONVEXSHAPE_H
#define CONVEXSHAPE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include "Light.h"
#include "ShadowFin.h"
 #include <iostream>
 #include <algorithm>    // std::find



class ConvexShape
{
public:
        ConvexShape();
        ConvexShape(sf::VertexArray points, sf::Color colorToUse);
        ~ConvexShape();

        void drawShadows(Light &light, sf::RenderTarget *App);
        void draw(sf::RenderTarget *App);


protected:
private:
    sf::VertexArray shapePoints;
    sf::Color shapeColor;
    std::vector<sf::Vector2f> pointsC;
    sf::Vector2f getEdge(sf::Vector2f v1, sf::Vector2f v2);
    std::vector<ShadowFin> getShadowFins(Light lightOrigin, int indexOrigin, int step);
    sf::Vector2f getVectorFromIndex(int index);
    int getIntFromIndex(int index);


};

#endif // CONVEXSHAPE_H
