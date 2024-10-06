export module GameObject;

#pragma once
#include <SDL.h>

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
    bool IsIntersect(const GameObject& other) const;

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

    bool operator==(const GameObject& other) const {
        return _id == other._id;
    }
};