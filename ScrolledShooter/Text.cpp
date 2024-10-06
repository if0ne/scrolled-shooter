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

void Text::Render(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = _x;
    rect.y = _y;
    rect.w = _text.size() * _size;
    rect.h = _size * 1.7f;

    SDL_RenderCopy(renderer, _message, nullptr, &rect);
}

void Text::RenderCenter(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = _x - (_text.size() * _size) / 2;
    rect.y = _y - _size * 1.7f / 2;
    rect.w = _text.size() * _size;
    rect.h = _size * 1.7f;

    SDL_RenderCopy(renderer, _message, nullptr, &rect);
}