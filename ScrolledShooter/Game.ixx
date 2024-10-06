#pragma once
#include <iostream>
#include <exception>
#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

export module Game;

export class PlayerShip;
export class Game;

import Bullet;
import GameObject;
import PlayerShip;
import PlayerController;
import Meteor;
import MeteorManager;
import Text;

import Enemy;
import Bird;
import Bomber;
import Fighter;
import EnemyFactory;

enum class GameState {
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

    void Initialize() {
        _scoreText = std::make_unique<Text>(10.0, 10.0, 24.0, "0");

        _playerShip = std::make_shared<PlayerShip>(150, kScreenHeight / 2, 0.500f);
        _playerController = std::make_shared<PlayerController>(_playerShip);

        _enemyFactory = std::make_unique<EnemyFactory>(1.5f);
        _meteorManager = std::make_unique<MeteorManager>();
        _prevScore = _score;
        _score = 0;

        _bullets.clear();
        _bulletsToCreate.clear();
        _bulletsToRemove.clear();

        _enemies.clear();
        _enemyToCreate.clear();
        _enemyToRemove.clear();

        _meteors.clear();
        _meteorToCreate.clear();
        _meteorToRemove.clear();

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

            switch (_state) {
            case GameState::Running:
                ProcessEventsInGame(event);
                break;
            case GameState::End:
                ProcessEventsInEnd(event);
                break;
            }
        }
    }

    void ProcessEventsInGame(SDL_Event& event) {
        _playerController->ProcessEvent(event);
    }

    void ProcessEventsInEnd(SDL_Event& event) {
        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            Initialize();
            _state = GameState::Running;
            break;
        }
    }

    void Update(float dt) {
        if (_state == GameState::Running) {
            _enemyFactory->Update();
            _meteorManager->Update();

            _playerController->Update();
            _playerShip->Update(dt);

            for (auto& bullet : _bullets) {
                bullet->Update(dt);
            }

            for (auto& enemy : _enemies) {
                enemy->Update(dt);
            }

            for (auto& meteor : _meteors) {
                meteor->Update(dt);
            }
        }
    }

    void PostUpdate() {
        if (_state == GameState::Running) {
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
                std::shared_ptr<Bullet> objToCreate = _bulletsToCreate.back();
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
                std::shared_ptr<Enemy> objToCreate = _enemyToCreate.back();
                _enemies.push_back(std::move(objToCreate));
                _enemyToCreate.pop_back();
            }

            while (!_meteorToRemove.empty()) {
                Meteor& objToRemove = _meteorToRemove.back();
                _meteors.erase(std::remove_if(
                    _meteors.begin(),
                    _meteors.end(),
                    [&](auto& p) {
                        return objToRemove.Id() == p->Id();
                    }
                ), _meteors.end());
                _meteorToRemove.pop_back();
            }


            while (!_meteorToCreate.empty()) {
                std::shared_ptr<Meteor> objToCreate = _meteorToCreate.back();
                _meteors.push_back(std::move(objToCreate));
                _meteorToCreate.pop_back();
            }
        }
    }

    void Render() {
        switch (_state)
        {
        case GameState::Running:
            RenderInGame();
            break;
        case GameState::End:
            RenderInEnd();
            break;
        default:
            break;
        }
    }

    void RenderInGame() {
        SDL_SetRenderDrawColor(_renderer, 66, 170, 255, 255);
        SDL_RenderClear(_renderer);

        SDL_Rect rect = { 0.0, kScreenHeight - 10, kScreenWidth, kScreenHeight };
        SDL_SetRenderDrawColor(_renderer, 0, 230, 0, 255);
        SDL_RenderFillRect(_renderer, &rect);

        _playerShip->Render(_renderer);

        for (auto& bullet : _bullets) {
            bullet->Render(_renderer);
        }

        for (auto& enemy : _enemies) {
            enemy->Render(_renderer);
        }

        for (auto& meteor : _meteors) {
            meteor->Render(_renderer);
        }

        _scoreText->Render(_renderer);

        SDL_RenderPresent(_renderer);
    }

    void RenderInEnd() {
        SDL_SetRenderDrawColor(_renderer, 66, 170, 255, 255);
        SDL_RenderClear(_renderer);

        SDL_Rect rect = { 0.0, kScreenHeight - 10, kScreenWidth, kScreenHeight };
        SDL_SetRenderDrawColor(_renderer, 0, 230, 0, 255);
        SDL_RenderFillRect(_renderer, &rect);

        _endText->Render(_renderer);

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

    void KillPlayer() {
        if (_score > _prevScore) {
            std::string output = "New record: ";
            output += std::to_string(_score);
            _endText = std::make_unique<Text>(kScreenWidth / 2, kScreenHeight / 2, 24, std::move(output));
        } else {
            _endText = std::make_unique<Text>(kScreenWidth / 2, kScreenHeight / 2, 24, "You lose!");
        }
        _state = GameState::End;
    }

    void AddScore(uint64_t score) {
        _score += score;
        _scoreText->SetText(std::to_string(_score));
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