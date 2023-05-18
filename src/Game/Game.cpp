#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

#include "Game.h"
#include "../ECS/ECS.h"

Game::Game() {}

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
  /*
  Entity tank = registry.CreateEntity();
  tank.AddComponent<TransformComponent>();
  tank.AddComponent<BoxColliderComponent>();
  tank.AddComponent<SpriteComponent>("../assets/images/tank-tiger-right.png");
  */
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

  /*
  MovementSystem.Update();
  CollisionSystem.Update();
  */
}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Render game objects...

  SDL_RenderPresent(renderer);
}
