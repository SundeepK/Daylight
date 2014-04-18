#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Intersect.h"
#include "VectorMath.h"
#include "Light.h"

class DirectionalLight : public Light
{
public:
    DirectionalLight(const std::string &lightName, const sf::Vector2f &initialPosition, const sf::Color &color, const float initailItensity, const float angle, const float openAngle);
    ~DirectionalLight();
    DirectionalLight(const DirectionalLight &that);
    DirectionalLight(DirectionalLight &&that);

    sf::Vector2f getVec() ;
    void setVec(const sf::Vector2f &lightVec) ;
    std::string getKey() ;
    sf::Color getColor() ;
    float getIntensity() ;
    void generateLight(std::vector<sf::Vector2f> &shapePoints, std::vector<float> &uniqueAngles) ;
    void render(sf::RenderTarget &renderTarget, sf::RenderStates &renderState) ;

protected:
private:
    static bool compareIntersects(Intersect vec1, Intersect vec2);
    std::vector<Intersect> getIntersectPoints( std::vector<sf::Vector2f> &shapeVectors, const std::vector<float> &uniqueAngles);
    void buildLightRays(std::vector<sf::Vector2f> &lightRays);
    Intersect getIntersect(std::vector<sf::Vector2f> &shapeVectors,  sf::VertexArray ray);
    sf::VertexArray lightVertexArray;
    sf::VertexArray debugRays;
    sf::Vector2f lightVector;
    sf::Color lightColor;
    std::string lightKey;
    float intensity;
    float facingAngle;
    float openingAngle;

    std::vector<sf::Vector2f> directionalRays;
};

#endif // DIRECTIONALLIGHT_H
