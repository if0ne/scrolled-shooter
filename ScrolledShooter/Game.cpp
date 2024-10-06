#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

import Game;

import Bullet;
import GameObject;
import PlayerShip;
import PlayerController;
import Meteor;
import MeteorManager;
import Text;

import Enemy;
import EnemyFactory;

void Game::Initialize() {
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

void Game::ProcessEvents() {
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

void Game::ProcessEventsInGame(SDL_Event& event) {
    _playerController->ProcessEvent(event);
}

void Game::ProcessEventsInEnd(SDL_Event& event) {
    switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
        Initialize();
        _state = GameState::Running;
        break;
    }
}

void Game::Update(float dt) {
    if (_state == GameState::Running) {
        UpdateInGame(dt);
    }
}

void Game::UpdateInGame(float dt) {
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

void Game::PostUpdate() {
    if (_state == GameState::Running) {
        PostUpdateInGame();
    }
}

void Game::PostUpdateInGame() {
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

void Game::Render() {
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

void Game::RenderInGame() {
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

void Game::RenderInEnd() {
    SDL_SetRenderDrawColor(_renderer, 66, 170, 255, 255);
    SDL_RenderClear(_renderer);

    SDL_Rect rect = { 0.0, kScreenHeight - 10, kScreenWidth, kScreenHeight };
    SDL_SetRenderDrawColor(_renderer, 0, 230, 0, 255);
    SDL_RenderFillRect(_renderer, &rect);

    _endText->Render(_renderer);

    SDL_RenderPresent(_renderer);
}

void Game::Run() {
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

void Game::KillPlayer() {
    if (_score > _prevScore) {
        std::string output = "New record: ";
        output += std::to_string(_score);
        _endText = std::make_unique<Text>(kScreenWidth / 2, kScreenHeight / 2, 24, std::move(output));
    }
    else {
        _endText = std::make_unique<Text>(kScreenWidth / 2, kScreenHeight / 2, 24, "You lose!");
    }
    _state = GameState::End;
}

void Game::AddScore(uint64_t score) {
    _score += score;
    _scoreText->SetText(std::to_string(_score));
}