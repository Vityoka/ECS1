#pragma once
#include "vec2f.h"
#include <SFML/Graphics.hpp>

class CTransform
{
public:
    Vec2f pos = {};
    Vec2f velocity = {};
    float angle;

    CTransform(const Vec2f& p, const Vec2f& v, float a)
        :pos(p), velocity(v), angle(a){};
};

class CShape
{
public:
    sf::CircleShape circle;

    CShape(const sf::CircleShape c)
        :circle(c){};

    CShape(int numOfVertices, float radius, const sf::Color& fillColor, const sf::Color& outlineColor = sf::Color::White, const float thickness = 1.0F)
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


class CCollision
{
public:
    float radius = 0;
    CCollision(float r) : radius(r){};
};

class CScore
{
public:
    int score = 0;
    CScore(int s) : score(s){};
};

class CInput
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

    CInput(){};
};

class CLifespan
{
public:
    int totalLifespan = 0;
    int remainingLifespan = 0;
    CLifespan(int totalLifespan, int remainingLifespan)
        : totalLifespan(totalLifespan)
        , remainingLifespan(totalLifespan){};
};