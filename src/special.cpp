#include "special.h"
#include "main.h"
SpeedUp::SpeedUp(float x, float y,float bottom) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90.0f;
    speed = 0.01;
    this->yspeed = 0.1;
    this->miny = bottom+2;
    this->xspeed = -0.03;
    int n = 5;
    int inc = 1;
    float r = 0.6;
	GLfloat vertex_buffer_data[9*n];
	for (int i = 0; i < 9*n; i+=9)
	{
		float angle = 2*M_PI*inc/n;
		// if(inc==n) angle = 0;
		vertex_buffer_data[i]=r*cos(angle);
		vertex_buffer_data[i+1]=r*sin(angle);
		vertex_buffer_data[i+2]=0;
		vertex_buffer_data[i+3]=0;
		vertex_buffer_data[i+4]=0;
		vertex_buffer_data[i+5]=0;
		vertex_buffer_data[i+6]=r*cos(2*M_PI*+(inc+1)/n);
		vertex_buffer_data[i+7]=r*sin(2*M_PI*+(inc+1)/n);
		vertex_buffer_data[i+8]=0;
		inc++;
	}
    // const GLfloat color_buffer[]={
    // };
    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, COLOR_POW, GL_FILL);
}

void SpeedUp::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
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
void SpeedUp::tick(){
    if(this->yspeed>0) this->yspeed += 0.001f;
    else this->yspeed -= 0.001f;
    
    
    this->position.x += this->xspeed;
    if(this->position.y > 0-this->miny){
        this->yspeed = -0.03;
    }    
    else if(this->position.y < this->miny+2) this ->yspeed = 0.03;
    this->position.y += this->yspeed;
    
};

CoinsUp::CoinsUp(float x, float y,float bottom) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90.0f;
    speed = 0.01;
    this->yspeed = 0.1;
    this->miny = bottom+2;
    this->xspeed = -0.03;
    int n = 5;
    int inc = 1;
    float r = 0.6;
	GLfloat vertex_buffer_data[9*n];
	for (int i = 0; i < 9*n; i+=9)
	{
		float angle = 2*M_PI*inc/n;
		// if(inc==n) angle = 0;
		vertex_buffer_data[i]=r*cos(angle);
		vertex_buffer_data[i+1]=r*sin(angle);
		vertex_buffer_data[i+2]=0;
		vertex_buffer_data[i+3]=0;
		vertex_buffer_data[i+4]=0;
		vertex_buffer_data[i+5]=0;
		vertex_buffer_data[i+6]=r*cos(2*M_PI*+(inc+1)/n);
		vertex_buffer_data[i+7]=r*sin(2*M_PI*+(inc+1)/n);
		vertex_buffer_data[i+8]=0;
		inc++;
	}
    // const GLfloat color_buffer[]={
    // };
    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void CoinsUp::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void CoinsUp::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
bool CoinsUp::detect_collision(bounding_box_t a, bounding_box_t b) {
    bool x = a.x + a.width >= b.x && b.x + b.width >= a.x?true:false;
    bool y = a.y + a.height >= b.y && b.y + b.height >= a.y?true:false;
    return (x && y);
}
void CoinsUp::tick(){
    this->position.x += this->xspeed;
    this->position.y = 4*sin(this->position.x);
};

Sword::Sword(float x, float y,float bottom) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0.0f;
    speed = 0.01;
    this->yspeed = 0.1;
    this->miny = bottom+2;
    this->xspeed = -0.03;
    const GLfloat vertex_buffer_data[]={
        0.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f,
        0.35f, 2.0f, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.35f, 2.0f, 0.0f,
        0.35f, 0.0f, 0.0f, 

        0.17f, 2.5f, 0.0f,
        0.0f, 2.0f, 0.0f,
        0.35f, 2.0f, 0.0f, //upper blade

        -0.75f, 0.0f, 0.0f,
        -0.75f, -0.15f, 0.0f,
        1.1f, -0.15f, 0.0f,

        -0.75f, 0.0f, 0.0f,
        1.1f, 0.0f, 0.0f,
        1.1f, -0.15f, 0.0f,

        0.0f, -0.15f, 0.0f,
        0.35f, -0.15f, 0.0f,
        0.35f, -0.8f, 0.0f,

        0.0f, -0.15f, 0.0f,
        0.35f, -0.8f, 0.0f,
        0.0f, -0.8f, 0.0f,  //grip
    };
    const GLfloat color_data[]={

        192.0f/256.0f,192.0f/256.0f,192.0f/256.0f,         
        192.0f/256.0f,192.0f/256.0f,192.0f/256.0f, 
        192.0f/256.0f,192.0f/256.0f,192.0f/256.0f, 
  
        192.0f/256.0f,192.0f/256.0f,192.0f/256.0f, 
        192.0f/256.0f,192.0f/256.0f,192.0f/256.0f, 
        192.0f/256.0f,192.0f/256.0f,192.0f/256.0f, 
  
        192.0f/256.0f,192.0f/256.0f,192.0f/256.0f, 
        192.0f/256.0f,192.0f/256.0f,192.0f/256.0f, 
        192.0f/256.0f,192.0f/256.0f,192.0f/256.0f, 

        32.0f/256.0f,32.0f/256.0f,32.0f/256.0f,
        32.0f/256.0f,32.0f/256.0f,32.0f/256.0f,
        32.0f/256.0f,32.0f/256.0f,32.0f/256.0f,
  
        32.0f/256.0f,32.0f/256.0f,32.0f/256.0f,
        32.0f/256.0f,32.0f/256.0f,32.0f/256.0f,
        32.0f/256.0f,32.0f/256.0f,32.0f/256.0f,
  
        32.0f/256.0f,32.0f/256.0f,32.0f/256.0f,
        32.0f/256.0f,32.0f/256.0f,32.0f/256.0f,
        32.0f/256.0f,32.0f/256.0f,32.0f/256.0f,
  
        32.0f/256.0f,32.0f/256.0f,32.0f/256.0f,
        32.0f/256.0f,32.0f/256.0f,32.0f/256.0f,
        32.0f/256.0f,32.0f/256.0f,32.0f/256.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 7*3, vertex_buffer_data, color_data, GL_FILL);
}

void Sword::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
void Sword::tick(){
    this->position.x += this->xspeed;
    this->position.y = 4*sin(this->position.x) - 2*cos(this->position.x);
};


