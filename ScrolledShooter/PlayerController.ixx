#pragma once
#include <SDL.h>
#include <memory>

export module PlayerController;

import PlayerShip;

export class PlayerController {
private:
    std::shared_ptr<PlayerShip> _player;

    bool _isHoldingShoot;
public:
    PlayerController(std::shared_ptr<PlayerShip> player)
        : _player(player)
        , _isHoldingShoot(false)
    {}

    void ProcessEvent(const SDL_Event& e) {
        switch (e.type) {
        case SDL_MOUSEMOTION:
            _player->TargetY(e.motion.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT) {
                _isHoldingShoot = true;
            }   
            break;
        case SDL_MOUSEBUTTONUP:
            if (e.button.button == SDL_BUTTON_LEFT) {
                _isHoldingShoot = false;
            }
            break;
        }
    }

    void Update() {
        if (_isHoldingShoot) {
            _player->Shoot();
        }
    }
};