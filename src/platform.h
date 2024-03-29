#include "main.h"
#include "player.h"
#ifndef PLATFORM_H
#define PLATFORM_H


class Platform {
public:
    Platform() {}
    Platform(float x, float y,float depth);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
    void tick(Player* p);
    void move();
private:
    VAO *object;
};

#endif // BALL_H
