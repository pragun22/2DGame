#include "dragon.h"
#include "main.h"

Dragon::Dragon(float x, float y) {
    const GLfloat vertex_buffer_data[]={
    // Main Body
    0, 0, 0,
    0, 1.0f, 0,
    3.0f, 1.5f,0,

    0, 0, 0,
    3.0f, -0.5f, 0,
    3, 1.5f, 0,
    // main body ends here
    //tail
    0, 0, 0,
    0, 1, 0,
    -1.0f, 0.25f, 0,

    -1, 0.25f, 0,
    -1, 0.75f, 0,
    0, 1, 0,

    -1, 0.25f, 0,
    -1, 0.75f, 0,
    -2, -1, 0,
    // tail ends here

    /* legs */
    0, 0, 0,
    0, -1.0f, 0,
    1, -1.0f, 0,

    0, -1.0f, 0,
    1.0f, -1.0f, 0,
    1.0f, -1.25f, 0,

    1.0f, -1.0f, 0,
    1.0f, -1.25f, 0,
    2.0f, -1.25f, 0,

    3.0f, -0.5f, 0,
    3.0f, -1.0f, 0,
    4.0f, -1.0f, 0,

    3.0f, -1.0f, 0,
    4.0f, -1.0f, 0,
    4.0f ,-1.25f, 0,
    
    4.0f, -1.0f, 0,
    4.0f, -1.25f, 0,
    5.0f, -1.25f, 0,

    //head
    3.0f, -0.5f, 0.0f,
    3.0f, 1.5f, 0.0f,
    4.0f, 0.0f, 0.0f,

    3.0f, 1.5f, 0.0f,
    4.0f, 0.0f, 0.0f,
    5.0f, 1.0f, 0.0f,
    
    3.0f, 1.5f, 0.0f,
    5.0f, 1.0f, 0.0f,
    5.0f, 2.0f, 0.0f,
    
    5.0f, 1.0f, 0.0f,
    5.0f, 2.0f, 0.0f,
    6.0f, 2.0f, 0.0f,
    
    5.0f, 2.0f, 0.0f,
    6.0f, 2.0f, 0.0f,
    6.0f, 3.0f, 0.0f,
    
    6.0f, 2.0f, 0.0f,
    6.0f, 3.0f, 0.0f,
    7.0f, 2.0f, 0.0f,

    //wing
    0.0, 0.0, 0,
    3.0f, -0.5f, 0,
    4.0f, 6.0f, 0,

    0.0f, 1.0f, 0,
    3.0f, 1.5f, 0,
    3.0f, 6.0f, 0


    };
    this->object = create3DObject(GL_TRIANGLES, 18*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
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

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
