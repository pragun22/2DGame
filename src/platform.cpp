#include "platform.h"
#include "main.h"

Platform::Platform(float x, float y, float depth) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    GLfloat vertex_buffer_data[]={
        0, 0, 0,
        0, depth, 0,
        3, depth, 0, // square 2
        
        0, 0, 0,
        3, depth, 0,
        3, 0, 0, //square 1

        3, 0, 0,
        6, depth, 0,
        3, depth, 0, //square 3
        
        6, 0, 0,
        6, depth, 0,
        3, 0, 0 //square 4
        
    };
    int i,inc=0;
    for(i=0;i<12;i++)
    {
        vertex_buffer_data[i] = 0+inc;
        vertex_buffer_data[i+1] = 0;
        vertex_buffer_data[i+2] = 0;
        vertex_buffer_data[i+3] = 0+inc;
        vertex_buffer_data[i+4] = depth;
        vertex_buffer_data[i+5] = 0;
        vertex_buffer_data[i+6] = 3+inc;
        vertex_buffer_data[i+7] = depth;
        vertex_buffer_data[i+8] = 0;
        vertex_buffer_data[i+9] = 0+inc;
        vertex_buffer_data[i+10] = 0;
        vertex_buffer_data[i+11] = 0;
        vertex_buffer_data[i+12] = 3+inc;
        vertex_buffer_data[i+13] = depth;
        vertex_buffer_data[i+14] = 0;
        vertex_buffer_data[i+15] = 3+inc;
        vertex_buffer_data[i+16] = 0;
        vertex_buffer_data[i+17] = 0;
    }
    const GLfloat color_buffer[]={
        98.0/256.0, 244.0/256.0, 66.0/256.0,
        98.0/256.0, 244.0/256.0, 66.0/256.0,
        98.0/256.0, 244.0/256.0, 66.0/256.0,
        98.0/256.0, 244.0/256.0, 66.0/256.0,
        98.0/256.0, 244.0/256.0, 66.0/256.0,
        98.0/256.0, 244.0/256.0, 66.0/256.0, //green

        66.0/256.0, 134.0/256.0, 244.0/256.0,
        66.0/256.0, 134.0/256.0, 244.0/256.0,
        66.0/256.0, 134.0/256.0, 244.0/256.0,
        66.0/256.0, 134.0/256.0, 244.0/256.0,
        66.0/256.0, 134.0/256.0, 244.0/256.0,
        66.0/256.0, 134.0/256.0, 244.0/256.0 // blue
    };
    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color_buffer, GL_FILL);
}

void Platform::draw(glm::mat4 VP) {
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

void Platform::move(){

}