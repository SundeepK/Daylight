#ifndef LIGHT_H
#define LIGHT_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct LightKey
{
    public:
    LightKey (std::string key) : lightKey(key){}

    std::string key() const { return lightKey; }
    private:
    std::string lightKey;
};

class Light
{
    public:
        Light();
        virtual ~Light();
        virtual void generateLight(std::vector<sf::Vector2f> &shapePoints, std::vector<float> &uniqueAngles) = 0;
        virtual void render(sf::RenderTarget &renderTarget, sf::RenderStates &renderState) = 0;
        virtual sf::Vector2f getVec()  = 0;
        virtual void setVec(const sf::Vector2f &lightVec) = 0;
        virtual std::string getKey()  = 0;
        virtual sf::Color getColor()  = 0;
        virtual float getIntensity()  = 0;
        bool shouldDebugLines = false;

    protected:
    private:
};

#endif // LIGHT_H
