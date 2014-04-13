#ifndef LIGHT_H
#define LIGHT_H
#include <string>
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
        Light(const std::string &lightName, const sf::Vector2f &initialPosition, const sf::Color &color, const float initailItensity);
        virtual ~Light();
        sf::Vector2f getVec();
        void setVec(const sf::Vector2f &lightVec);
        std::string getKey();
        sf::Color getColor();
        float getIntensity();
    protected:
    private:
    sf::Vector2f lightVector;
    sf::Color lightColor;
    std::string lightKey;
    float intensity;
};

#endif // LIGHT_H
