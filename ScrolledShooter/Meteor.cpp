import Meteor;
import Game;

void Meteor::Update(float dt) {
    _x += _velocityX * dt;
    _y += _velocityY * dt;

    if (IsIntersect(*Game::Instance().Player().get())) {
        Game::Instance().KillPlayer();
        return;
    }

    auto enemies = Game::Instance().Enemies();
    for (auto& enemy : enemies) {
        if (enemy->IsCollidable() && IsIntersect(*enemy.get())) {
            Game::Instance().DestroyEnemy(*enemy.get());
        }
    }

    if (_y > Game::kScreenHeight + _height / 2.0) {
        Game::Instance().DestroyMeteor(*this);
    }
}