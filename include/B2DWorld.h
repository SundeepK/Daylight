#ifndef B2DWORLD_H
#define B2DWORLD_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>

class B2DWorld
{
    public:
        B2DWorld();
        virtual ~B2DWorld();
    protected:
    private:
        b2World world;
};

class B2BodyBuilder
{
     public:
     B2BodyBuilder();
     virtual ~B2BodyBuilder();
     B2BodyBuilder setPosition(b2Vec2 position);
     B2BodyBuilder bodyType(float x, float y);
     B2BodyBuilder bodyDef(b2BodyDef bodyDef);
     B2BodyBuilder setFriction(float friction);
     B2BodyBuilder setRestitution(float restitution);
     B2BodyBuilder setDensity(float density);
     B2BodyBuilder setSensor(bool isSensor);
     B2BodyBuilder build(b2Shape* shape);

};

#endif // B2DWORLD_H
