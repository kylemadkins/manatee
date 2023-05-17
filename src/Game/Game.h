#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game {
  private:
    bool isRunning = false;
    int previousTicks = 0;
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
