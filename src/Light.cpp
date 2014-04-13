#include "Light.h"

Light::Light(const std::string &lightName, const sf::Vector2f &initialPosition, const sf::Color &color, const float initialItensity)
    : lightKey(lightName), lightVector(initialPosition), lightColor(color), intensity(initialItensity)
{
}

Light::~Light()
{
}

sf::Vector2f Light::getVec()
{
    return lightVector;
}


std::string Light::getKey()
{
    return lightKey;
}

void Light::setVec(const sf::Vector2f &lightVec)
{
    lightVector = lightVec;
}

sf::Color Light::getColor(){
    return lightColor;
}

float Light::getIntensity(){
    return intensity;
}
