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
    bool tick(Player* hooman);
    void set_position(float x, float y);
    bool detect_collision(bounding_box_t a, bounding_box_t b);
    double speed;
private:
    VAO *object;
};

#endif // MAGNET_H
