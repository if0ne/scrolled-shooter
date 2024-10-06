#include <SDL.h>
#include <memory>

import PlayerController;

void PlayerController::ProcessEvent(const SDL_Event& e) {
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

void PlayerController::Update() {
    if (_isHoldingShoot) {
        _player->Shoot();
    }
}