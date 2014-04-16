#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Intersect.h"
#include "VectorMath.h"
#include "Light.h"


class SpotLight : public Light
{
public:
    SpotLight(const std::string &lightName, const sf::Vector2f &initialPosition, const sf::Color &color, const float initailItensity);
    ~SpotLight();
    SpotLight(const SpotLight &that);
    SpotLight(SpotLight &&that);

    sf::Vector2f getVec() ;
    void setVec(const sf::Vector2f &lightVec) ;
    std::string getKey() ;
    sf::Color getColor() ;
    float getIntensity() ;
    void generateLight(std::vector<sf::Vector2f> &shapePoints, std::vector<float> &uniqueAngles) ;
    void render(sf::RenderTarget &renderTarget, sf::RenderStates &renderState) ;

    bool shouldDebugLines = false;

protected:
private:
    std::vector<Intersect> getIntersectPoints( std::vector<sf::Vector2f> &shapeVectors, const std::vector<float> &uniqueAngles);
    Intersect getLineIntersect(sf::VertexArray ray, sf::VertexArray segment);
    static bool compareIntersects(Intersect vec1, Intersect vec2);
    sf::VertexArray lightVertexArray;
    sf::VertexArray debugRays;
    sf::Vector2f lightVector;
    sf::Color lightColor;
    std::string lightKey;
    float intensity;
};

#endif // LIGHT_H
