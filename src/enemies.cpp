#include "enemies.h"
#include "main.h"
Firelines::Firelines(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 62.0f;
    speed = 0.01;
    int n = 400;
    int inc = 1;
    const GLfloat vertex_buffer_data[]={
        0, 0 ,0,
        0, 3, 0,
        1, 3, 0,

        0, 0, 0,
        1, 0, 0,
        1, 3, 0, /* left dumble */

        1, 1, 0,
        4, 1, 0,
        1 ,2 ,0,

        4, 1, 0,
        4, 2, 0,
        1, 2, 0, // middle body

        4, 0, 0,
        5, 0, 0,
        4, 3 ,0,

        4, 3, 0,
        5, 3, 0,
        5, 0, 0 /* right dumble */
    };
    const GLfloat color_buffer[]={
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0,
 
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0, /* left dumble */
        
        220.0/256.0, 120.0/256.0, 109.0/256.0,
        220.0/256.0, 120.0/256.0, 109.0/256.0,
        220.0/256.0, 120.0/256.0, 109.0/256.0,

        220.0/256.0, 120.0/256.0, 109.0/256.0,
        220.0/256.0, 120.0/256.0, 109.0/256.0,
        220.0/256.0, 120.0/256.0, 109.0/256.0, /* middle body */

        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0,
  
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0, /* right dumble */
    };
    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color_buffer, GL_FILL);
}

void Firelines::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale (glm::vec3(1.3,0.45,0));    // glScalef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Firelines::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Firelines::tick(){
}

Firebeams::Firebeams(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0.0f;
    const GLfloat vertex_buffer_data[]={
        0, 0 ,0,
        0.2f, 1, 0,
        0.2f, 0, 0,

        0, 0, 0,
        0.2f, 0, 0,
        0.2f, -1, 0, /* left dumble */

        0.2f, 0.4f, 0,
        0.2f, -0.4f, 0,
        3.2f, -0.4f, 0,

        3.2f, 0.4, 0,
        3.2f, -0.4, 0,
        0.2, 0.4, 0, // middle body

        3.4, 0, 0,
        3.2, 1, 0,
        3.2, 0,0,

        3.4, 0, 0,
        3.2, 0, 0,
        3.2 , -1, 0 /* right dumble */
    };
    const GLfloat color_buffer[]={
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0,
 
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0, /* left dumble */
        
        242.0/256.0, 40.0/256.0, 34.0/256.0,
        242.0/256.0, 40.0/256.0, 34.0/256.0,
        242.0/256.0, 40.0/256.0, 34.0/256.0,

        242.0/256.0, 40.0/256.0, 34.0/256.0,
        242.0/256.0, 40.0/256.0, 34.0/256.0,
        242.0/256.0, 40.0/256.0, 34.0/256.0,/* middle body */

        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0,
  
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0,
        34.0/256.0, 34.0/256.0, 105.0/256.0, /* right dumble */
    };
    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color_buffer, GL_FILL);
}

void Firebeams::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale (glm::vec3(4, 0.9, 1));    // glScalef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Firebeams::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Firebeams::tick(){
}