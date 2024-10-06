import Bullet;
import Game;

void Bullet::Update(float dt) {
    _x += _velocityX * dt;
    _y += _velocityY * dt;

    _velocityY += _acceleration * dt;

    if (_x < 0.0
        || _x > Game::kScreenWidth
        || _y < 0.0
        || _y > Game::kScreenHeight) {
        Game::Instance().DestroyBullet(*this);
    }
}