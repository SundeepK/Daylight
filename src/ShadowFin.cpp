#include "ShadowFin.h"

ShadowFin::ShadowFin(sf::Vector2f rootPoint)
    : rootVector(rootPoint)
{
    penumberIntensity = 1.0f;
    outerUmbra = 1.0f;
    depth = 1.0f;
    index = 1;
}

ShadowFin::~ShadowFin()
{

}

void ShadowFin::setInner(sf::Vector2f point)
{
    innerVector = point;
}

void ShadowFin::setOut(sf::Vector2f point)
{
    outerVector = point;
}

sf::Vector2f ShadowFin::getOuter()
{
    return outerVector;
}

sf::Vector2f ShadowFin::getInner()
{
    return innerVector;
}

int ShadowFin::getIndex()
{
    return index;
}

void ShadowFin::draw(sf::RenderTarget *App)
{
    //  sf::VertexArray vertextArray(sf::Triangles);
//    vertextArray.append(rootVector);
//    vertextArray.append(innerVector);
//    vertextArray.append(outerVector);
    sf::VertexArray vertextArray(sf::Triangles);
    sf::Color convexColor(sf::Color::Blue);
    vertextArray.append(sf::Vertex(rootVector,convexColor));
    vertextArray.append(sf::Vertex(innerVector,convexColor));
    vertextArray.append(sf::Vertex(outerVector,convexColor));
    std::cout << rootVector.x << std::endl;
    App->draw(vertextArray, sf::BlendMultiply);


}


void ShadowFin::setPenumberaIntensity(float value)
{
    penumberIntensity = value;
}
void ShadowFin::setUmberaIntensity(float value)
{
    outerUmbra = value;
}

void ShadowFin::setIndex(int value)
{
    index = value;
}

