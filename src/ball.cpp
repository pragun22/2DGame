#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->friction = 0.95;
    this->gravity = 0.01;
    speed = 0.01;
    this->yspeed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // static const GLfloat vertex_buffer_data[] = {
    //      0.0f, 0.0f, 0.0f, // triangle 1 : begin
    //     -1.0f,-1.0f, 1.0f,
    //     -1.0f, 1.0f, 1.0f, // triangle 1 : end
    //     1.0f, 1.0f,-1.0f, // triangle 2 : begin
    //     -1.0f,-1.0f,-1.0f,
    //     -1.0f, 1.0f,-1.0f, // triangle 2 : end
    // };
    int n = 4;
    int inc = 1;
	GLfloat vertex_buffer_data[9*n];
	for (int i = 0; i < 9*n; i+=9)
	{
		float angle = 2*M_PI*inc/n;
		// if(inc==n) angle = 0;
		vertex_buffer_data[i]=1*cos(angle);
		vertex_buffer_data[i+1]=1*sin(angle);
		vertex_buffer_data[i+2]=2;
		vertex_buffer_data[i+3]=0;
		vertex_buffer_data[i+4]=0;
		vertex_buffer_data[i+5]=0;
		vertex_buffer_data[i+6]=cos(2*M_PI*+(inc+1)/n);
		vertex_buffer_data[i+7]=sin(2*M_PI*+(inc+1)/n);
		vertex_buffer_data[i+8]=2;
		inc++;
	}
    
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
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

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tickl(int col) {
    if(col) this->position.y -=speed;
    else 
    {
        this->position.x += speed;
    }
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
}
void Ball::tickr(int col) {
   if(col) this->position.y -=speed;
    else 
    {
        this->position.x -=speed;
    }
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

}
void Ball::jump(){
    this->yspeed = 0.215f;

}