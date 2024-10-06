import GameObject;

bool GameObject::IsIntersect(const GameObject& other) const {
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