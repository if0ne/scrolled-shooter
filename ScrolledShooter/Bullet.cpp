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

    switch (_hitLayer)
    {
    case HitLayer::Player:
        if (IsIntersect(*Game::Instance().Player().get())) {
            Game::Instance().DestroyBullet(*this);
            Game::Instance().KillPlayer();
        }
        break;
    case HitLayer::Enemy:
        auto enemies = Game::Instance().Enemies();

        for (auto& enemy : enemies) {
            if (enemy->IsBulletCollidable() && IsIntersect(*enemy.get())) {
                Game::Instance().AddScore(1);
                Game::Instance().DestroyEnemy(*enemy.get());
                Game::Instance().DestroyBullet(*this);
                break;
            }
        }

        break;
    }
}