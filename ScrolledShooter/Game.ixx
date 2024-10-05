#include <iostream>
#include <exception>
#include <vector>

#include <SDL.h>

export module Game;
export class Game;

import GameObject;
import PlayerShip;

export class Game {
private:
    static Game* _instance;

    bool _isRunning;
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

    std::vector<std::unique_ptr<GameObject>> _gameObjects;

    std::vector<std::unique_ptr<GameObject>> _objectToCreate;
    std::vector<std::reference_wrapper<GameObject>> _objectsToRemove;

    Game() : _isRunning(true) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::exception(SDL_GetError());
        }

        _window = SDL_CreateWindow("Scrolled Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    }

    void Initialize() {
        _gameObjects.push_back(std::make_unique<PlayerShip>());
    }

    void ProcessEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                _isRunning = false;
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_MOUSEBUTTONDOWN:
                break;
            }
        }
    }

    void Update() {
        for (auto& go : _gameObjects) {
            go->Update(1.0);
        }
    }

    void PostUpdate() {
        while (!_objectsToRemove.empty()) {
            GameObject& objToRemove = _objectsToRemove.back();
            _gameObjects.erase(std::remove_if(
                _gameObjects.begin(), 
                _gameObjects.end(), 
                [&](auto& p) {
                    return objToRemove.Id() == p->Id();
                }
            ), _gameObjects.end());
            _objectsToRemove.pop_back();
        }


        while (!_objectToCreate.empty()) {
            std::unique_ptr<GameObject> objToCreate = std::move(_objectToCreate.back());
            _gameObjects.push_back(std::move(objToCreate));
            _objectsToRemove.pop_back();
        }
    }

    void Render() {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);

        for (auto& go : _gameObjects) {
            go->Render(_renderer);
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
            ProcessEvents();
            Update();
            PostUpdate();
            Render();
        }

        std::cout << "Exiting from game" << std::endl;

        ResetInstance();
    }

    void RemoveGameObject(GameObject& object) {
        _objectsToRemove.push_back(object);
    }

    void CreateGameObject(std::unique_ptr<GameObject>&& object) {
        _objectToCreate.push_back(std::move(object));
    }
};

Game* Game::_instance = nullptr;