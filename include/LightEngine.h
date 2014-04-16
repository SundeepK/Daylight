#ifndef LIGHTENGINE_H
#define LIGHTENGINE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <unordered_map>
#include "Light.h"
#include "SpotLight.h"
#include "Intersect.h"
#include <unordered_set>
#include <math.h>
#include "VectorMath.h"
#include <memory>
#include "DirectionalLight.h"


struct VectorHash {
    inline std::size_t operator()(const sf::Vector2f &v) const {
        return v.x*31+v.y;
    }
};

class LightEngine
{
    public:

        LightEngine(int width, int height, sf::Color);
        ~LightEngine();
        LightKey addLight(const std::string &key, const sf::Vector2f &lightVector, const sf::Color &lightColor, const float intensity);
        LightKey addDirectionLight(const std::string &key, const sf::Vector2f &lightVector, const sf::Color &lightColor, const float intensity, const float angleIn, const float openingAngle );

        void removeLight(const LightKey &lightKey);
        void setPosition(const LightKey &lightKey, const sf::Vector2f &newPosition);
        std::vector<LightKey> getLightKeys();
        void draw(sf::RenderWindow &renderWindow);
        void addShape(const sf::VertexArray &shape);
        void enableSoftShadow(bool shouldUseSoftShadow);
        void debugLightRays(bool shouldDebugLines);

    protected:
    private:

    Intersect getLineIntersect(sf::VertexArray ray, sf::VertexArray segment);
    void addUniquePoints(std::vector<sf::Vector2f> &shapePoints, std::unordered_set<sf::Vector2f, VectorHash> &points, sf::VertexArray vertextArray);
    void addPoints(std::vector<sf::Vector2f> &points, sf::VertexArray vertextArray);
    std::vector<float> getUniqueAngles(const sf::Vector2f &position);

    std::unordered_map<std::string, std::unique_ptr<Light>> lights;
    std::unordered_set<sf::Vector2f, VectorHash> shapePointsSet;
    std::vector<sf::Vector2f> uniquePoints;
    std::vector<sf::Vector2f> shapeVectors;

    bool shoulDebugLines = false;
    bool shouldUseSoftBlur = false;
    sf::Shader lightShader;
    sf::Shader blurShader;
    sf::RenderTexture lightRenderTex;
    sf::Color renderColor;

};

#endif // LIGHTENGINE_H
