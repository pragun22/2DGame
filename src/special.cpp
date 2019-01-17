#include "special.h"
#include "main.h"
SpeedUp::SpeedUp(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    this->yspeed = 0;
    int n = 400;
    int inc = 1;
    const GLfloat vertex_buffer_data[]={
        0, 1.5, 0,  //pant starts here
        2, 1.5, 0,
        2, 1, 0,

        0, 1.5, 0,
        0, 1, 0,
        2, 1, 0, 
        
        0, 1, 0,
        0.7f, 1, 0,
        0, 0, 0,  //pant ends here

        0, 0, 0, //main body
        0.7, 1, 0,
        0.7, 0, 0,

        2, 0, 0,
        1.3, 0, 0,
        1.3, 1, 0, //main body end

        1.3, 1, 0, //head starts
        2, 1, 0,
        2, 0, 0  // head stops
    };
    const GLfloat color_buffer[]={
        233.0/256.0, 13.0/256.0, 13.0/256.0,
        233.0/256.0, 13.0/256.0, 13.0/256.0,
        233.0/256.0, 13.0/256.0, 13.0/256.0,//red
        
        24.0/256.0, 38.0/256.0, 161.0/256.0,
        24.0/256.0, 38.0/256.0, 161.0/256.0,
        24.0/256.0, 38.0/256.0, 161.0/256.0,//blue

        24.0/256.0, 38.0/256.0, 161.0/256.0,
        24.0/256.0, 38.0/256.0, 161.0/256.0,
        24.0/256.0, 38.0/256.0, 161.0/256.0,

        24.0/256.0, 38.0/256.0, 161.0/256.0,
        24.0/256.0, 38.0/256.0, 161.0/256.0,
        24.0/256.0, 38.0/256.0, 161.0/256.0,

        233.0/256.0, 13.0/256.0, 13.0/256.0,
        233.0/256.0, 13.0/256.0, 13.0/256.0,
        233.0/256.0, 13.0/256.0, 13.0/256.0,//red
        
        233.0/256.0, 13.0/256.0, 13.0/256.0,
        233.0/256.0, 13.0/256.0, 13.0/256.0,
        233.0/256.0, 13.0/256.0, 13.0/256.0,//red
        

    };
    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color_buffer, GL_FILL);
}

void SpeedUp::draw(glm::mat4 VP) {
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

void SpeedUp::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
bool SpeedUp::detect_collision(bounding_box_t a, bounding_box_t b) {
    bool x = a.x + a.width >= b.x && b.x + b.width >= a.x?true:false;
    bool y = a.y + a.height >= b.y && b.y + b.height >= a.y?true:false;
    return (x && y);
}