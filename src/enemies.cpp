#include "enemies.h"
#include "main.h"
Firelines::Firelines(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 63.0f;
    // this->rotation = 50.0f + float(rand()%20);
    speed = 0.01;
    int n = 400;
    int inc = 1;
    const GLfloat vertex_buffer_data[]={
        0, 0 ,0,
        0, 2.2f, 0,
        1, 2.2f, 0,

        0, 0, 0,
        1, 0, 0,
        1, 2.2f, 0, /* left dumble */

        1, 0.2f, 0,
        4, 0.2f, 0,
        1 ,2 ,0,

        4, 0.2f, 0,
        4, 2, 0,
        1, 2, 0, // middle body

        4, 0, 0,
        5, 0, 0,
        4, 2.2f ,0,

        4, 2.2f, 0,
        5, 2.2f, 0,
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
    glm::mat4 scale = glm::scale (glm::vec3(1.5,0.45,0));    // glScalef
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
bool Firelines::detect_collision(bounding_box_t a){
    float m = -1.0f * tan((float) (this->rotation * M_PI / 180.0f));
    float c = this->position.y + this->position.x*m;
    float normaliser = sqrt(1 + m*m);
    for(float i = a.y ; i < a.y+a.height - 0.4f ; i+=0.05f){
        float dist  = ((a.x+a.width)*m + i - c)/normaliser;
        if(abs(dist)<0.1){
            std::cout<<a.y<<" -right se kata- "<<i<<" "<<dist<<std::endl;
            exit(0);
        } 
    }
    for(float i = a.y ; i < a.y+a.height ; i+=0.05f){
        float dist  = (a.x*m + i - c)/normaliser;
        if(abs(dist)<0.1){
            std::cout<<a.y<<" -left se kata- "<<i<<" "<<dist<<std::endl;
            exit(0);
        } 
    }
    float c2 = 2.2f*normaliser - c;
    for(float i = a.y ; i < a.y+a.height - 0.4f; i+=0.05f){
        float dist  = ((a.x+a.width)*m + i - c2)/normaliser;
        if(abs(dist)<0.1){
            std::cout<<a.y<<" -right se kata- "<<i<<" "<<dist<<std::endl;
            exit(0);

        } 
    }
    for(float i = a.y ; i < a.y+a.height ; i+=0.05f){
        float dist  = (a.x*m + i - c2)/normaliser;
        if(abs(dist)<0.1){
            std::cout<<a.y<<" -left se kata- "<<i<<" "<<dist<<std::endl;
            exit(0);
        } 
    }
    
    return true;
}

Firebeams::Firebeams(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90.0f;
    this->flag = false;
    this->facto = 0.1f;
    this->time = clock();
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
    glm::mat4 scale = glm::scale (glm::vec3(3.5, 0.7, 1));    // glScalef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
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
void Firebeams::tick(Player* hooman){
    if(this->rotation>0.1f) this->rotation -= 1.2f;
    if(this->position.y > 7.0f) this->facto = 0.10f;
    if(this->position.y < -3.0f) this->facto = -0.10f;
    this->position.y -= this->facto;
    bounding_box_t side1,b;
    side1.x =this->position.x;
    side1.y =this->position.y - 0.7f;
    side1.height = 2*0.7f;
    side1.width = 3.5 * 0.2f;
    b.x = hooman->position.x;
    b.y = hooman->position.y-1.0f;
    b.width = 1;
    b.height = 2.4;
    float tempx = b.x, tempy = b.y;
    if(detect_collision(side1,b) && this->flag)
    {
        std::cout<<"lagda ishara "<<rand()<<std::endl;
        hooman->position.x = side1.x-1.0f;
        hooman->position.y = tempy+1.0f;
    }
    if(hooman->position.x - 6.0f>this->position.x) this->position.x = hooman->position.x - 6.0f;
    if(this->flag){
        clock_t end = clock();
        int timer = ((int) (end - this->time)) / CLOCKS_PER_SEC;
        if(timer>=10) this->flag = false;
    }
}
void Firebeams::reset(){
    this->rotation = 90.0f;
    this->position.y = 6;
}
Boomerang::Boomerang(float x, float y, float cen_x, float cen_y){
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0.0f;
    this->degree = 0.0f;
    this->x = cen_x;
    this->y = cen_y;
    const GLfloat vertex_buffer_data[]={
        0.3f, 0, 0,
        -0.5, 0, 0,
        -0.5, -0.5, 0,

        -0.3f, 0, 0,
        0.5, 0, 0,
        0.5, -0.5, 0
    };
    // const GLfloat color_buffer[]={
    // };
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    
}
void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale (glm::vec3(1, 1, 1));    // glScalef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
void Boomerang::tick(){
    this->rotation +=1.2f;
    this->degree += 0.01f;
    if(this->rotation > 360.0f) this->rotation = 0.0f;
    if(this->degree > 360.0f) this->degree = 0.0f;
    this->position.x = this->x + 15*cos(this->degree);
    this->position.y = this->y + 4*sin(this->degree);
}