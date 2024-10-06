#include <SDL.h>

#include <memory>
#include <math.h>

import MeteorManager;
import Meteor;
import Game;
import Utility;

void MeteorManager::Update() {
    float tick = SDL_GetTicks64() / 1000.0;
    float elapsed = (tick - _lastSpawnTime);

    if (elapsed > _spawnTime) {
        _lastSpawnTime = tick;
        
        int randomY = Random(0, Game::kScreenHeight);

        float y = randomY + 500.0;
        float x = -Game::kScreenWidth;
        float len = sqrtf(x * x + y * y);

        float ny = y / len;
        float nx = x / len;
        float randomSpeed = Random(400.0f, 500.0f);

        Game::Instance().SpawnMeteor(std::make_shared<Meteor>(
            Game::kScreenWidth,
            -500.0,
            nx * randomSpeed,
            ny * randomSpeed
        ));

        _spawnTime = Random(15.0f, 25.0f);
    }
}