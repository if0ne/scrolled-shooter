export module Game;

#pragma once
#include <iostream>
#include <exception>
#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

import Bullet;
import GameObject;
import PlayerShip;
import PlayerController;
import Meteor;
import MeteorManager;
import Text;

import Enemy;
import EnemyFactory;

export enum class GameState {
    Running,
    End,
};

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

    std::vector<std::shared_ptr<Meteor>> _meteors;
    std::vector<std::shared_ptr<Meteor>> _meteorToCreate;
    std::vector<std::reference_wrapper<Meteor>> _meteorToRemove;

    uint64_t _lastTick;

    uint64_t _prevScore;
    uint64_t _score;
    std::unique_ptr<Text> _scoreText;
    std::unique_ptr<Text> _endText;

    std::unique_ptr<EnemyFactory> _enemyFactory;
    std::unique_ptr<MeteorManager> _meteorManager;

    GameState _state;

    Game() 
        : _isRunning(true)
        , _score(0)
        , _state(GameState::Running)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::exception(SDL_GetError());
        }

        if (TTF_Init() < 0) {
            throw std::exception(SDL_GetError());
        }

        _window = SDL_CreateWindow("Scrolled Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kScreenWidth, kScreenHeight, 0);
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    }

    void Initialize();

    void ProcessEvents();
    void ProcessEventsInGame(SDL_Event& event);
    void ProcessEventsInEnd(SDL_Event& event);

    void Update(float dt);
    void UpdateInGame(float dt);
    void PostUpdate();
    void PostUpdateInGame();

    void Render();
    void RenderInGame();
    void RenderInEnd();
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

    void Run();
    void KillPlayer();
    void AddScore(uint64_t score);

    void DestroyBullet(Bullet& object) {
        _bulletsToRemove.push_back(object);
    }

    void SpawnBullet(std::shared_ptr<Bullet> object) {
        _bulletsToCreate.push_back(object);
    }

    void DestroyEnemy(Enemy& object) {
        _enemyFactory->HandleDeadEnemy();
        _enemyToRemove.push_back(object);
    }

    void SpawnEnemy(std::shared_ptr<Enemy> object) {
        _enemyToCreate.push_back(object);
    }

    void DestroyMeteor(Meteor& object) {
        _meteorToRemove.push_back(object);
    }

    void SpawnMeteor(std::shared_ptr<Meteor> object) {
        _meteorToCreate.push_back(object);
    }

    SDL_Renderer* Renderer() const {
        return _renderer;
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