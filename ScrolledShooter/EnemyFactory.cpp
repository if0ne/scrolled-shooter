#include <SDL.h>
#include <memory>

import Game;

import Enemy;
import Bird;
import Bomber;
import Fighter;

import Utility;

import EnemyFactory;

void EnemyFactory::Update() {
    float tick = SDL_GetTicks64() / 1000.0;
    float elapsed = (tick - _lastSpawnTime);

    if (_active < _maxActive && elapsed > _spawnRate) {
        _lastSpawnTime = tick;
        _active++;
        _spawnRate = std::max(_spawnRate - 0.01f, 0.2f);
        std::shared_ptr<Enemy> enemy = RandomEnemy();
        Game::Instance().SpawnEnemy(enemy);
    }

    if (_deadCounter == static_cast<int>(_maxActive * 1.5f)) {
        _deadCounter = 0;
        _maxActive += 2;
    }
}

void EnemyFactory::HandleDeadEnemy() {
    _active--;
    _deadCounter++;
}

std::shared_ptr<Enemy> EnemyFactory::RandomEnemy() {
    int random = Random(0, 2);

    switch (random) {
    case 0: {
        float offset = Random(-50.0f, 50.0f);
        return std::make_shared<Bird>(Game::kScreenWidth, Game::kScreenHeight - 100.0 + offset, -200.0f);
    }
    case 1: {
        int random = Random(0, 2);
        float offset = Random(-100.0f, 100.0f);

        if (random) {
            return std::make_shared<Bomber>(Game::kScreenWidth, 150.0f + offset, -450.0f);
        } else {
            return std::make_shared<Bomber>(Game::kScreenWidth, Game::kScreenHeight / 2 + offset, -450.0f);
        }
    }
    case 2: {
        int random = Random(0, 2);
        float offset = Random(-100.0f, 100.0f);

        if (random) {
            return std::make_shared<Fighter>(Game::kScreenWidth, Game::kScreenHeight / 2 + offset, -300.0f, Game::Instance().Player());
        } else {
            return std::make_shared<Fighter>(Game::kScreenWidth, Game::kScreenHeight / 2 + offset, -450.0f, Game::Instance().Player());
        }
    }
    default:
        throw std::exception("Broken random");
        break;
    }
}