#include "SpotLight.h"

SpotLight::SpotLight(const std::string &lightName, const sf::Vector2f &initialPosition, const sf::Color &color, const float initialItensity)
    : Light(), lightKey(lightName), lightVector(initialPosition), lightColor(color), intensity(initialItensity)
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
    lightVector = lightVec;
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

        Intersect closestInterect(sf::Vector2f(799,799), 1000);
        for(int i = 0 ;  i < shapeVectors.size(); i+=2)
        {
            sf::Vector2f seg1 =shapeVectors[i];
            sf::Vector2f seg2 =shapeVectors[i+1];
            sf::VertexArray segLine(sf::Lines);
            segLine.append(seg1);
            segLine.append(seg2);
            Intersect intersect =  VectorMath::getLineIntersect(ray, segLine);

            if(intersect.getIntersectPoint().x > 0 && intersect.getIntersectPoint().y > 0)
            {
                //add only the intersect with the smallest magnitude since it will be closest intersect
                if(intersect.getParam() < closestInterect.getParam())
                {
                    closestInterect = intersect;
                }
            }

        }

        if(closestInterect.getParam() < 1000)
        {
            closestInterect.setAngle(angle);
            intersects.push_back(closestInterect);
        }
    }
    std::sort(intersects.begin(), intersects.end(), compareIntersects);
    return intersects;
}

void SpotLight::generateLight(std::vector<sf::Vector2f> &shapePoints, std::vector<float> &uniqueAngles)
{

    std::vector<Intersect> intersects = getIntersectPoints(shapePoints,uniqueAngles);
    sf::VertexArray rayLine(sf::TrianglesFan);
    rayLine.append(sf::Vertex(lightVector, sf::Color::White));
    sf::VertexArray rays(sf::Lines);

    for(int i = 0; i < intersects.size(); i++)
    {
        rayLine.append(sf::Vertex(intersects[i].getIntersectPoint(), sf::Color::White));

        if(shouldDebugLines)
        {
            rays.append(sf::Vertex(lightVector, sf::Color::Red));
            rays.append(sf::Vertex(intersects[i].getIntersectPoint(), sf::Color::Red));
        }
    }

    rayLine.append(sf::Vertex(intersects[0].getIntersectPoint(),  sf::Color::White));
    lightVertexArray = rayLine;
    if(shouldDebugLines){
        debugRays = rays;
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
