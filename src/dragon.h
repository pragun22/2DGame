#include "main.h"
#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
    float xthrust;
    float ythrust;
    float xspeed;
    float yspeed;
    void move();
    void tick();
    void set_position(float x, float y);
    bool detect_collision(bounding_box_t a);
private:
    VAO *object;
};

#endif // BALL_H
