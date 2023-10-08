#pragma once
#include "vec2f.h"
#include <SFML/Graphics.hpp>

class cTransform
{
public:
    Vec2f pos = {};
    Vec2f velocity = {};
    float angle;

    cTransform(const Vec2f& p, const Vec2f& v, float a)
        :pos(p), velocity(v), angle(a){};
};

class cShape
{
public:
    sf::CircleShape circle;

    cShape(const sf::CircleShape c)
        :circle(c){};

    cShape(int numOfVertices, float radius, const sf::Color& fillColor, const sf::Color& outlineColor, const float thickness)
        :circle(radius, numOfVertices)
    {
        circle.setFillColor(fillColor);
        circle.setOutlineColor(outlineColor);
        circle.setOutlineThickness(thickness);

        // Set the 0,0 coordinate of the shape from the top left corner of the AABB of the circle to the middle of the circle
        // This will cause that the setPosition function of the shape will put the middle of the circle to the given position.
        circle.setOrigin(radius, radius);
    }
};


class cCollision
{
public:
    float radius = 0;
    cCollision(float r) : radius(r){};
};

class cScore
{
public:
    int score = 0;
    cScore(int s) : score(s){};
};

class cInput
{
public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool leftMouse = false;
    bool rightMouse = false;
    bool P = false;
    bool ESC = false;

    cInput(){};
};

class cLifespan
{
public:
    int totalLifespan = 0;
    int remainingLifespan = 0;
    cLifespan(int totalLifespan, int remainingLifespan)
        : totalLifespan(totalLifespan)
        , remainingLifespan(totalLifespan){};
};