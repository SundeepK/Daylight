#include "LightEngine.h"

LightEngine::LightEngine()
{

//    shadowBlur.loadFromFile("shaders/blur_x.frag", sf::Shader::Fragment);
//    shadowBlur.loadFromFile("shaders/blur_y.frag", sf::Shader::Fragment);
    shadowBlur.loadFromFile("shaders/lightFs.frag", sf::Shader::Fragment);
    shadowBlur.setParameter("texture", sf::Shader::CurrentTexture);
    lightRenderTex.create(800,800);
    offset = 0.5;
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

bool compareIntersects(Intersect vec1, Intersect vec2)
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


Intersect LightEngine::getLineIntersect(sf::VertexArray ray, sf::VertexArray segment)
{

    float r_px= ray[0].position.x;
    float r_py = ray[0].position.y;
    float r_dx = ray[1].position.x - ray[0].position.x;
    float r_dy = ray[1].position.y - ray[0].position.y;

    float s_px = segment[0].position.x;
    float s_py =segment[0].position.y;
    float s_dx = segment[1].position.x - segment[0].position.x;
    float s_dy =segment[1].position.y - segment[0].position.y;

    //parallel check
    float r_mag = sqrt(r_dx*r_dx+r_dy*r_dy);
    float s_mag = sqrt(s_dx*s_dx+s_dy*s_dy);
    if(r_dx/r_mag==s_dx/s_mag && r_dy/r_mag==s_dy/s_mag)  // if they point in same direction, then theres no intersection
    {
        return  Intersect(sf::Vector2f(0,0), 0);
    }

    float T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx);
    float T1 = (s_px+s_dx*T2-r_px)/r_dx;

    if(T1<0) return Intersect(sf::Vector2f(0,0), 0);
    if(T2<0 || T2>1) return Intersect(sf::Vector2f(0,0), 0);

    return Intersect(sf::Vector2f(r_px+r_dx*T1,r_py+r_dy*T1),T1);
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


std::vector<Intersect> LightEngine::getIntersectPoints(const std::vector<float> &uniqueAngles, const sf::Vector2f &point)
{
    std::vector<Intersect> intersects;
    for(int uniqueAngleIndex=0; uniqueAngleIndex < uniqueAngles.size(); uniqueAngleIndex++)
    {
        float angle = uniqueAngles[uniqueAngleIndex];
        float x = cos(angle);
        float y = sin(angle);

        sf::VertexArray ray(sf::Lines);
        ray.append(sf::Vertex(point, sf::Color::Black));
        ray.append(sf::Vertex(sf::Vector2f(point.x + x,point.y + y), sf::Color::Black));

        Intersect closestInterect(sf::Vector2f(799,799), 1000);
        for(int i = 0 ;  i < shapeVectors.size(); i+=2)
        {
            sf::Vector2f seg1 =shapeVectors[i];
            sf::Vector2f seg2 =shapeVectors[i+1];
            sf::VertexArray segLine(sf::Lines);
            segLine.append(seg1);
            segLine.append(seg2);
            Intersect intersect =  getLineIntersect(ray, segLine);

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

void LightEngine::draw(sf::RenderWindow &renderWindow)
{

    lightRenderTex.clear(sf::Color(50,50,50));

    for ( auto lightIterator = lights.begin(); lightIterator!= lights.end(); ++lightIterator )
    {
        Light light = lightIterator->second;
        std::vector<float> uniqueAngles = getUniqueAngles(light.getVec());
        std::vector<Intersect> intersects = getIntersectPoints(uniqueAngles,light.getVec());
            shadowBlur.setParameter("lightpos",light.getVec());
            shadowBlur.setParameter("lightColor",sf::Vector3f(1,1,0));
            shadowBlur.setParameter("screenHeight",800);


        sf::VertexArray rayLine(sf::TrianglesFan);
        rayLine.append(sf::Vertex(light.getVec(), sf::Color::White));
        for(int i = 0; i < intersects.size(); i++)
        {
           rayLine.append(sf::Vertex(intersects[i].getIntersectPoint(), sf::Color::White));
        }
        rayLine.append(sf::Vertex(intersects[0].getIntersectPoint(),  sf::Color::White));
     //   renderWindow.draw(rayLine);
        sf::RenderStates r1(sf::BlendAdd);
        r1.shader = &shadowBlur;
        lightRenderTex.draw(rayLine, r1);

        if(shoulDebugLines){

        for(int i = 0; i < intersects.size(); i++){
           sf::VertexArray line(sf::Lines);
           line.append(sf::Vertex(light.getVec(), sf::Color::Red));
           line.append(sf::Vertex(intersects[i].getIntersectPoint(), sf::Color::Red));
           lightRenderTex.draw(line);
            }
        }
    }

    lightRenderTex.display();

    sf::RenderStates r(sf::BlendMultiply);
   // r.shader = &shadowBlur;
    renderWindow.draw(sf::Sprite (lightRenderTex.getTexture()), r);


}


LightKey LightEngine::addLight(const std::string &key, const sf::Vector2f &lightVector, const sf::Color &lightColor)
{
    auto it = lights.find(key);
//    if( it != lights.end() )
//    {
        lights.insert(std::make_pair(key,Light(key,lightVector, lightColor)));
//    }

    return LightKey(key);
}

void LightEngine::removeLight(const LightKey &lightKey)
{

}

void LightEngine::setPosition(const LightKey &lightKey, const sf::Vector2f &newPosition)
{
    std::unordered_map<std::string,Light>::iterator got = lights.find (lightKey.key());
    if (!(got == lights.end()) )
    {
        Light light =  got->second;
        light.setVec(newPosition);
         got->second = light;
    }
    int i = 0;

}

void LightEngine::debugLightRays(bool debugLines){
    shoulDebugLines = debugLines;
}





