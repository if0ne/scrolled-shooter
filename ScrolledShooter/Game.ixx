#pragma once
#include <iostream>
#include <exception>
#include <vector>

#include <SDL.h>

export module Game;

export class PlayerShip;
export class Game;

import Bullet;
import GameObject;
import PlayerShip;
import PlayerController;
import Enemy;

import Bird;
import Bomber;
import Fighter;

import EnemyFactory;

export class Game {
public:
    static const int kScreenWidth = 1280;
    static const int kScreenHeight = 720;
private:
    static Game* _instance;

    bool _isRunning;
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

    std::shared_ptr<PlayerController> _playerController;
    std::shared_ptr<PlayerShip> _playerShip;

    std::vector<std::shared_ptr<Bullet>> _bullets;

    std::vector<std::shared_ptr<Bullet>> _bulletsToCreate;
    std::vector<std::reference_wrapper<Bullet>> _bulletsToRemove;

    std::vector<std::shared_ptr<Enemy>> _enemies;

    std::vector<std::shared_ptr<Enemy>> _enemyToCreate;
    std::vector<std::reference_wrapper<Enemy>> _enemyToRemove;

    uint64_t _lastTick;

    std::unique_ptr<EnemyFactory> _enemyFactory;

    Game() 
        : _isRunning(true)
        , _enemyFactory(std::make_unique<EnemyFactory>(1.5f))
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::exception(SDL_GetError());
        }

        _window = SDL_CreateWindow("Scrolled Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kScreenWidth, kScreenHeight, 0);
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    }

    void Initialize() {
        _playerShip = std::make_shared<PlayerShip>(150, kScreenHeight / 2, 0.500f);

        _playerController = std::make_shared<PlayerController>(_playerShip);

        _lastTick = SDL_GetTicks64();
    }

    void ProcessEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                _isRunning = false;
                break;
            }

            _playerController->ProcessEvent(event);
        }
    }

    void Update(float dt) {
        _enemyFactory->Update();

        _playerController->Update();
        _playerShip->Update(dt);

        for (auto& bullet : _bullets) {
            bullet->Update(dt);
        }

        for (auto& enemy : _enemies) {
            enemy->Update(dt);
        }
    }

    void PostUpdate() {
        while (!_bulletsToRemove.empty()) {
            Bullet& objToRemove = _bulletsToRemove.back();
            _bullets.erase(std::remove_if(
                _bullets.begin(),
                _bullets.end(),
                [&](auto& p) {
                    return objToRemove.Id() == p->Id();
                }
            ), _bullets.end());
            _bulletsToRemove.pop_back();
        }


        while (!_bulletsToCreate.empty()) {
            std::shared_ptr<Bullet> objToCreate = std::move(_bulletsToCreate.back());
            _bullets.push_back(std::move(objToCreate));
            _bulletsToCreate.pop_back();
        }

        while (!_enemyToRemove.empty()) {
            Enemy& objToRemove = _enemyToRemove.back();
            _enemies.erase(std::remove_if(
                _enemies.begin(),
                _enemies.end(),
                [&](auto& p) {
                    return objToRemove.Id() == p->Id();
                }
            ), _enemies.end());
            _enemyToRemove.pop_back();
        }


        while (!_enemyToCreate.empty()) {
            std::shared_ptr<Enemy> objToCreate = std::move(_enemyToCreate.back());
            _enemies.push_back(std::move(objToCreate));
            _enemyToCreate.pop_back();
        }
    }

    void Render() {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);

        _playerShip->Render(_renderer);

        for (auto& bullet : _bullets) {
            bullet->Render(_renderer);
        }

        for (auto& enemy : _enemies) {
            enemy->Render(_renderer);
        }

        SDL_RenderPresent(_renderer);
    }
public:
    ~Game() {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    static Game& Instance() {
        if (_instance == nullptr) {
            _instance = new Game{};
        }

        return *_instance;
    }

    static void ResetInstance() {
        if (_instance != nullptr) {
            delete _instance;
        }

        _instance = nullptr;
    }

    void Run() {
        std::cout << "Running game" << std::endl;

        Initialize();
        while (_isRunning) {
            uint64_t currentTick = SDL_GetTicks64();
            float deltaTime = (currentTick - _lastTick) / 1000.0;
            _lastTick = currentTick;

            ProcessEvents();
            Update(deltaTime);
            PostUpdate();
            Render();
        }

        std::cout << "Exiting from game" << std::endl;

        ResetInstance();
    }

    void DestroyBullet(Bullet& object) {
        _bulletsToRemove.push_back(object);
    }

    void SpawnBullet(std::shared_ptr<Bullet>&& object) {
        _bulletsToCreate.push_back(std::move(object));
    }

    void DestroyEnemy(Enemy& object) {
        _enemyFactory->HandleDeadEnemy();
        _enemyToRemove.push_back(object);
    }

    void SpawnEnemy(std::shared_ptr<Enemy>&& object) {
        _enemyToCreate.push_back(std::move(object));
    }

    void KillPlayer() {
        std::cout << "You lose!" << std::endl;
    }

    std::shared_ptr<PlayerShip> Player() const {
        return _playerShip;
    }

    const std::vector<std::shared_ptr<Enemy>>& Enemies() const {
        return _enemies;
    }

    const std::vector<std::shared_ptr<Bullet>>& Bullets() const {
        return _bullets;
    }
};

Game* Game::_instance = nullptr;