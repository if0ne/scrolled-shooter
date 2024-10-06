import Enemy;
import Game;

void Enemy::Update(float dt) {
    if (_x < -100.0
        || _x > Game::kScreenWidth + 100.0) {
        Game::Instance().DestroyEnemy(*this);
    }

    if (IsIntersect(*Game::Instance().Player().get())) {
        Game::Instance().KillPlayer();
    }
}