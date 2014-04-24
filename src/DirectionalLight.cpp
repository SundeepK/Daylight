#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const ClosestIntersectionFinder &intersectionFinder,const std::string &lightName, const sf::Vector2f &initialPosition,
        const sf::Color &color, const float initailItensity, const float angleIn, const float openAngle, const bool isDynamic)
    : Light(), intersectFinder(intersectionFinder), lightKey(lightName), lightVector(initialPosition), lightColor(color), intensity(initailItensity), facingAngle(angleIn), fieldOfView(openAngle), isDynamicLight(isDynamic)
{
    buildLightRays(directionalRays);
}

void DirectionalLight::buildLightRays(std::vector<sf::Vector2f> &lightRays)
{

    float fangle     = facingAngle * M_PI / 180;
    float offsetAngle   = fieldOfView * M_PI / 180;
    //float radius = 200; TODO use a radius value

    lightRays.clear();
    float endAngle = fangle+offsetAngle/2;

    directionalRays.push_back(sf::Vector2f(lightVector.x + cos((fangle-offsetAngle/2)) ,lightVector.y + sin((fangle-offsetAngle/2))));
    directionalRays.push_back(sf::Vector2f(lightVector.x + cos(endAngle) ,lightVector.y + sin(endAngle)));

}


DirectionalLight::~DirectionalLight()
{
}


sf::Vector2f DirectionalLight::getVec()
{
    return lightVector;
}


std::string DirectionalLight::getKey()
{
    return lightKey;
}

void DirectionalLight::setVec(const sf::Vector2f &lightVec)
{
    lightVector = lightVec;
    buildLightRays(directionalRays);
}

sf::Color DirectionalLight::getColor()
{
    return lightColor;
}

float DirectionalLight::getIntensity()
{
    return intensity;
}

bool DirectionalLight::isRayInFieldOfView(float facingAngle, float fieldOfViewAngle, sf::Vector2f ray ){

        sf::Vector2f lightDir ( cos(facingAngle), sin(facingAngle) );
        sf::Vector2f normalRay = VectorMath::normalize(sf::Vector2f (ray.x - lightVector.x, ray.y - lightVector.y  ) );
        sf::Vector2f normalLightDir = VectorMath::normalize(lightDir);

        float a = acos((normalRay.x * normalLightDir.x) + (normalRay.y * normalLightDir.y));
        return a  < fieldOfViewAngle;

}

std::vector<Intersect> DirectionalLight::getIntersectPoints( std::vector<sf::Vector2f> &shapeVectors, const std::vector<float> &uniqueAngles)
{
    std::vector<Intersect> intersects;
    float fangle     = facingAngle * M_PI / 180;
    float offsetAngle   = fieldOfView * M_PI / 180;

    for(int uniqueAngleIndex=0; uniqueAngleIndex < uniqueAngles.size(); uniqueAngleIndex++)
    {
        float angle = uniqueAngles[uniqueAngleIndex];
        float x = cos(angle);
        float y = sin(angle);

        sf::Vector2f lightVectorToEdge(lightVector.x + x,lightVector.y + y);
        sf::VertexArray ray(sf::Lines);
        ray.append(sf::Vertex(lightVector, sf::Color::Black));
        ray.append(sf::Vertex(lightVectorToEdge, sf::Color::Black));

        if(isRayInFieldOfView(fangle, offsetAngle, lightVectorToEdge)){
           std::vector<Intersect> closestIntersections = intersectFinder.findClosestIntersection(ray,shapeVectors, angle);
           intersects.insert(intersects.end(), closestIntersections.begin(), closestIntersections.end());
        }
    }

    //add the start ray for the directional light, this is the angle the direction light is pointing in minus openingAngle/2
    addFieldOfViewRay(directionalRays[0], shapeVectors, intersects, (fangle-offsetAngle/2));
    //add the end ray for directional light, this is the angle the direction light is pointing in plus openingAngle/2
    addFieldOfViewRay(directionalRays[directionalRays.size()-1], shapeVectors, intersects, (fangle+offsetAngle/2));

    std::sort(intersects.begin(), intersects.end(), IntersectComp(lightVector));
    return intersects;
}

void DirectionalLight::addFieldOfViewRay(sf::Vector2f rayLines, std::vector<sf::Vector2f> &shapeVectors, std::vector<Intersect> &intersects, const float angle){
        sf::VertexArray ray(sf::Lines);
        ray.append(sf::Vertex(lightVector, sf::Color::Black));
        ray.append(sf::Vertex(rayLines, sf::Color::Black));
        std::vector<Intersect> closestIntersections = intersectFinder.findClosestIntersection(ray,shapeVectors, angle);
        intersects.insert(intersects.end(), closestIntersections.begin(), closestIntersections.end());
}

void DirectionalLight::generateLight(std::vector<sf::Vector2f> &shapePoints, std::vector<float> &uniqueAngles)
{
    if(!isDynamicLight && !hasGeneratedLightBefore){
      generateLightRays(shapePoints,uniqueAngles );
      hasGeneratedLightBefore = true;
    }else if(isDynamicLight){
      generateLightRays(shapePoints,uniqueAngles );
    }
}

void DirectionalLight::generateLightRays(std::vector<sf::Vector2f> &shapePoints, std::vector<float> &uniqueAngles){
    std::vector<Intersect> intersects = getIntersectPoints(shapePoints,uniqueAngles);
    sf::VertexArray lightRays(sf::TrianglesFan);
    sf::VertexArray debugLightRays(sf::Lines);
    buildLightRayVertexes(lightRays, debugLightRays, intersects);

    lightVertexArray.clear();
    lightVertexArray = lightRays;

    if(shouldDebugLines)
    {
        debugRays = debugLightRays;
    }
}

void DirectionalLight::buildLightRayVertexes(sf::VertexArray &rayLine, sf::VertexArray &debugLightRays,  std::vector<Intersect> &intersects)
{
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

void DirectionalLight::render(sf::RenderTarget &target, sf::RenderStates &renderState)
{

    target.draw(lightVertexArray, renderState);

    if(shouldDebugLines)
    {
        target.draw(debugRays);
    }

}
