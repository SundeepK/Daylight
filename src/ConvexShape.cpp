#include "ConvexShape.h"


ConvexShape::ConvexShape()
{
}

ConvexShape::ConvexShape(sf::VertexArray points, sf::Color colorToUse)
    : shapePoints(points), shapeColor(colorToUse)
{
}


ConvexShape::~ConvexShape()
{
}

void ConvexShape::draw(sf::RenderTarget *App)
{

    App->draw(shapePoints);
}


void ConvexShape::drawShadows(Light &light, sf::RenderTarget *App)
{
    pointsC.clear();
    for(int i = 0 ; i < shapePoints.getVertexCount(); i++)
    {
        pointsC.push_back(shapePoints[i].position);
    }
    int firstPoint =0;
    int lastPoint =0;
    bool isFrontFacing = NULL;
    int pointSize = pointsC.size();
    for(int i =  -1; i < pointSize; i++)
    {
        sf::Vector2f currentVec = getVectorFromIndex(i);
        sf::Vector2f previousVec = getVectorFromIndex(i-1);

        sf::Vector2f normalVec(currentVec.y - previousVec.y, currentVec.x - previousVec.x);
        sf::Vector2f lightVec(currentVec.x - light.GetPosition().x, currentVec.y - light.GetPosition().y);


        if ((normalVec.x * -1 * lightVec.x) + (normalVec.y * lightVec.y) > 0)
        {
            if(isFrontFacing != NULL && !isFrontFacing)
            {
                std::vector<sf::Vector2f>::iterator it;
                it = find (pointsC.begin(), pointsC.end(), previousVec);
                int index = std::distance(pointsC.begin(), it);
                lastPoint=index;

            }
            isFrontFacing = true;
        }
        else
        {
            if(isFrontFacing != NULL  && isFrontFacing)
            {
                std::vector<sf::Vector2f>::iterator it;
                it = find (pointsC.begin(), pointsC.end(), previousVec);
                int index = std::distance(pointsC.begin(), it);
                firstPoint = index;

            }
            isFrontFacing = false;
        }
    }
    std::cout << firstPoint << std::endl;

//    if(((firstPoint) < 0 || (lastPoint) < 0 ))
//    {
//        std::cout << "retutning less than zero" << std::endl;
//        return;
//    }



   std::vector<ShadowFin> startFins = getShadowFins(light,firstPoint, 1 );
   std::vector<ShadowFin> endFins = getShadowFins(light, lastPoint, -1 );


//    for(int i = 0 ; i < startFins.size(); i ++)
//    {
//        startFins[i].draw(App);
//    }
//
//        for(int i = 0 ; i < endFins.size(); i ++)
//    {
//        endFins[i].draw(App);
//    }



    if(startFins.size() > 0 && endFins.size() > 0){


    std::vector<sf::Vector2f> backpoints;
    for(int i = startFins[0].getIndex(); i < shapePoints.getVertexCount() + startFins[0].getIndex() ; i++)
    {
        backpoints.insert(backpoints.begin(), getVectorFromIndex(i%shapePoints.getVertexCount()));
        if((i%shapePoints.getVertexCount()) == endFins[0].getIndex())
        {
            break;
        }
    }

    float sumofBack = 0;
    std::vector<float> backlength;
    backlength.push_back(0.0f);
    int backpointSize = backpoints.size();
    for(int  i = 1; i < backpointSize; i++)
    {
        sf::Vector2f fromPoint = backpoints[getIntFromIndex(i-1)];
        sf::Vector2f toPoint = backpoints[getIntFromIndex(i)];
        float l = Vector2fWrapper(sf::Vector2f(fromPoint.x - toPoint.x, fromPoint.y - toPoint.y)).lenght();
        backlength.insert(backlength.begin(), l);
        sumofBack+=l;
    }


    sf::VertexArray vertextArray(sf::TrianglesStrip);
    sf::Color convexColor(sf::Color::Black);
    float  a= 0;
    for(int i = 0; i < backpointSize; i++)
    {
        sf::Vector2f point = backpoints[getIntFromIndex(i)];
        vertextArray.append(point);
        if(i != backpoints.size() -2)
        {
            vertextArray.append( sf::Vertex(sf::Vector2f(point.x + (startFins[0].getInner().x * (a/sumofBack)) + (endFins[0].getInner().x * (1 - (a/sumofBack))) ,
            point.y + (startFins[0].getInner().y * (a/sumofBack)) + (endFins[0].getInner().y * (1 - (a/sumofBack)))), convexColor));
        }
        else
        {
            vertextArray.append(sf::Vertex(sf::Vector2f( point.x + startFins[0].getInner().x , point.y + startFins[0].getInner().y ) ));
        }
        a+=backlength[getIntFromIndex(i)];
    }
        sf::RenderStates r(sf::BlendAdd);

    App->draw(vertextArray);

    }

    App->draw(shapePoints);


}

std::vector<ShadowFin> ConvexShape::getShadowFins(Light lightOrigin, int indexOrigin, int step)
{
    std::vector<ShadowFin> shadowFins;
    int i = indexOrigin;

    while(true)
    {
        sf::Vector2f point1 = getVectorFromIndex(i);

        i -= step;
        if(i < 0)
        {
            i = shapePoints.getVertexCount() -1;
        }
        else if(i == shapePoints.getVertexCount())
        {
            i = 0;
        }

        sf::Vector2f point2 = getVectorFromIndex(i);
        sf::Vector2f edge = getEdge(point1, point2);
        Vector2fWrapper edgeWrap(edge);
        edgeWrap.normalize();

        ShadowFin shadowFin(point2);
        shadowFin.setIndex(i);
        Vector2fWrapper lightWrap(lightOrigin.getOuterVector(point2, step));
        float angle = edgeWrap.angle() - lightWrap.angle();

        if(step ==1)
        {
            if(angle < 0 || angle > M_PI * 0.5)
            {
                break;
            }
        }
        else if(step == -1)
        {
            if(angle > M_PI )
            {
                angle -= M_PI * 2;
            }
            if(angle > 0 || angle < -M_PI * 0.5)
            {
                break;
            }
        }

        shadowFin.setOut(lightOrigin.getOuterVector(point2,step));
        shadowFin.setInner(edge * (Vector2fWrapper(lightOrigin.getInnerVector(point2, step)).lenght()) );
        shadowFins.push_back(shadowFin);
    }

    i = indexOrigin;
    while(true)
    {
        sf::Vector2f point1 = getVectorFromIndex(i);
        ShadowFin shadowFin(point1);
        shadowFin.setIndex(i);

        shadowFin.setOut(lightOrigin.getOuterVector(point1, step));
        shadowFin.setInner(lightOrigin.getInnerVector(point1, step));

        if(shadowFins.size() > 0)
        {
            shadowFin.setOut(shadowFins[getIntFromIndex(0)].getInner());
        }

        i+=step;
        if(i < 0)
        {
            i = shapePoints.getVertexCount() - 1;
        }
        else if( i == shapePoints.getVertexCount())
        {
            i = 0;
        }

        sf::Vector2f point2 = getVectorFromIndex(i);
        sf::Vector2f edge = getEdge(point1, point2);
        Vector2fWrapper edgeWrap(edge);
        edgeWrap.normalize();

        bool done = true;
        Vector2fWrapper penumber(shadowFin.getOuter());
        penumber.normalize();

        Vector2fWrapper umbera(shadowFin.getInner());
        umbera.normalize();
        Vector2fWrapper lightWrapper(lightOrigin.getOuterVector(point2, step));

        if(acos(edgeWrap.dot(penumber.getVector2f()) <
                acos(umbera.dot(penumber.getVector2f()))))
        {
            shadowFin.setInner(edgeWrap.getVector2f() * lightWrapper.lenght());
            done = false;
        }
        shadowFins.insert(shadowFins.begin(), shadowFin);

        if(done)
        {
            break;
        }
    }

//    int angleSum =0;
//    for(int i = 0 ; i < shadowFins.size(); i++){
//        angleSum += shadowFins[i].angle();
//    }
//
//    int angle = 0;

    return shadowFins;

}

sf::Vector2f ConvexShape::getEdge(sf::Vector2f v1, sf::Vector2f v2)
{
    return sf::Vector2f(v1.x - v2.x, v1.x - v2.y);
}

int ConvexShape::getIntFromIndex(int index)
{
    if(pointsC.size()==1) index=0;
    else if(index < 0 || index >= pointsC.size()) index = index % pointsC.size();
    if(index<0) index = pointsC.size() + index;
    return  index;
}

sf::Vector2f ConvexShape::getVectorFromIndex(int index)
{
    if(pointsC.size()==1) index=0;
    else if(index < 0 || index >= pointsC.size()) index = index % pointsC.size();
    if(index<0) index = pointsC.size() + index;
    return  pointsC[index];
}


