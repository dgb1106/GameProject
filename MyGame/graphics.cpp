#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"
#include "defs.h"

void logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) logErrorAndExit("SDL_Init", SDL_GetError());

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logErrorAndExit("Create Window", SDL_GetError());

    windowIcon = IMG_Load(WINDOW_ICON);
    SDL_SetWindowIcon(window, windowIcon);

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) logErrorAndExit("SDL_image error:", IMG_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logErrorAndExit("Create Renderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Graphics::prepareScene() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Graphics::prepareScene(SDL_Texture* texture) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void Graphics::presentScene() {
    SDL_RenderPresent(renderer);
}

SDL_Texture* Graphics::loadTexture(const char* filename) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s: ", filename);

    SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
    if (texture == nullptr) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s ", IMG_GetError());

    return texture;
}

void Graphics::renderTexture(SDL_Texture* texture, int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Graphics::renderTexture(SDL_Texture* texture, int x, int y, double angle) {
    SDL_Rect dest;
    dest.x = x - 64;
    dest.y = y;

    SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);

    SDL_RenderCopyEx(renderer, texture, nullptr, &dest, angle * 180 / PI - 180, nullptr, SDL_FLIP_NONE);
}

SDL_Texture* Graphics::renderText(const char* text, TTF_Font* font, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,"Render text surface %s", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (texture == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,"Create texture from text %s", SDL_GetError());
        return nullptr;
    }

    return texture;
}

void Graphics::render(const ScrollingBackground& bgr) {
    renderTexture(bgr.texture, bgr.scrollingOffset, 0);
    renderTexture(bgr.texture, bgr.scrollingOffset - bgr.width, 0);
}

void Graphics::render(int x, int y, const Sprite& sprite) {
    const SDL_Rect* clip = sprite.getCurrentClip();
    SDL_Rect renderQuad = {x, y, clip->w, clip->h};
    SDL_RenderCopy(renderer, sprite.texture, clip, &renderQuad);
}

void Graphics::quit() {
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(windowIcon);

    SDL_Quit();
}

void ScrollingBackground::setTexture(SDL_Texture* _texture) {
    texture = _texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

void ScrollingBackground::scroll(int distance) {
    scrollingOffset -= distance;
    if (scrollingOffset < 0) scrollingOffset = width;
}

Sprite::Sprite(SDL_Texture* _texture, Vector _position) : texture(_texture), position(_position) {
    SDL_Rect clip;
    for (int i = 0; i < BOX_FRAMES; i++) {
        clip.x = BOX_CLIPS[i][0];
        clip.y = BOX_CLIPS[i][1];
        clip.w = BOX_CLIPS[i][2];
        clip.h = BOX_CLIPS[i][3];
        clips.push_back(clip);
    }
}

void Sprite::tick() {
    currentFrame = (currentFrame + 1) % clips.size();
}
