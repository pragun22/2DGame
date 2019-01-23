#include "main.h"
#ifndef BALLOON_H
#define BALLOON_H


class Balloon {
public:
    Balloon() {}
    Balloon(float x, float y,float a,float b);
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
