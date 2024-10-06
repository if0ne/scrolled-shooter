#pragma once
#include <SDL.h>

export module GameObject;

static int nextId = 0;

export class GameObject {
protected:
    int _id;

    // Center coordinates
    float _x = 0.0;
    float _y = 0.0;

    float _width = 1.0;
    float _height = 1.0;

public:
    GameObject() 
        : _id(nextId++) 
    {}

    GameObject(float x, float y, float width, float height)
        : _id(nextId++)
        , _x(x)
        , _y(y)
        , _width(width)
        , _height(height)
    {}

    virtual void Update(float dt) = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;

    int Id() const {
        return _id;
    }

    void Coords(float x, float y) {
        _x = x;
        _y = y;
    }

    float X() const {
        return _x;
    }

    float Y() const {
        return _y;
    }

    void Size(float width, float height) {
        _width = width;
        _height = height;
    }

    bool IsIntersect(const GameObject& other) const {
        float halfWidth = _width / 2.0f;
        float halfHeight = _height / 2.0f;
        float otherHalfWidth = other._width / 2.0f;
        float otherHalfHeight = other._height / 2.0f;

        float minX = _x - halfWidth;
        float maxX = _x + halfWidth;
        float minY = _y - halfHeight;
        float maxY = _y + halfHeight;

        float otherMinX = other._x - otherHalfWidth;
        float otherMaxX = other._x + otherHalfWidth;
        float otherMinY = other._y - otherHalfHeight;
        float otherMaxY = other._y + otherHalfHeight;

        return (minX <= otherMaxX && maxX >= otherMinX &&
            minY <= otherMaxY && maxY >= otherMinY);
    }

    bool operator==(const GameObject& other) const {
        return _id == other._id;
    }
};