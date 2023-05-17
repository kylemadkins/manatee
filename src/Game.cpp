#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "spdlog/spdlog.h"

#include "Game.h"

glm::vec2 playerPos;
glm::vec2 playerVel;

Game::Game() {
  isRunning = false;
}

Game::~Game() {}

void Game::Initialize() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    spdlog::error("Unable to initialize SDL");
    return;
  }

  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);
  windowWidth = displayMode.w;
  windowHeight = displayMode.h;
  window = SDL_CreateWindow(
    "Manatee",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    windowWidth,
    windowHeight,
    SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN
  );
  if (!window) {
    spdlog::error("Unable to create a window");
    return;
  }

  renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );
  if (!renderer) {
    spdlog::error("Unable to create a renderer");
    return;
  }

  const int targetWidth = 1280;
  const int targetHeight = 720;

  float scaleX = static_cast<float>(windowWidth) / targetWidth;
  float scaleY = static_cast<float>(windowHeight) / targetHeight;
  float scale = std::min(scaleX, scaleY);

  int logicalWidth = static_cast<int>(targetWidth * scale);
  int logicalHeight = static_cast<int>(targetHeight * scale);

  SDL_RenderSetLogicalSize(renderer, logicalWidth, logicalHeight);

  isRunning = true;

  spdlog::info("Game initialized");
}

void Game::Run() {
  Setup();
  while (isRunning) {
    ProcessInput();
    Update();
    Render();
  }
}

void Game::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Game::Setup() {
  playerPos = glm::vec2(0, 0);
  playerVel = glm::vec2(100.0, 0.0);
}

void Game::ProcessInput() {
  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    switch(sdlEvent.type) {
      case SDL_QUIT:
        isRunning = false;
        break;
      case SDL_KEYDOWN:
        if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
          isRunning = false;
        }
        break;
    }
  }
}

void Game::Update() {
  double deltaTime = (SDL_GetTicks() - previousTicks) / 1000.0;
  previousTicks = SDL_GetTicks();

  playerPos.x += playerVel.x * deltaTime;
  playerPos.y += playerVel.y * deltaTime;
}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderFillRect(renderer, NULL);

  SDL_Surface* tankSurface = IMG_Load("../assets/images/tank-tiger-right.png");
  SDL_Texture* tankTexture = SDL_CreateTextureFromSurface(renderer, tankSurface);
  SDL_FreeSurface(tankSurface);
  SDL_Rect tankRect = {
    static_cast<int>(playerPos.x),
    static_cast<int>(playerPos.y),
    32,
    32
  };
  SDL_RenderCopy(renderer, tankTexture, NULL, &tankRect);
  SDL_DestroyTexture(tankTexture);

  SDL_RenderPresent(renderer);
}
