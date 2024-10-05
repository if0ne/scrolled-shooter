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

export class Game {
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

    uint64_t _lastTick;

    Game() : _isRunning(true) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::exception(SDL_GetError());
        }

        _window = SDL_CreateWindow("Scrolled Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    }

    void Initialize() {
        _playerShip = std::make_shared<PlayerShip>(150, 720 / 2, 5);

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
        _playerController->Update();
        _playerShip->Update(dt);

        for (auto& bullet : _bullets) {
            bullet->Update(dt);
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
    }

    void Render() {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);

        _playerShip->Render(_renderer);

        for (auto& bullet : _bullets) {
            bullet->Render(_renderer);
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
};

Game* Game::_instance = nullptr;