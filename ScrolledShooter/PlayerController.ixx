export module PlayerController;

#pragma once
#include <SDL.h>
#include <memory>

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

    void ProcessEvent(const SDL_Event& e);
    void Update();
};