#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float friction;
    float gravity;
    float yspeed;
    float xspeed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void jump();
    void move(int l);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
