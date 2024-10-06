#include <SDL_ttf.h>
#include <string>

import Text;
import Game;

void Text::SetText(std::string&& text) {
    _text = text;

    if (_surfaceMessage) {
        SDL_FreeSurface(_surfaceMessage);
    }

    if (_message) {
        SDL_DestroyTexture(_message);
    }

    _surfaceMessage = TTF_RenderText_Solid(_font, _text.c_str(), _color);
    _message = SDL_CreateTextureFromSurface(Game::Instance().Renderer(), _surfaceMessage);
}