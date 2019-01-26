#include "main.h"
#include "player.h"
#ifndef TUNNEL_H
#define TUNNEL_H


class Tunnel {
public:
    Tunnel() {}
    Tunnel(float x, float y);
    glm::vec3 position;
    float rotation;
    float friction;
    float gravity;
    float yspeed;
    float xspeed;
    void draw(glm::mat4 VP);
    void tick(Player* hooman);
    void set_position(float x, float y);
    bool detect_collision(bounding_box_t a, bounding_box_t b);
    double speed;
private:
    VAO *object;
};

#endif // MAGNET_H
