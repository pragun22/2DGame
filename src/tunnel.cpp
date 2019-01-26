#include "tunnel.h"
Tunnel::Tunnel(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0.0f;
    this->rot = 180.0f;
    speed = 0.01;
    int n = 50;
    int inc = 0;
    float r = 9.0f ;
    GLfloat vertex_buffer_data[9*n/2];
    GLfloat vertex_buffer_data1[9*n/2];
	for (int i = 0; i < 9*n/2; i+=9)
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
    inc = 0;
    for (int i = 0; i < 9*n/2; i+=9)
	{
		float angle = 2*M_PI*inc/n;
		// if(inc==n) angle = 0;
		vertex_buffer_data1[i]=(r-2)*cos(angle);
		vertex_buffer_data1[i+1]=(r-2)*sin(angle);
		vertex_buffer_data1[i+2]=0;
		vertex_buffer_data1[i+3]=0;
		vertex_buffer_data1[i+4]=0;
		vertex_buffer_data1[i+5]=0;
		vertex_buffer_data1[i+6]=(r-2)*cos(2*M_PI*+(inc+1)/n);
		vertex_buffer_data1[i+7]=(r-2)*sin(2*M_PI*+(inc+1)/n);
		vertex_buffer_data1[i+8]=0;
		inc++;
	}
    this->object = create3DObject(GL_TRIANGLES, 3*n/2, vertex_buffer_data, COLOR_REAL_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3*n/2, vertex_buffer_data1, COLOR_BACKGROUND, GL_FILL);
}

void Tunnel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);

}

void Tunnel::tick(Player* hooman){
    if(this->rot > 0.0f) this->rot -= 1.0f;
    
    hooman->position.x = this->position.x + 9.0f*cos((float) (this->rot * M_PI / 180.0f));
    hooman->position.y = this->position.y + 9.0f*sin((float) (this->rot * M_PI / 180.0f));
}