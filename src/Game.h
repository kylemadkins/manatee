#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

const int FPS = 60;
const int MS_PER_FRAME = 1000 / FPS;

class Game {
  private:
    bool isRunning;
    int previousFrameMs = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;

  public:
    int windowWidth;
    int windowHeight;

    Game();
    ~Game();
    void Initialize();
    void Run();
    void Destroy();
    void Setup();
    void ProcessInput();
    void Update();
    void Render();
};

#endif
