#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"

class MovementSystem: public System {
  public:
    MovementSystem();
    ~MovementSystem();
    void Update();
};

#endif
