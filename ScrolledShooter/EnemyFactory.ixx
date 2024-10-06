#pragma once
#include <memory>

export module EnemyFactory;

import Enemy;

export class EnemyFactory {
private:
    int _active;
    int _maxActive;
    int _deadCounter;

    float _spawnRate;
    float _lastSpawnTime;
public:
    EnemyFactory(float spawnRate)
        : _active(0)
        , _maxActive(2)
        , _deadCounter(0)
        , _spawnRate(spawnRate)
        , _lastSpawnTime(0.0)
    {}

    void Update();
    void HandleDeadEnemy();
    std::shared_ptr<Enemy> RandomEnemy();
};