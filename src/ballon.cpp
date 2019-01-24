#include "balloon.h"
Balloon::Balloon(float x, float y, float a,float b) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->xspeed = (float)a + 0.01f;
    this->yspeed = (float)b + 0.05f;
    this->xthrust = (float)a;
    this->ythrust = (float)b;
    speed = 0.01;
    int n = 400;
    int inc = 1;
    float r = 0.4f ;
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
    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, COLOR_BLUE, GL_FILL);
    if(this->xthrust < 0.14f) this->xspeed = 0.2f;
    if(this->ythrust < 0.04f) this->yspeed = 0.1f;
    if(this->xthrust < 0.00f) this->xspeed = this->xthrust - 0.04f;
    if(this->ythrust < 0.00f) this->yspeed = this->ythrust + 0.18f;


}

void Balloon::draw(glm::mat4 VP) {
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

void Balloon::tick(){
    // std::cout<<this->xthrust<<std::endl;
    this->position.x += this->xspeed;
    this->position.y += this->yspeed;
    // if(this->yspeed!=0.0f){
        this->yspeed += -1*0.006f;
    // }
}
bool Balloon::detect_collision(bounding_box_t a){
    float r = 0.4f;
    bounding_box_t b;
    b.x = this->position.x - r;
    b.y = this->position.y - r;
    b.height = 2*r;
    b.width = 2*r; 
    bool x = a.x + a.width >= b.x && b.x + b.width >= a.x?true:false;
    bool y = a.y + a.height >= b.y && b.y + b.height >= a.y?true:false;
    return (x && y);
}