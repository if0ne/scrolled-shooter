import Enemy;
import Game;

void Enemy::Update(float dt) {
    if (_x < 0.0
        || _x > Game::kScreenWidth
        || _y < 0.0
        || _y > Game::kScreenHeight) {
        Game::Instance().DestroyEnemy(*this);
    }

    if (IsIntersect(*Game::Instance().Player().get())) {
        Game::Instance().KillPlayer();
    }
}