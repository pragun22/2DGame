#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color,float r) {
    this->position = glm::vec3(x, y, 0);
    int n = 400;
    int inc = 1;
	this->r = r;
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

void Ball::tick(Player* hooman){
	if(hooman->magnet){
		float t1 = abs(hooman->position.x - this->position.x);
		float t2 = abs(hooman->position.y - this->position.y);
		float dis = sqrt(t1*t1 + t2*t2); 
		float force = 0.460f/dis; 
		float temp1 = hooman->position.x*hooman->position.x + hooman->position.y*hooman->position.y;
		float temp2 = this->position.x*this->position.x + this->position.y*this->position.y;
		bool flag = false;
		bool flag2 = false;
		if(hooman->position.y < this->position.y) flag  = true;
		if(hooman->position.x < this->position.x) flag2  = true;
		if(dis<40.0f)
		{
			if(flag2) this->position.x -= force*(t1)/dis;
			else this->position.x += force*(t1)/dis;
			if(flag) this->position.y -= force*(t2)/dis; 
			else this->position.y += force*(t2)/dis; 
		}
	}
}