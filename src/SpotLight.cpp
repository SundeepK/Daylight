#include "SpotLight.h"

SpotLight::SpotLight(const ClosestIntersectionFinder &intersectionFinder,const std::string &lightName, const sf::Vector2f &initialPosition, const sf::Color &color, const float initialItensity, const bool isDynamic)
    : Light(), intersectFinder(intersectionFinder), lightKey(lightName), lightVector(initialPosition), lightColor(color), intensity(initialItensity), isDynamicLight(isDynamic)
{
}

SpotLight::~SpotLight()
{
}

SpotLight::SpotLight(const SpotLight &that){
         lightVertexArray = that.lightVertexArray;
         debugRays = that.debugRays;
         lightVector = that.lightVector;
         lightColor = that.lightColor;
         lightKey = that.lightKey;
         intensity = that.intensity;
}

SpotLight::SpotLight(SpotLight &&that) :  lightVertexArray (that.lightVertexArray),  debugRays(that.debugRays),  lightVector (that.lightVector),  lightColor (that.lightColor),
            lightKey (that.lightKey),   intensity (that.intensity)
{
}

sf::Vector2f SpotLight::getVec()
{
    return lightVector;
}


std::string SpotLight::getKey()
{
    return lightKey;
}

void SpotLight::setVec(const sf::Vector2f &lightVec)
{
    if(isDynamicLight){
        lightVector = lightVec;
    }
}

sf::Color SpotLight::getColor()
{
    return lightColor;
}

float SpotLight::getIntensity()
{
    return intensity;
}

bool SpotLight::compareIntersects(Intersect vec1, Intersect vec2)
{
    if(vec1.getAngle()  - vec2.getAngle() < 0)
    {
        return true;
    }
    else if (vec1.getAngle()  - vec2.getAngle() > 0)
    {
        return false;
    }

    return false;
}

std::vector<Intersect> SpotLight::getIntersectPoints( std::vector<sf::Vector2f> &shapeVectors, const std::vector<float> &uniqueAngles)
{
    std::vector<Intersect> intersects;
    for(int uniqueAngleIndex=0; uniqueAngleIndex < uniqueAngles.size(); uniqueAngleIndex++)
    {
        float angle = uniqueAngles[uniqueAngleIndex];
        float x = cos(angle);
        float y = sin(angle);

        sf::VertexArray ray(sf::Lines);
        ray.append(sf::Vertex(lightVector, sf::Color::Black));
        ray.append(sf::Vertex(sf::Vector2f(lightVector.x + x,lightVector.y + y), sf::Color::Black));

        std::vector<Intersect> closestIntersections = intersectFinder.findClosestIntersection(ray,shapeVectors, angle);
        intersects.insert(intersects.end(), closestIntersections.begin(), closestIntersections.end());
    }
    std::sort(intersects.begin(), intersects.end(), compareIntersects);
    return intersects;
}

bool SpotLight::shouldRenderLight(){
    bool shouldDrawLight;
    if(!isDynamicLight && !hasGeneratedLightBefore)
    {
        return true;
    }
    else if(isDynamicLight)
    {
        return true;
    }
    else{
        return false;
    }
}

void SpotLight::generateLight(std::vector<sf::Vector2f> &shapePoints, std::vector<float> &uniqueAngles)
{
    if(!isDynamicLight && !hasGeneratedLightBefore){
      generateLightRays(shapePoints,uniqueAngles );
      hasGeneratedLightBefore = true;
    }else if(isDynamicLight){
      generateLightRays(shapePoints,uniqueAngles );
    }
}

void SpotLight::generateLightRays(std::vector<sf::Vector2f> &shapePoints, std::vector<float> &uniqueAngles){
    std::vector<Intersect> intersects = getIntersectPoints(shapePoints,uniqueAngles);
    sf::VertexArray lightRays(sf::TrianglesFan);
    sf::VertexArray debugLightRays(sf::Lines);
    buildLightRayVertexes(lightRays, debugLightRays, intersects);
    lightRays.append(sf::Vertex(intersects[0].getIntersectPoint(),  sf::Color::White));
    lightVertexArray.clear();
    lightVertexArray = lightRays;

    if(shouldDebugLines)
    {
        debugRays = debugLightRays;
    }
}

void SpotLight::buildLightRayVertexes(sf::VertexArray &rayLine, sf::VertexArray &debugLightRays,  std::vector<Intersect> &intersects){
    rayLine.append(sf::Vertex(lightVector, sf::Color::White));
    for(int i = 0; i < intersects.size(); i++)
    {
        sf::Vector2f v = intersects[i].getIntersectPoint();
        rayLine.append(sf::Vertex(v, sf::Color::White));
        if(shouldDebugLines)
        {
            debugLightRays.append(sf::Vertex(lightVector, sf::Color::Red));
            debugLightRays.append(sf::Vertex(intersects[i].getIntersectPoint(), sf::Color::Red));
        }
    }
}


void SpotLight::render(sf::RenderTarget &target, sf::RenderStates &renderState)
{

    target.draw(lightVertexArray, renderState);

    if(shouldDebugLines)
    {
      target.draw(debugRays);
    }

}
