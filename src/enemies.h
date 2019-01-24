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
    bool detect_collision(bounding_box_t a);
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
    float facto;
    clock_t time;
    void draw(glm::mat4 VP);
    double speed;
    void move();
    void reset();
    void tick(Player* hooman);
    void set_position(float x, float y);
private:
    VAO *object;
};
class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, float cen_x, float cen_y);
    glm::vec3 position;
    float rotation;
    bool flag;
    float x;
    float y;
    float degree;
    clock_t time;
    void draw(glm::mat4 VP);
    double speed;
    void move();
    void tick();
    void set_position(float x, float y);
private:
    VAO *object;
};

#endif // BALL_H
