#include "main.h"
#include "player.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color, float r);
    glm::vec3 position;
    float rotation;
    float friction;
    float r;
    bool tick(Player* hooman);
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
