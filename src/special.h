#include "main.h"
#ifndef SPECIAL_H
#define SPECIAL_H


class SpeedUp {
public:
    SpeedUp() {}
    SpeedUp(float x, float y, float bottom);
    glm::vec3 position;
    float rotation;
    float yspeed;
    float xspeed;
    float miny;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bool tick(float x);
    bool detect_collision(bounding_box_t a, bounding_box_t b);
    double speed;
private:
    VAO *object;
};
class CoinsUp {
public:
    CoinsUp() {}
    CoinsUp(float x, float y, float bottom);
    glm::vec3 position;
    float rotation;
    float yspeed;
    float miny;
    float xspeed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bool tick(float x);
    bool detect_collision(bounding_box_t a, bounding_box_t b);
    double speed;
private:
    VAO *object;
};
class Sword {
public:
    Sword() {}
    Sword(float x, float y, float bottom);
    glm::vec3 position;
    float rotation;
    float yspeed;
    float miny;
    float xspeed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bool tick(float x);
    bool detect_collision(bounding_box_t a, bounding_box_t b);
    double speed;
private:
    VAO *object;
};
#endif // MAGNET_H
