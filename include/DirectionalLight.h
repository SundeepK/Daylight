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
#include "ClosestIntersectionFinder.h"


struct IntersectComp : std::binary_function<Intersect, Intersect, bool>
{

    sf::Vector2f M;
    IntersectComp(sf::Vector2f v) : M(v) {}
    bool operator() ( Intersect vec1,  Intersect vec2)

    {
        sf::Vector2f o1 = vec1.getIntersectPoint();
        sf::Vector2f o2 = vec2.getIntersectPoint();

        float ang1     = atan( ((o1.y - M.y)/(o1.x - M.x) ) * M_PI / 180);
        float ang2     = atan( (o2.y - M.y)/(o2.x - M.x) * M_PI / 180);
        if(ang1 < ang2) return true;
        else if (ang1 > ang2) return false;

        return true;
    }
};


class DirectionalLight : public Light
{
public:
    DirectionalLight(const ClosestIntersectionFinder &intersectionFinder, const std::string &lightName, const sf::Vector2f &initialPosition, const sf::Color &color, const float initailItensity, const float angle, const float openAngle);
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
    bool isRayInFieldOfView(float facingAngle, float fieldOfViewAngle, sf::Vector2f ray );
    void addIntersect(const sf::VertexArray &ray, std::vector<sf::Vector2f> &shapeVectors, std::vector<Intersect> &intersects);
    void addFieldOfViewRay(sf::Vector2f rayLines, std::vector<sf::Vector2f> &shapeVectors, std::vector<Intersect> &intersects, const float angle);


    sf::VertexArray lightVertexArray;
    sf::VertexArray debugRays;
    sf::Vector2f lightVector;
    sf::Color lightColor;
    std::string lightKey;
    float intensity;
    float facingAngle;
    float fieldOfView;
    ClosestIntersectionFinder intersectFinder;

    std::vector<sf::Vector2f> directionalRays;
};

#endif // DIRECTIONALLIGHT_H
