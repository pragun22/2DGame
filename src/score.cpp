#include "score.h"
#include "main.h"

One::One(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    const GLfloat vertex_buffer_data[]={
        0, 0, 0,
        0, 0.5f, 0,
        0.25f, 0.5f, 0,

        0, 0, 0,
        0.25f, 0, 0,
        0.25f, 0.5f, 0, // lower left

        0, 1, 0,
        0.25f, 1.0f, 0,
        0, 0.5f, 0,

        0, 0.5f, 0,
        0.25f, 0.5f, 0,
        0.25f, 1.0f, 0, // upper left

        0.75f, 1.0f, 0,
        1.0f, 1.0f, 0,
        0.75f, 0.5f, 0,

        1.0f, 1.0f, 0,
        1.0f, 0.5f, 0,
        0.75f, 0.5f, 0, // upper right
        
        0.75f, 0, 0,
        1, 0.0f, 0,
        1.0f, 0.5f, 0,

        0.75f, 0, 0,
        0.75f, 0.5f, 0,
        1.0f, 0.5f, 0, // lower right

        0.25f, 0, 0,
        0.75f, 0 , 0,
        0.75f, 0.12f, 0,

        0.25f, 0, 0,
        0.75f, 0.12f , 0,
        0.25f, 0.12f, 0,  //lower middle

        0.25f, 0.5f, 0,
        0.75f, 0.5f , 0,
        0.75f, 0.62f, 0,

        0.25f, 0.5f, 0,
        0.75f, 0.62f , 0,
        0.25f, 0.62f, 0,  //middle middle

        0.25f, 1, 0,
        0.75f, 1 , 0,
        0.75f, 0.88f, 0,

        0.25f, 1, 0,
        0.75f, 0.88f , 0,
        0.25f, 0.88f, 0,  //lower middle
        
    };
    this->object = create3DObject(GL_TRIANGLES, 14*3, vertex_buffer_data, COLOR_REAL_BLACK, GL_FILL);
}

void One::draw(glm::mat4 VP) {
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
Two::Two(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    const GLfloat vertex_buffer_data[]={
        0, 0, 0,
        0, 0.5f, 0,
        0.25f, 0.5f, 0,

        0, 0, 0,
        0.25f, 0, 0,
        0.25f, 0.5f, 0, // lower left

        0.75f, 1.0f, 0,
        1.0f, 1.0f, 0,
        0.75f, 0.5f, 0,

        1.0f, 1.0f, 0,
        1.0f, 0.5f, 0,
        0.75f, 0.5f, 0, // upper right

        0.25f, 0, 0,
        0.75f, 0 , 0,
        0.75f, 0.12f, 0,

        0.25f, 0, 0,
        0.75f, 0.12f , 0,
        0.25f, 0.12f, 0,  //lower middle

        0.25f, 0.5f, 0,
        0.75f, 0.5f , 0,
        0.75f, 0.62f, 0,

        0.25f, 0.5f, 0,
        0.75f, 0.62f , 0,
        0.25f, 0.62f, 0,  //middle middle

        0.25f, 1, 0,
        0.75f, 1 , 0,
        0.75f, 0.88f, 0,

        0.25f, 1, 0,
        0.75f, 0.88f , 0,
        0.25f, 0.88f, 0,  //lower middle
        
    };
    this->object = create3DObject(GL_TRIANGLES, 14*3, vertex_buffer_data, COLOR_REAL_BLACK, GL_FILL);
}

void Two::draw(glm::mat4 VP) {
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
Three::Three(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    const GLfloat vertex_buffer_data[]={
        0.75f, 1.0f, 0,
        1.0f, 1.0f, 0,
        0.75f, 0.5f, 0,

        1.0f, 1.0f, 0,
        1.0f, 0.5f, 0,
        0.75f, 0.5f, 0, // upper right
        
        0.75f, 0, 0,
        1, 0.0f, 0,
        1.0f, 0.5f, 0,

        0.75f, 0, 0,
        0.75f, 0.5f, 0,
        1.0f, 0.5f, 0, // lower right

        0.25f, 0, 0,
        0.75f, 0 , 0,
        0.75f, 0.12f, 0,

        0.25f, 0, 0,
        0.75f, 0.12f , 0,
        0.25f, 0.12f, 0,  //lower middle

        0.25f, 0.5f, 0,
        0.75f, 0.5f , 0,
        0.75f, 0.62f, 0,

        0.25f, 0.5f, 0,
        0.75f, 0.62f , 0,
        0.25f, 0.62f, 0,  //middle middle

        0.25f, 1, 0,
        0.75f, 1 , 0,
        0.75f, 0.88f, 0,

        0.25f, 1, 0,
        0.75f, 0.88f , 0,
        0.25f, 0.88f, 0,  //lower middle
        
    };
    this->object = create3DObject(GL_TRIANGLES, 14*3, vertex_buffer_data, COLOR_REAL_BLACK, GL_FILL);
}

void Three::draw(glm::mat4 VP) {
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
Four::Four(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    const GLfloat vertex_buffer_data[]={
        0, 1, 0,
        0.25f, 1.0f, 0,
        0, 0.5f, 0,

        0, 0.5f, 0,
        0.25f, 0.5f, 0,
        0.25f, 1.0f, 0, // upper left

        0.75f, 1.0f, 0,
        1.0f, 1.0f, 0,
        0.75f, 0.5f, 0,

        1.0f, 1.0f, 0,
        1.0f, 0.5f, 0,
        0.75f, 0.5f, 0, // upper right
        
        0.75f, 0, 0,
        1, 0.0f, 0,
        1.0f, 0.5f, 0,

        0.75f, 0, 0,
        0.75f, 0.5f, 0,
        1.0f, 0.5f, 0, // lower right

        0.25f, 0.5f, 0,
        0.75f, 0.5f , 0,
        0.75f, 0.62f, 0,

        0.25f, 0.5f, 0,
        0.75f, 0.62f , 0,
        0.25f, 0.62f, 0,  //middle middle
        
    };
    this->object = create3DObject(GL_TRIANGLES, 14*3, vertex_buffer_data, COLOR_REAL_BLACK, GL_FILL);
}

void Four::draw(glm::mat4 VP) {
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
Five::Five(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    const GLfloat vertex_buffer_data[]={

        0, 1, 0,
        0.25f, 1.0f, 0,
        0, 0.5f, 0,

        0, 0.5f, 0,
        0.25f, 0.5f, 0,
        0.25f, 1.0f, 0, // upper left
        
        0.75f, 0, 0,
        1, 0.0f, 0,
        1.0f, 0.5f, 0,

        0.75f, 0, 0,
        0.75f, 0.5f, 0,
        1.0f, 0.5f, 0, // lower right

        0.25f, 0, 0,
        0.75f, 0 , 0,
        0.75f, 0.12f, 0,

        0.25f, 0, 0,
        0.75f, 0.12f , 0,
        0.25f, 0.12f, 0,  //lower middle

        0.25f, 0.5f, 0,
        0.75f, 0.5f , 0,
        0.75f, 0.62f, 0,

        0.25f, 0.5f, 0,
        0.75f, 0.62f , 0,
        0.25f, 0.62f, 0,  //middle middle

        0.25f, 1, 0,
        0.75f, 1 , 0,
        0.75f, 0.88f, 0,

        0.25f, 1, 0,
        0.75f, 0.88f , 0,
        0.25f, 0.88f, 0,  //lower middle
        
    };
    this->object = create3DObject(GL_TRIANGLES, 14*3, vertex_buffer_data, COLOR_REAL_BLACK, GL_FILL);
}

void Five::draw(glm::mat4 VP) {
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
Six::Six(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    const GLfloat vertex_buffer_data[]={
        0, 0, 0,
        0, 0.5f, 0,
        0.25f, 0.5f, 0,

        0, 0, 0,
        0.25f, 0, 0,
        0.25f, 0.5f, 0, // lower left

        0, 1, 0,
        0.25f, 1.0f, 0,
        0, 0.5f, 0,

        0, 0.5f, 0,
        0.25f, 0.5f, 0,
        0.25f, 1.0f, 0, // upper left
        
        0.75f, 0, 0,
        1, 0.0f, 0,
        1.0f, 0.5f, 0,

        0.75f, 0, 0,
        0.75f, 0.5f, 0,
        1.0f, 0.5f, 0, // lower right

        0.25f, 0, 0,
        0.75f, 0 , 0,
        0.75f, 0.12f, 0,

        0.25f, 0, 0,
        0.75f, 0.12f , 0,
        0.25f, 0.12f, 0,  //lower middle

        0.25f, 0.5f, 0,
        0.75f, 0.5f , 0,
        0.75f, 0.62f, 0,

        0.25f, 0.5f, 0,
        0.75f, 0.62f , 0,
        0.25f, 0.62f, 0,  //middle middle

        
    };
    this->object = create3DObject(GL_TRIANGLES, 14*3, vertex_buffer_data, COLOR_REAL_BLACK, GL_FILL);
}

void Six::draw(glm::mat4 VP) {
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
Seven::Seven(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    const GLfloat vertex_buffer_data[]={


        0.75f, 1.0f, 0,
        1.0f, 1.0f, 0,
        0.75f, 0.5f, 0,

        1.0f, 1.0f, 0,
        1.0f, 0.5f, 0,
        0.75f, 0.5f, 0, // upper right
        
        0.75f, 0, 0,
        1, 0.0f, 0,
        1.0f, 0.5f, 0,

        0.75f, 0, 0,
        0.75f, 0.5f, 0,
        1.0f, 0.5f, 0, // lower right

        0.25f, 1, 0,
        0.75f, 1 , 0,
        0.75f, 0.88f, 0,

        0.25f, 1, 0,
        0.75f, 0.88f , 0,
        0.25f, 0.88f, 0,  //lower middle
        
    };
    this->object = create3DObject(GL_TRIANGLES, 14*3, vertex_buffer_data, COLOR_REAL_BLACK, GL_FILL);
}

void Seven::draw(glm::mat4 VP) {
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
Eight::Eight(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    const GLfloat vertex_buffer_data[]={
        0, 0, 0,
        0, 0.5f, 0,
        0.25f, 0.5f, 0,

        0, 0, 0,
        0.25f, 0, 0,
        0.25f, 0.5f, 0, // lower left

        0, 1, 0,
        0.25f, 1.0f, 0,
        0, 0.5f, 0,

        0, 0.5f, 0,
        0.25f, 0.5f, 0,
        0.25f, 1.0f, 0, // upper left

        0.75f, 1.0f, 0,
        1.0f, 1.0f, 0,
        0.75f, 0.5f, 0,

        1.0f, 1.0f, 0,
        1.0f, 0.5f, 0,
        0.75f, 0.5f, 0, // upper right
        
        0.75f, 0, 0,
        1, 0.0f, 0,
        1.0f, 0.5f, 0,

        0.75f, 0, 0,
        0.75f, 0.5f, 0,
        1.0f, 0.5f, 0, // lower right

        0.25f, 0, 0,
        0.75f, 0 , 0,
        0.75f, 0.12f, 0,

        0.25f, 0, 0,
        0.75f, 0.12f , 0,
        0.25f, 0.12f, 0,  //lower middle

        0.25f, 0.5f, 0,
        0.75f, 0.5f , 0,
        0.75f, 0.62f, 0,

        0.25f, 0.5f, 0,
        0.75f, 0.62f , 0,
        0.25f, 0.62f, 0,  //middle middle

        0.25f, 1, 0,
        0.75f, 1 , 0,
        0.75f, 0.88f, 0,

        0.25f, 1, 0,
        0.75f, 0.88f , 0,
        0.25f, 0.88f, 0,  //lower middle
        
    };
    this->object = create3DObject(GL_TRIANGLES, 14*3, vertex_buffer_data, COLOR_REAL_BLACK, GL_FILL);
}

void Eight::draw(glm::mat4 VP) {
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
Nine::Nine(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    const GLfloat vertex_buffer_data[]={

        0, 1, 0,
        0.25f, 1.0f, 0,
        0, 0.5f, 0,

        0, 0.5f, 0,
        0.25f, 0.5f, 0,
        0.25f, 1.0f, 0, // upper left

        0.75f, 1.0f, 0,
        1.0f, 1.0f, 0,
        0.75f, 0.5f, 0,

        1.0f, 1.0f, 0,
        1.0f, 0.5f, 0,
        0.75f, 0.5f, 0, // upper right
        
        0.75f, 0, 0,
        1, 0.0f, 0,
        1.0f, 0.5f, 0,

        0.75f, 0, 0,
        0.75f, 0.5f, 0,
        1.0f, 0.5f, 0, // lower right

        0.25f, 0, 0,
        0.75f, 0 , 0,
        0.75f, 0.12f, 0,

        0.25f, 0, 0,
        0.75f, 0.12f , 0,
        0.25f, 0.12f, 0,  //lower middle

        0.25f, 0.5f, 0,
        0.75f, 0.5f , 0,
        0.75f, 0.62f, 0,

        0.25f, 0.5f, 0,
        0.75f, 0.62f , 0,
        0.25f, 0.62f, 0,  //middle middle

        0.25f, 1, 0,
        0.75f, 1 , 0,
        0.75f, 0.88f, 0,

        0.25f, 1, 0,
        0.75f, 0.88f , 0,
        0.25f, 0.88f, 0,  //lower middle
        
    };
    this->object = create3DObject(GL_TRIANGLES, 14*3, vertex_buffer_data, COLOR_REAL_BLACK, GL_FILL);
}

void Nine::draw(glm::mat4 VP) {
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