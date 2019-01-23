#include "main.h"
#include "main.h"
#ifndef CIRCULAR_H
#define CIRCULAR_H


class Circular {
public:
    Circular() {}
    Circular(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
    void move();
    void tick();
    void set_position(float x, float y);
    bool detect_collision(bounding_box_t a);
private:
    VAO *object;
};

#endif // BALL_H
