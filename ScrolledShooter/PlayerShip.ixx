export module PlayerShip;

import GameObject;
import Utility;

export class PlayerShip : public GameObject {
private:
    float _targetY;

    float _velocityY;
    float _acceleration;
    float _prevSign;
    float _moveThreshold;

    float _fireRate;
    float _lastShotTime;
public:
    PlayerShip(float x, float y, float fireRate) 
        : GameObject(x, y, 150.0f, 75.0f)
        , _targetY(y)
        , _moveThreshold(_height / 4.0f)
        , _velocityY(0.0f)
        , _acceleration(1700.0f)
        , _prevSign(1.0f)
        , _fireRate(fireRate)
        , _lastShotTime(0.0)
    {}

    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
    void Shoot();

    void TargetY(float y) {
        _targetY = y;
    }

    float TargetY() {
        return _targetY;
    }
};