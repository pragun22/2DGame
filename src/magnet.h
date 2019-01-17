#include "main.h"
#include "player.h"
#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y);
    glm::vec3 position;
    float rotation;
    float friction;
    float gravity;
    float yspeed;
    float xspeed;
    void draw(glm::mat4 VP);
    void tick(Player* hooman);
    void set_position(float x, float y);
    double speed;
private:
    VAO *object;
};

#endif // MAGNET_H
