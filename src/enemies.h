#include "main.h"
#include "player.h"
#ifndef ENEMIES_H
#define ENEMIES_H


class Firelines {
public:
    Firelines() {}
    Firelines(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
    void move();
    void tick();
    void set_position(float x, float y);
private:
    VAO *object;
};

class Firebeams {
public:
    Firebeams() {}
    Firebeams(float x, float y);
    glm::vec3 position;
    float rotation;
    bool flag;
    clock_t time;
    void draw(glm::mat4 VP);
    double speed;
    void move();
    void tick(Player* hooman);
    void set_position(float x, float y);
private:
    VAO *object;
};

#endif // BALL_H
