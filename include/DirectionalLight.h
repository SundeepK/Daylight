#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Intersect.h"
#include "VectorMath.h"
#include "Light.h"
#include <math.h>


struct IntersectComp : std::binary_function<Intersect, Intersect, bool>
    {
    IntersectComp(sf::Vector2f v) : M(v) {}
    bool operator() ( Intersect vec1,  Intersect vec2) {

    sf::Vector2f o1 = vec1.getIntersectPoint();
    sf::Vector2f o2 = vec2.getIntersectPoint();

    double angle1 = atan2(o1.y - M.y, o1.x - M.x);
    double angle2 = atan2(o2.y - M.y, o2.x - M.x);

     float ang1     = atan( ((o1.y - M.y)/(o1.x - M.x) ) * M_PI / 180);
     float ang2     = atan( (o2.y - M.y)/(o2.x - M.x) * M_PI / 180);
        if(ang1 < ang2) return true;
        else if (ang1 > ang2) return false;
        return true;


    }
    sf::Vector2f M;
    };


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
