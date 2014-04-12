#include <sstream>
#include "Intersect.h"
#include <math.h>
#include <iostream>
#include <unordered_set>
#include "LightEngine.h"

int main()
{

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    sf::RenderWindow App(sf::VideoMode(800, 800, desktop.bitsPerPixel), "2D Shadows",sf::Style::Default, settings);

    sf::Clock Clock;

    sf::VertexArray screen(sf::Quads, 4);
    screen.append(sf::Vertex(sf::Vector2f(0, 0),sf::Color(0,0,0,0)));
    screen.append(sf::Vertex(sf::Vector2f(800, 0), sf::Color(0,0,0,0)));
    screen.append(sf::Vertex(sf::Vector2f(800, 800), sf::Color(0,0,0,0)));
    screen.append(sf::Vertex(sf::Vector2f(0, 800), sf::Color(0,0,0,0)));

    sf::VertexArray border(sf::Lines);
    border.append(sf::Vertex(sf::Vector2f(1,1), sf::Color::Red));
    border.append(sf::Vertex(sf::Vector2f(799,1), sf::Color::Red));

    border.append(sf::Vertex(sf::Vector2f(799,1), sf::Color::Red));
    border.append(sf::Vertex(sf::Vector2f(799,799), sf::Color::Red));

    border.append(sf::Vertex(sf::Vector2f(799,799), sf::Color::Red));
    border.append(sf::Vertex(sf::Vector2f(1,799), sf::Color::Red));

    border.append(sf::Vertex(sf::Vector2f(1,799), sf::Color::Red));
    border.append(sf::Vertex(sf::Vector2f(1,1), sf::Color::Red));

    sf::VertexArray line1(sf::Lines);
    line1.append(sf::Vertex(sf::Vector2f(200,260), sf::Color::Red));
    line1.append(sf::Vertex(sf::Vector2f(270,150), sf::Color::Red));

    line1.append(sf::Vertex(sf::Vector2f(270,150), sf::Color::Red));
    line1.append(sf::Vertex(sf::Vector2f(300,200), sf::Color::Red));

    line1.append(sf::Vertex(sf::Vector2f(300,200), sf::Color::Red));
    line1.append(sf::Vertex(sf::Vector2f(350,320), sf::Color::Red));

    line1.append(sf::Vertex(sf::Vector2f(350,320), sf::Color::Red));
    line1.append(sf::Vertex(sf::Vector2f(200,260), sf::Color::Red));

    sf::VertexArray line2(sf::Lines);
    line2.append(sf::Vertex(sf::Vector2f(340,60), sf::Color::Red));
    line2.append(sf::Vertex(sf::Vector2f(340,40), sf::Color::Red));

    line2.append(sf::Vertex(sf::Vector2f(360,40), sf::Color::Red));
    line2.append(sf::Vertex(sf::Vector2f(370,70), sf::Color::Red));

    line2.append(sf::Vertex(sf::Vector2f(370,70), sf::Color::Red));
    line2.append(sf::Vertex(sf::Vector2f(340,60), sf::Color::Red));

    sf::VertexArray shape1(sf::Lines);
    shape1.append(sf::Vertex(sf::Vector2f(600,600), sf::Color::Red));
    shape1.append(sf::Vertex(sf::Vector2f(700,600), sf::Color::Red));

    shape1.append(sf::Vertex(sf::Vector2f(700,600), sf::Color::Red));
    shape1.append(sf::Vertex(sf::Vector2f(700,700), sf::Color::Red));

    shape1.append(sf::Vertex(sf::Vector2f(700,700), sf::Color::Red));
    shape1.append(sf::Vertex(sf::Vector2f(600,750), sf::Color::Red));

    shape1.append(sf::Vertex(sf::Vector2f(600,750), sf::Color::Red));
    shape1.append(sf::Vertex(sf::Vector2f(600,600), sf::Color::Red));

    sf::VertexArray shape2(sf::Lines);
    shape2.append(sf::Vertex(sf::Vector2f(100,600), sf::Color::Red));
    shape2.append(sf::Vertex(sf::Vector2f(200,600), sf::Color::Red));

    shape2.append(sf::Vertex(sf::Vector2f(200,600), sf::Color::Red));
    shape2.append(sf::Vertex(sf::Vector2f(200,700), sf::Color::Red));

    shape2.append(sf::Vertex(sf::Vector2f(200,700), sf::Color::Red));
    shape2.append(sf::Vertex(sf::Vector2f(100,700), sf::Color::Red));

    shape2.append(sf::Vertex(sf::Vector2f(100,700), sf::Color::Red));
    shape2.append(sf::Vertex(sf::Vector2f(100,600), sf::Color::Red));

    LightEngine lightEngine;
    lightEngine.addShape(border);
    lightEngine.addShape(line1);
    lightEngine.addShape(line2);
    lightEngine.addShape(shape1);
    lightEngine.addShape(shape2);
    lightEngine.debugLightRays(false);

    LightKey mouseLight = lightEngine.addLight("mouse light", sf::Vector2f(400,400), sf::Color::White);
    while (App.isOpen())
    {
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
            {
                App.close();
            }
        }

        Clock.restart();

       App.clear(sf::Color::White);

       sf::Vector2f mousePos(sf::Vector2f(sf::Mouse::getPosition(App).x,sf::Mouse::getPosition(App).y));
       lightEngine.setPosition(mouseLight, mousePos);

        lightEngine.draw(App);

        App.draw(line1);
        App.draw(line2);
        App.draw(shape1);
        App.draw(shape2);
        App.display();
    }


    return EXIT_SUCCESS;
};




