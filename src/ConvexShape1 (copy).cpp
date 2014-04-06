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

    for(int i = 1; i <= shapePoints.getVertexCount() ; i++)
    {
        sf::Vector2f* currentVec = shapePoints[i];
        sf::Vector2f* previousVec = shapePoints[i-1];

        sf::Vector2f normalVec(currentVec->y - previousVec->y, currentVec->x - previousVec->x);

        sf::Vector2f lightVec(currentVec->x - light.x, currentVec->y - light.y);

        bool isFrontFacing = false;
        int firstPoint =0;
        int lastPoint =0;

        if ((normalVec.x * -1 * lightVec.x) + (normalVec.y * lightVec.y) > 0){
            if(!isFrontFacing){
                firstPoint = i;
            }
            isFrontFacing = true;
        }else{
            if(isFrontFacing){
                lastPoint=i;
            }
            isFrontFacing = false;
        }

        if(((firstPoint) < 0 || (lastPoint) < 0 ){
            return;
        }

        }

        std::vector<ShadowFin> startFins = getShadowFins(light.GetPosition(),firstPoint, 1 );
        std::vector<ShadowFin> endFins = getShadowFins(light.GetPosition(),lastPoint, -1 );

        for(int i = 0 ; i < startFins.size(); i ++){
            startFins[i].draw(App);
        }

       for(int i = 0 ; i < endFins.size(); i ++){
            endFins[i].draw(App);
        }

         App->draw(shapePoints);
}

std::vector<ShadowFin> ConvexShape::getShadowFins(sf::Vector2f lightOrigin, int indexOrigin, int step, sf::VertexArray points){
    std::vector<ShadowFin> shadowFins();
    int i = indexOrigin;

    while(true){
       sf::Vertex point1 = shapePoints[i];

       i-=step;
       if(i < 0){
        i = shapePoints.getVertexCount() -1;
       }else if(i == shapePoints.getVertexCount()){
        i = 0;
       }

       sf::Vertex point2 = shapePoints[i];
       sf::Vector2f edge = getEdge(point1, point2);
       Vector2fWrapper edgeWrap(edge);
       edgeWrap.normalize();

       ShadowFin shadowFin(point2);

       Vector2fWrapper lightWrap(lightOrigin);
       float angle = edgeWrap.angle() - lightWrap.angle();

       if(step ==1){
            if(angle < 0 || angle > M_PI * 0.5){
                break;
            }
       }else if(step == -1){
        if(angle > M_PI ){
            angle -= M_PI * 2;
        }
        if(angle > 0 || angle < -M_PI * 0.5){
            break;
        }
       }

      shadowFin.setOut(light.getOuterVector(point1,step));
      shadowFin.setInner(light.getInnerVector(point2, step));
      shadowFins.push_back(shadowFin);
    }

    int i = indexOrigin;
    while(true){
       sf::Vertex point1 = shapePoints[i];
       ShadowFin shadowFin(point1);
       shadowFin.setIndex(i);
       shadowFin.setOut(light.getOuterVector(point1, step));
       shadowFin.setInner(light.getInnerVector(point1, step));

       if(shadowFins.size() > 0){
            shadowFin.setOut(shadowFin[0].innerVector);
       }

       i+=step;
       if(i < 0){
            i = shapePoints.getVertexCount() - 1;
       }else if( i == shapePoints.getVertexCount()){
            i = 0;
       }

       sf::Vector2f point2 = shapePoints[i];
       sf::Vector2f edge = getEdge(point1, point2);
       Vector2fWrapper edgeWrap(edge);
       edgeWrap.normalize();

       bool done = true;
       Vector2fWrapper penumber(shadowFin.getOuter());
       penumber.normalize();
       Vector2fWrapper umbera(shadowFin.getInner());
       umbera.normalize();
       Vector2fWrapper lightWrapper(light.getOuterVector(point1, step));
       if(acos(edgeWrap.dot(penumber.getVector2f()) <
          acos(umbera.dot(penumber.getVector2f())))){
          shadowFin.setInner(edgeWrap.getVector2f() * lightWrapper.lenght());
          done = false;
       }
       shadowFins.insert(0, shadowFin);

       if(done){
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

sf::Vector2 ConvexShape::getEdge(sf::Vertex v1, sf::Vertext v2){
    return sf::Vector2f(v1.position.x - v2.position.x, v2.positions.x - v2.position.y);
}



