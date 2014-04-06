//#include <sstream>
//#include "Intersect.h"
//#include <math.h>
//#include <iostream>
//#include <unordered_set>
//
//void addPoints(std::vector<sf::Vector2f> &points, sf::VertexArray vertextArray)
//{
//    for(int  i = 0 ; i < vertextArray.getVertexCount() ; i ++)
//    {
//        points.push_back(vertextArray[i].position);
//    }
//}
//
//struct VectorHash {
//    inline std::size_t operator()(const sf::Vector2f & v) const {
//        return v.x*31+v.y;
//    }
//};
//
//struct compVectors {
//
//bool operator() (sf::Vector2f vec1, sf::Vector2f vec2){
//    return vec1.x < vec2.x && vec1.y < vec2.y;
//}
//};
//
//bool compareIntersectVectors1(Intersect vec1, Intersect vec2){
//    if(vec1.getAngle()  - vec2.getAngle() < 0){
//        return true;
//    }else if (vec1.getAngle()  - vec2.getAngle() > 0){
//        return false;
//    }
//
//    return false;
//}
//
//
//void addUniquePoints(std::vector<sf::Vector2f> &shapePoints,
//    std::unordered_set<sf::Vector2f, VectorHash> &points, sf::VertexArray vertextArray)
//{
//    for(int  i = 0 ; i < vertextArray.getVertexCount() ; i ++)
//    {
//        const bool is_in = points.find(vertextArray[i].position) != points.end();
//        if(!is_in){
//         shapePoints.push_back(vertextArray[i].position);
//         points.insert(vertextArray[i].position);
//        }
//     //   points.push_back(vertextArray[i].position);
//    }
//}
//
//Intersect getLineIntersect(sf::VertexArray ray, sf::VertexArray segment)
//{
//
//float r_px= ray[0].position.x;
//float r_py =  ray[0].position.y;
//float r_dx = ray[1].position.x - ray[0].position.x;
//float r_dy = ray[1].position.y - ray[0].position.y;
//
//float s_px = segment[0].position.x;
//float s_py =segment[0].position.y;
//float s_dx = segment[1].position.x - segment[0].position.x;
//float s_dy =segment[1].position.y - segment[0].position.y;
//
//
//	// Are they parallel? If so, no intersect
//	float r_mag = sqrt(r_dx*r_dx+r_dy*r_dy);
//	float s_mag = sqrt(s_dx*s_dx+s_dy*s_dy);
//	if(r_dx/r_mag==s_dx/s_mag && r_dy/r_mag==s_dy/s_mag){ // Directions are the same.
//		return  Intersect(sf::Vector2f(0,0), 0);
//	}
//
//	// SOLVE FOR T1 & T2
//	// r_px+r_dx*T1 = s_px+s_dx*T2 && r_py+r_dy*T1 = s_py+s_dy*T2
//	// ==> T1 = (s_px+s_dx*T2-r_px)/r_dx = (s_py+s_dy*T2-r_py)/r_dy
//	// ==> s_px*r_dy + s_dx*T2*r_dy - r_px*r_dy = s_py*r_dx + s_dy*T2*r_dx - r_py*r_dx
//	// ==> T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx)
//	float T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx);
//	float T1 = (s_px+s_dx*T2-r_px)/r_dx;
//
//	// Must be within parametic whatevers for RAY/SEGMENT
//	if(T1<0) return Intersect(sf::Vector2f(0,0), 0);
//	if(T2<0 || T2>1) return Intersect(sf::Vector2f(0,0), 0);
//
//	// Return the POINT OF INTERSECTION
//	return Intersect(sf::Vector2f(r_px+r_dx*T1,r_py+r_dy*T1),T1);
//}
//
//int main()
//{
//    sf::RenderWindow App(sf::VideoMode(800, 800, 32), "2D Shadows");
//
//    sf::Clock Clock;
//
//    sf::VertexArray triangle(sf::Triangles, 3);
//    triangle.append(sf::Vertex(sf::Vector2f(500, 500), sf::Color::Green));
//        triangle.append(sf::Vertex(sf::Vector2f(650, 650), sf::Color::Green));
//    triangle.append(sf::Vertex(sf::Vector2f(500, 650), sf::Color::Green));
//
//    sf::VertexArray quad(sf::Quads, 4);
//    quad.append(sf::Vertex(sf::Vector2f(600, 600), sf::Color::Green));
//    quad.append(sf::Vertex(sf::Vector2f(700, 600), sf::Color::Green));
//    quad.append(sf::Vertex(sf::Vector2f(700, 700), sf::Color::Green));
//    quad.append(sf::Vertex(sf::Vector2f(600, 700), sf::Color::Green));
//
//        sf::VertexArray screen(sf::Quads, 4);
//    screen.append(sf::Vertex(sf::Vector2f(0, 0),sf::Color(0,0,0,0)));
//    screen.append(sf::Vertex(sf::Vector2f(800, 0), sf::Color(0,0,0,0)));
//    screen.append(sf::Vertex(sf::Vector2f(800, 800), sf::Color(0,0,0,0)));
//    screen.append(sf::Vertex(sf::Vector2f(0, 800), sf::Color(0,0,0,0)));
//
//    sf::VertexArray border(sf::Lines);
//    border.append(sf::Vertex(sf::Vector2f(1,1), sf::Color::Red));
//    border.append(sf::Vertex(sf::Vector2f(799,1), sf::Color::Red));
//
//    border.append(sf::Vertex(sf::Vector2f(799,1), sf::Color::Red));
//    border.append(sf::Vertex(sf::Vector2f(799,799), sf::Color::Red));
//
//    border.append(sf::Vertex(sf::Vector2f(799,799), sf::Color::Red));
//    border.append(sf::Vertex(sf::Vector2f(1,799), sf::Color::Red));
//
//    border.append(sf::Vertex(sf::Vector2f(1,799), sf::Color::Red));
//    border.append(sf::Vertex(sf::Vector2f(1,1), sf::Color::Red));
//
//    sf::VertexArray line1(sf::Lines);
//    line1.append(sf::Vertex(sf::Vector2f(200,260), sf::Color::Red));
//    line1.append(sf::Vertex(sf::Vector2f(220,150), sf::Color::Red));
//
//    line1.append(sf::Vertex(sf::Vector2f(220,150), sf::Color::Red));
//    line1.append(sf::Vertex(sf::Vector2f(300,200), sf::Color::Red));
//
//    line1.append(sf::Vertex(sf::Vector2f(300,200), sf::Color::Red));
//    line1.append(sf::Vertex(sf::Vector2f(350,320), sf::Color::Red));
//
//    line1.append(sf::Vertex(sf::Vector2f(350,320), sf::Color::Red));
//    line1.append(sf::Vertex(sf::Vector2f(200,260), sf::Color::Red));
//
//
//    sf::VertexArray line2(sf::Lines);
//    line2.append(sf::Vertex(sf::Vector2f(340,60), sf::Color::Red));
//    line2.append(sf::Vertex(sf::Vector2f(340,40), sf::Color::Red));
//
//    line2.append(sf::Vertex(sf::Vector2f(360,40), sf::Color::Red));
//    line2.append(sf::Vertex(sf::Vector2f(370,70), sf::Color::Red));
//
//    line2.append(sf::Vertex(sf::Vector2f(370,70), sf::Color::Red));
//    line2.append(sf::Vertex(sf::Vector2f(340,60), sf::Color::Red));
//
//    std::unordered_set<sf::Vector2f, VectorHash> shapePointsSet;
//    std::vector<sf::Vector2f> uniqPoints;
//
//    addUniquePoints(uniqPoints,shapePointsSet, border);
//    addUniquePoints(uniqPoints, shapePointsSet, line1);
//    addUniquePoints(uniqPoints, shapePointsSet, line2);
//
//   std::vector<sf::Vector2f> shapePoints;
//    addPoints(shapePoints, border);
//    addPoints(shapePoints, line1);
//    addPoints(shapePoints, line2);
//
//    for(int  i = 0 ; i < uniqPoints.size(); i ++){
//      std::cout << uniqPoints[i].x << " y" << uniqPoints[i].y << std::endl;
//    }
//
//
//    sf::VertexArray line(sf::Lines);
//    line.append(sf::Vertex(sf::Vector2f(400,400), sf::Color::Black));
//    line.append(sf::Vertex(sf::Vector2f(410,400), sf::Color::Black));
//
//
//    while (App.isOpen())
//    {
//        sf::Event Event;
//        while (App.pollEvent(Event))
//        {
//            if (Event.type == sf::Event::Closed)
//            {
//                App.close();
//            }
//        }
//
//        Clock.restart();
//
//    App.clear(sf::Color::Black);
//
//    sf::Vector2f mousePos(sf::Vector2f(sf::Mouse::getPosition(App).x,sf::Mouse::getPosition(App).y));
//
//    std::vector<Intersect> intersects;
//
//
//    std::vector<double> uniqueAngles;
//    for(int  i  = 0 ; i  < uniqPoints.size(); i++){
//        sf::Vector2f point = uniqPoints[i];
//        double angle = atan2(point.y - mousePos.y, point.x - mousePos.x);
//        uniqueAngles.push_back((angle-0.0001f));
//        uniqueAngles.push_back(angle);
//        uniqueAngles.push_back((angle+0.0001f));
//    }
//
//
//
//	for(int uniqueAngleIndex=0; uniqueAngleIndex < uniqueAngles.size(); uniqueAngleIndex++ ){
//       double angle = uniqueAngles[uniqueAngleIndex];
//       double x = cos(angle);
//       double y = sin(angle);
//
//        sf::VertexArray ray(sf::Lines);
//        ray.append(sf::Vertex(mousePos, sf::Color::Black));
//        ray.append(sf::Vertex(sf::Vector2f(mousePos.x + x,mousePos.y + y), sf::Color::Black));
//
//        Intersect closestInterect(sf::Vector2f(799,799), 1000);
//        for(int i = 0 ;  i < shapePoints.size(); i+=2)
//        {
//            sf::Vector2f seg1 =shapePoints[i];
//            sf::Vector2f seg2 =shapePoints[i+1];
//            sf::VertexArray segLine(sf::Lines);
//            segLine.append(seg1);
//            segLine.append(seg2);
//            Intersect intersect =  getLineIntersect(ray, segLine);
//
//            if(intersect.getIntersectPoint().x > 0 && intersect.getIntersectPoint().y > 0)
//            {
//                if(intersect.getParam() < closestInterect.getParam())
//                {
//                    closestInterect = intersect;
//                }
//            }
//
//        }
//
//        if(closestInterect.getParam() < 1000){
//        closestInterect.setAngle(angle);
//        intersects.push_back(closestInterect);
//        }
//
//
//        }
//
//        std::sort(intersects.begin(), intersects.end(), compareIntersectVectors1);
//
//        sf::VertexArray rayLine(sf::TrianglesFan);
//        rayLine.append(sf::Vertex(mousePos, sf::Color::White));
//        for(int i = 0; i < intersects.size(); i++){
//         rayLine.append(sf::Vertex(intersects[i].getIntersectPoint(), sf::Color::White));
//        // rayLine.append(sf::Vertex(intersects[i-1].getIntersectPoint(), sf::Color::Black));
//
//        }
//        rayLine.append(sf::Vertex(intersects[0].getIntersectPoint(), sf::Color::White));
//
//        App.draw(rayLine);
//
//
//
////        std::vector<sf::VertexArray> rays;
////        sf::Color col(255,0,0);
////        for(int i = 0; i < intersects.size(); i++){
////            sf::VertexArray rayLine(sf::Lines);
////            rayLine.append(sf::Vertex(mousePos, col));
////            rayLine.append(sf::Vertex(intersects[i].getIntersectPoint(), col));
////            rays.push_back(rayLine);
////        }
////
////        for(int i = 0; i < rays.size(); i++){
////            App.draw(rays[i]);
////        }
//
//        App.draw(triangle);
//        App.draw(quad);
//        App.draw(line1);
//        App.draw(line2);
//
//
//
//        App.display();
//    }
//
//
//    return EXIT_SUCCESS;
//};
//
//
//
//
