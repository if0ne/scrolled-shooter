#pragma once
#include <SDL_ttf.h>
#include <string>

export module Text;

export class Text {
private:
    TTF_Font* _font = nullptr;
    SDL_Surface* _surfaceMessage = nullptr;
    SDL_Texture* _message = nullptr;
    SDL_Color _color = { 255, 255, 255 };

    std::string _text;

    float _x;
    float _y;
    float _size;
public:
    Text(float x, float y, float size, std::string&& text) 
        : _x(x)
        , _y(y)
        , _size(size)
    {
        _font = TTF_OpenFont("Sans.ttf", size);
        SetText(std::move(text));
    }

    ~Text() {
        if (_font) {
            TTF_CloseFont(_font);
        }

        if (_surfaceMessage) {
            SDL_FreeSurface(_surfaceMessage);
        }

        if (_message) {
            SDL_DestroyTexture(_message);
        }
    }

    void Render(SDL_Renderer* renderer) {
        SDL_Rect rect;
        rect.x = _x;
        rect.y = _y;
        rect.w = _text.size() * _size;
        rect.h = _size * 1.7f;

        SDL_RenderCopy(renderer, _message, nullptr, &rect);
    }

    void SetText(std::string&& text);
};