#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->friction = 0.95;
    this->gravity = 0.01;
    speed = 0.01;
    this->yspeed = 0;
    int n = 400;
    int inc = 1;
    const GLfloat vertex_buffer_data[]={
        0, 0, 0,  //pant starts here
        0.5f, 0, 0,
        0, -1, 0,

        0.5F, 0, 0,
        0.375f, -0.25f, 0,
        0.875f, -0.25f, 0, 
        
        0.5f, 0, 0,
        1, 0, 0,
        1, -1, 0,  //pant ends here

        0, 0, 0, //main body
        0, 1, 0,
        1, 0, 0,

        0, 1, 0,
        1, 0, 0,
        1, 1, 1, //main body end

        0, 1, 0, //head starts
        1, 1, 0,
        0, 1.4f, 0  // head stops
    };
    const GLfloat color_buffer[]={
        209.0/256.0, 116.0/256.0, 22.0/256.0,
        209.0/256.0, 116.0/256.0, 22.0/256.0,
        209.0/256.0, 116.0/256.0, 22.0/256.0,

        209.0/256.0, 116.0/256.0, 22.0/256.0,
        209.0/256.0, 116.0/256.0, 22.0/256.0,
        209.0/256.0, 116.0/256.0, 22.0/256.0,

        209.0/256.0, 116.0/256.0, 22.0/256.0,
        209.0/256.0, 116.0/256.0, 22.0/256.0,
        209.0/256.0, 116.0/256.0, 22.0/256.0,

        232.0/256.0, 44.0/256.0, 112.0/256.0,
        232.0/256.0, 44.0/256.0, 112.0/256.0,
        232.0/256.0, 44.0/256.0, 112.0/256.0,

        232.0/256.0, 44.0/256.0, 112.0/256.0,
        232.0/256.0, 44.0/256.0, 112.0/256.0,
        232.0/256.0, 44.0/256.0, 112.0/256.0,

        81.0/256.0, 65.0/256.0, 13.0/256.0,
        81.0/256.0, 65.0/256.0, 13.0/256.0,
        81.0/256.0, 65.0/256.0, 13.0/256.0
    };
    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color_buffer, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Player::jump(){
    this->yspeed = 0.215f;
}
void Player::move(int l)
{
    if(l) this->xspeed = 0.075f;
    else this->xspeed = -1*0.075f;
}

void Player::tick(){
    this->position.x +=this->xspeed;
    this->position.y += this->yspeed;
    if(this->position.y<0)
    {
        this->yspeed = 0;
        this->position.y = 0;
    }
    if(this->yspeed!=0)
    {
        this->yspeed += -1*0.015;
    }
    if(this->xspeed>0)
    {
        this->xspeed -= 0.010;
        if(this->xspeed<0) this->xspeed = 0;
    }
    if(this->xspeed<0)
    {
        this->xspeed += 0.010;
        if(this->xspeed>0) this->xspeed = 0;
    }
}
