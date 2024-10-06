export module Meteor;

import GameObject;

export class Meteor : public GameObject {
private:
    float _velocityX;
    float _velocityY;
public:
    Meteor(float x, float y, float velocityX, float velocityY)
        : GameObject(x, y, 100.0f, 100.0f)
        , _velocityX(velocityX)
        , _velocityY(velocityY)
    {}

    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
};