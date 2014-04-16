#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const std::string &lightName, const sf::Vector2f &initialPosition, const sf::Color &color, const float initailItensity, const float angle, const float openAngle)
       : Light(), lightKey(lightName), lightVector(initialPosition), lightColor(color), intensity(initailItensity), facingAngle(angle), openingAngle(openAngle)
{
}

DirectionalLight::~DirectionalLight()
{
}

sf::Vector2f DirectionalLight::getVec(){
}

void DirectionalLight::setVec(const sf::Vector2f &lightVec){
}

std::string DirectionalLight::getKey(){

}

sf::Color DirectionalLight::getColor(){

}

float DirectionalLight::getIntensity(){

}

void DirectionalLight::generateLight(std::vector<sf::Vector2f> &shapePoints, std::vector<float> &uniqueAngles){

}

void DirectionalLight::render(sf::RenderTarget &renderTarget, sf::RenderStates &renderState){

}
