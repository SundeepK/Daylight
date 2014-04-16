#include "LightEngine.h"

LightEngine::LightEngine(int width, int height, sf::Color engCol) : renderColor(engCol)
{
    blurShader.loadFromFile("shaders/blur_x.frag", sf::Shader::Fragment);
    blurShader.loadFromFile("shaders/blur_y.frag", sf::Shader::Fragment);

    lightShader.loadFromFile("shaders/lightFs.frag", sf::Shader::Fragment);
    lightShader.setParameter("texture", sf::Shader::CurrentTexture);
    lightShader.setParameter("screenHeight",height);

    lightRenderTex.create(width,height);
}

LightEngine::~LightEngine()
{
    lights.clear();
}


void LightEngine::addPoints(std::vector<sf::Vector2f> &points, sf::VertexArray vertextArray)
{
    for(int  i = 0 ; i < vertextArray.getVertexCount() ; i ++)
    {
        points.push_back(vertextArray[i].position);
    }
}


void LightEngine::addUniquePoints(std::vector<sf::Vector2f> &shapePoints, std::unordered_set<sf::Vector2f, VectorHash> &points, sf::VertexArray vertextArray)
{
    for(int  i = 0 ; i < vertextArray.getVertexCount() ; i ++)
    {
        const bool is_in = points.find(vertextArray[i].position) != points.end();
        if(!is_in)
        {
            shapePoints.push_back(vertextArray[i].position);
            points.insert(vertextArray[i].position);
        }
    }
}


void LightEngine::addShape(const sf::VertexArray &shape)
{
    addUniquePoints(uniquePoints,shapePointsSet, shape);
    addPoints(shapeVectors, shape);
}

std::vector<float> LightEngine::getUniqueAngles(const sf::Vector2f &position)
{
    std::vector<float> uniqueAngles;
    for(int  i  = 0 ; i  < uniquePoints.size(); i++)
    {
        sf::Vector2f point = uniquePoints[i];
        float angle = atan2(point.y - position.y, point.x - position.x);
        uniqueAngles.push_back((angle-0.0001f));
        uniqueAngles.push_back(angle);
        uniqueAngles.push_back((angle+0.0001f));
    }
    return uniqueAngles;
}


void LightEngine::draw(sf::RenderWindow &renderWindow)
{

    lightRenderTex.clear(renderColor);
    sf::RenderStates r1(sf::BlendAdd);
    r1.shader = &lightShader;

    for ( auto lightIterator = lights.begin(); lightIterator!= lights.end(); ++lightIterator )
    {

     //    std::unique_ptr<Light> light(std::move(lightIterator->second));
        sf::Color lightColor = lightIterator->second->getColor();
        lightShader.setParameter("lightpos",lightIterator->second->getVec());
        lightShader.setParameter("lightColor", sf::Vector3f(lightColor.r, lightColor.g, lightColor.b));
        lightShader.setParameter("intensity", lightIterator->second->getIntensity());

        std::vector<float> angles = getUniqueAngles(lightIterator->second->getVec());

         if(shoulDebugLines){
           // light.shouldDebugLines = true;
        }

        lightIterator->second->generateLight(shapeVectors,angles);
        lightIterator->second->render(lightRenderTex, r1);

    }

    lightRenderTex.display();

    sf::RenderStates r(sf::BlendMultiply);

    if(shouldUseSoftBlur){
        r.shader = &blurShader;
    }

    renderWindow.draw(sf::Sprite (lightRenderTex.getTexture()), r);

}


LightKey LightEngine::addLight(const std::string &key, const sf::Vector2f &lightVector, const sf::Color &lightColor, const float intensity)
{
    auto it = lights.find(key);
//    if( it != lights.end() )
//    {
//        std::unique_ptr<Light> light( new SpotLight(key, lightVector, lightColor, intensity));
        lights.emplace(std::make_pair(key,  std::unique_ptr<Light> ( new SpotLight(key, lightVector, lightColor, intensity))));
//    }

    return LightKey(key);
}

void LightEngine::removeLight(const LightKey &lightKey)
{

}

void LightEngine::setPosition(const LightKey &lightKey, const sf::Vector2f &newPosition)
{
    std::unordered_map<std::string,std::unique_ptr<Light>>::iterator got = lights.find (lightKey.key());
    if (!(got == lights.end()) )
    {
        std::unique_ptr<Light> light(std::move(got->second));
        light->setVec(newPosition);
         got->second = std::move(light);
    }
    int i = 0;

}

void LightEngine::debugLightRays(bool debugLines){
    shoulDebugLines = debugLines;
}

void LightEngine::enableSoftShadow(bool shouldUseSoftShadow){
    shouldUseSoftBlur = shouldUseSoftShadow;
}



