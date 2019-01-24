#include "main.h"
#ifndef SCORE_H
#define SCORE_H


class One {
public:
    One() {}
    One(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void move();
    void tick();
    void set_position(float x, float y);
    bool detect_collision(bounding_box_t a);
private:
    VAO *object;
};

#endif // BALL_H
