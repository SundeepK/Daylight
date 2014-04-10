#ifndef LIGHTENGINE_H
#define LIGHTENGINE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <unordered_map>
#include "Light.h"
#include "Intersect.h"
#include <unordered_set>
#include <math.h>


struct VectorHash {
    inline std::size_t operator()(const sf::Vector2f &v) const {
        return v.x*31+v.y;
    }
};

class LightEngine
{
    public:

        LightEngine();
        virtual ~LightEngine();
        LightKey addLight(const std::string &key, const sf::Vector2f &lightVector, const sf::Color &lightColor);
        void removeLight(const LightKey &lightKey);
        void setPosition(const LightKey &lightKey, const sf::Vector2f &newPosition);
        std::vector<LightKey> getLightKeys();
        void debugLightRays(bool shouldDebugLines);
        void draw(sf::RenderWindow &renderWindow);
        void addShape(const sf::VertexArray &shape);

    protected:
    private:

    Intersect getLineIntersect(sf::VertexArray ray, sf::VertexArray segment);
    void addUniquePoints(std::vector<sf::Vector2f> &shapePoints, std::unordered_set<sf::Vector2f, VectorHash> &points, sf::VertexArray vertextArray);
    void addPoints(std::vector<sf::Vector2f> &points, sf::VertexArray vertextArray);
    std::vector<Intersect> getIntersectPoints(const std::vector<float> &uniqueAngles, const sf::Vector2f &point);
    std::vector<float> getUniqueAngles(const sf::Vector2f &position);

    bool shoulDebugLines = false;
    std::unordered_map<std::string, Light> lights;
    std::unordered_set<sf::Vector2f, VectorHash> shapePointsSet;
    std::vector<sf::Vector2f> uniquePoints;
    std::vector<sf::Vector2f> shapeVectors;
    sf::Shader shadowBlur;
    sf::RenderTexture lightRenderTex;
    float  offset;

};

#endif // LIGHTENGINE_H
