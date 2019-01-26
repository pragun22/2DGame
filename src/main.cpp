#include "main.h"
#include "timer.h"
#include "ball.h"
#include "player.h"
#include "magnet.h"
#include "balloon.h"
#include "special.h"
#include "dragon.h"
#include "enemies.h"
#include "platform.h"
#include "score.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

vector<Ball> coins;
set<int> del_coins;
Player player;
Dragon dragon;
Platform platform;
vector<One> one;
vector<Two> two;
vector<Three> three;
vector<Four> four;
vector<Five> five;
vector<Six> six;
vector<Seven> seven;
vector<Eight> eight;
vector<Nine> nine;
std::vector<SpeedUp> speeds;
std::vector<Firelines> firelines;
std::vector<Firebeams> firebeams;
std::vector<CoinsUp> pow_coins;
std::vector<Balloon> balloons;
vector<Boomerang> boomerang;
vector<Magnet> mag;
float score = 0;
float screen_zoom = 0.5f, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int pos = 0;
double acc = 0.0;
clock_t bond;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void score_tick(float x, int score){
    float pos = screen_center_x + 4 / screen_zoom - 5.0f;
    float top    = screen_center_y + 4 / screen_zoom - 1.0f;
    while(score>0){
        int temp = score % 10;
        if(temp==1){ if(one.size()>0) one.pop_back(); one.push_back(One(pos, top));}
        if(temp==2){ if(two.size()>0)two.pop_back();two.push_back(Two(pos, top));}
        if(temp==3){ if(three.size()>0)three.pop_back();three.push_back(Three(pos, top));}
        if(temp==4){ if(four.size()>0)four.pop_back();four.push_back(Four(pos, top));}
        if(temp==5){ if(five.size()>0)five.pop_back();five.push_back(Five(pos, top));}
        if(temp==6){ if(six.size()>0)six.pop_back();six.push_back(Six(pos, top));}
        if(temp==7){ if(seven.size()>0)seven.pop_back();seven.push_back(Seven(pos, top));}
        if(temp==8){ if(eight.size()>0)eight.pop_back();eight.push_back(Eight(pos, top));}
        if(temp==9){ if(nine.size()>0)nine.pop_back();nine.push_back(Nine(pos, top));}
        pos += 1.1f;
        score = score / 10;
    }
}
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 0, 0, 10);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    // ball1.draw(VP);
    dragon.draw(VP);
    player.draw(VP);
    platform.draw(VP);
    for(int i = 0; i < one.size();i++) one[i].draw(VP);
    for(int i = 0; i < two.size();i++) two[i].draw(VP);
    for(int i = 0; i < three.size();i++) three[i].draw(VP);
    for(int i = 0; i < four.size();i++) four[i].draw(VP);
    for(int i = 0; i < five.size();i++) five[i].draw(VP);
    for(int i = 0; i < six.size();i++) six[i].draw(VP);
    for(int i = 0; i < seven.size();i++) seven[i].draw(VP);
    for(int i = 0; i < eight.size();i++) eight[i].draw(VP);
    for(int i = 0; i < nine.size();i++) nine[i].draw(VP);
    for(int i = 0 ; i<firelines.size();i++) firelines[i].draw(VP);
    for(int i = 0 ; i<mag.size();i++) mag[i].draw(VP);
    for(int i = 0 ; i<boomerang.size();i++) boomerang[i].draw(VP);
    for(int i = 0 ; i<firebeams.size();i++) if(firebeams[i].flag) firebeams[i].draw(VP);
    for(int i = 0 ; i<balloons.size();i++) balloons[i].draw(VP);
    for(int i = 0; i < speeds.size() ; i++) speeds[i].draw(VP);
    for(int i = 0; i < pow_coins.size() ; i++) pow_coins[i].draw(VP);
    for(int i = 0; i < coins.size(); i++) coins[i].draw(VP);

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int zoom_in = glfwGetKey(window, GLFW_KEY_UP);
    int zoom_out = glfwGetKey(window, GLFW_KEY_DOWN);
    int ball = glfwGetKey(window, GLFW_KEY_B);
    if(ball){
        clock_t start = clock();
        double timer = ((double) (start - bond)) / CLOCKS_PER_SEC;
        if(timer > 0.2){
            balloons.push_back(Balloon(player.position.x+1, player.position.y+1,player.xspeed,player.yspeed));
            bond = clock();
        }
    }
    if (up) {
        player.jump();  
    }
    if(zoom_in) {   
        screen_zoom+=0.1f;
        if(screen_zoom>2.0f) screen_zoom = 2.0f;
    }
    if(zoom_out) {
        screen_zoom-=0.1f;
        if(screen_zoom<0.5f) screen_zoom = 0.5f;
    }
    if(right) {
        float factor = 1.0f;
        if(player.position.x >= screen_center_x + 1.0f ) screen_center_x += 0.24f,factor = 2.0f;
        else screen_center_x += 0.07f ;
        player.move(1,factor);
        platform.move();
    }
    if(left){
        float factor = 1.0f;
        if(player.position.x <= screen_center_x - 2.0f ) screen_center_x -= 0.24f,factor = 2.0f;
        else screen_center_x -= 0.07f ;
        player.move(0,factor);
        platform.move();
    } 
}
void tick_elements() {
    // screen_center_x += 0.07f;
    score_tick(player.position.x, 2574);
    player.tick();
    for(int i = 0 ; i < speeds.size(); i++) speeds[i].tick();
    for(int i = 0 ; i < pow_coins.size(); i++) pow_coins[i].tick();
    bounding_box_t a;
    a.x = player.position.x;
    a.y = player.position.y-1.0f;
    a.width = 1.0f;
    a.height = 2.4f;
    for(int i =0; i < firelines.size(); i++){
        bounding_box_t field;
        field.x = firelines[i].position.x-1.5f;
        field.y = firelines[i].position.y+0.3f;
        field.width = 5.0f;
        field.height = 5.0f;
        if(detect_collision(a,field)){
            cout<<field.y<<" aaj mai krke aaya "<<rand()<<endl;
            firelines[i].detect_collision(a);
        }
    } 
    for(int i = 0 ; i < mag.size() ; i++){
        mag[i].tick(&player);
    }
    for(int i = 0; i < balloons.size(); i++){
        balloons[i].tick();   
        bounding_box_t fire;
        fire.x = 0.2f*4 + firebeams[0].position.x;
        fire.y = firebeams[0].position.y - 0.4f*0.9;
        fire.width = 3.0f*4;
        fire.height = 0.8f*0.9;
        if(balloons[i].detect_collision(fire) && firebeams[0].flag){ 
            firebeams[0].flag = false;
            firebeams[0].reset();
            balloons.erase(balloons.begin()+i);
            break;
        }
        // for(int i = 0 ; i < firelines.size() ; i++){
        //     bounding_box_t b;
        //     b.x = balloons[i].position.x - 0.4f;
        //     b.y = balloons[i].position.y - 0.4f;
        //     b.height = 0.8f;
        //     b.width = 0.8f; 
        //     if(firelines[i].detect_collision(b)){
        //         firelines.erase(firelines.begin()+i);
        //          balloons.erase(balloons.begin()+i);                
        //         break;
        //     }
        // }
    }
    for(int i =0; i < boomerang.size(); i++){
        boomerang[i].tick();
        bounding_box_t boomer;
        boomer.x = -0.5f + boomerang[i].position.x;
        boomer.y = -0.5f + boomerang[i].position.y;
        boomer.width = 1.0f;
        boomer.height = 0.5f;
        if(detect_collision(boomer, a)){
            cout<<"laga laga kaata laga"<<endl;
        }
    } 
    for(int i = 0 ; i< speeds.size();i++){
        bounding_box_t pow;
        pow.x = speeds[i].position.x - 0.6f*cos(M_PI/5.0f);
        pow.y = speeds[i].position.y - 0.6f*sin(M_PI/5.0f);
        pow.height = (0.6f + 0.6f*cos(M_PI/5.0f));
        pow.width = (0.6f + 0.6f*cos(M_PI/5.0f));
        if(detect_collision(a,pow)){
            speeds.erase(speeds.begin()+i);
            cout<<"speed up"<<endl;
            break;
        }
    }
    for(int i = 0 ; i< pow_coins.size();i++){
        bounding_box_t pow;
        pow.x = pow_coins[i].position.x - 0.6f*cos(M_PI/5.0f);
        pow.y = pow_coins[i].position.y - 0.6f*sin(M_PI/5.0f);
        pow.height = (0.6f + 0.6f*cos(M_PI/5.0f));
        pow.width = (0.6f + 0.6f*cos(M_PI/5.0f));
        if(detect_collision(a,pow)){
            pow_coins.erase(pow_coins.begin()+i);
            score += 0.1f;
            break;
        }
    }
    for(int i = 0; i < firebeams.size(); i++){
        if(firebeams[i].flag) firebeams[i].tick(&player);
        else firebeams[i].reset();
        bounding_box_t fire;
        fire.x = 0.2f*3.5 + firebeams[i].position.x;
        fire.y = firebeams[i].position.y - 0.4f*0.7;
        fire.width = 3.0f*3.5;
        fire.height = 0.8f*0.7;
        if(detect_collision(a,fire)){
            
            if(firebeams[i].flag) std::cout<<"kat gaya "<<rand()<<std::endl;
        }
            
    }
    for(int i = 0; i<coins.size();i++){
        bounding_box_t b;
        b.x = coins[i].position.x-0.2f;
        b.y = coins[i].position.y-0.2f;
        b.width = 0.4;
        b.height = 0.4;
        if(detect_collision(a,b)){
            coins.erase(coins.begin()+i);
        }
    }
}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    float bottom = screen_center_y - 4.0f / screen_zoom;
    bond = clock();
    player = Player(-3.0f, bottom+2.0f, COLOR_BLACK,bottom);
    dragon = Dragon(4.0f,2.0f);
    platform = Platform(-30.0f, bottom , 1);
    speeds.push_back(SpeedUp(5.0f, 3.0f, bottom));
    pow_coins.push_back(CoinsUp(10.0f, 0.0f, bottom));
    for(int i = 0 ; i < 15 ; i++){
        float x = 15 + ((float)i/1.5f)*21.2f;
        firelines.push_back(Firelines(x,2));
    }
    firebeams.push_back(Firebeams(6, 6));
    for(int i = 0; i < 10 ; i++){
        float x = 20.0f + i*26.3f;
        boomerang.push_back(Boomerang(2.0f,2.0f, x, 0.0f));   
    }
    for(int i = 0 ; i < 10 ; i++){
        float x = 50.0f + i*43.0f;
         mag.push_back(Magnet(x,i%4 + 2));
    }
    for(int i = 0;i<50;i++){
        float x1 = 94.2 +(float)i/1.5f;
        if(i<=24 && i > 22){
            coins.push_back(Ball(x1, 2.0f, COLOR_COIN2,0.3f));
            coins.push_back(Ball(x1, 2.5f, COLOR_COIN2,0.3f));
        }
        else if(i<25){
            coins.push_back(Ball(x1, 2.0f, COLOR_COIN,0.2f));
            coins.push_back(Ball(x1, 2.5f, COLOR_COIN,0.2f));
        }
        else{
            coins.push_back(Ball(x1,2.5f,COLOR_COIN,0.2f));
            coins.push_back(Ball(x1,3.0f,COLOR_COIN,0.2f));
        }
    }
    for(int i = 0;i<50;i++){
        float x1 = 184.2 +(float)i/1.5f;
        if(i<=24 && i > 22){
            coins.push_back(Ball(x1, 0.0f, COLOR_COIN2,0.3f));
            coins.push_back(Ball(x1, 0.5f, COLOR_COIN2,0.3f));
        }
        else if(i<25){
            coins.push_back(Ball(x1, 0.0f, COLOR_COIN,0.2f));
            coins.push_back(Ball(x1, 0.5f, COLOR_COIN,0.2f));
        }
        else{
            coins.push_back(Ball(x1,0.5f,COLOR_COIN,0.2f));
            coins.push_back(Ball(x1,1.0f,COLOR_COIN,0.2f));
        }
    }
    // Create and compile our GLSL program from the shaders
    //fonts work
    //fonts work ends here
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}
float asc;

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    window = initGLFW(width, height);
    initGL (window, width, height);
    /* Draw in loop */
    clock_t start = clock();
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // std::cout<<"tick"<<std::endl;
            // 60 fps
            // OpenGL Draw commands
            clock_t end = clock();
            int timer = ((int) (end - start)) / CLOCKS_PER_SEC;
            int random1 = rand()%1232;
            int random2 = rand()%1232;
            // if(true){   
            if(abs(random1 - random2)==0){
                for(int i = 0 ; i < firebeams.size() ; i++){
                    
                    if(!firebeams[i].flag){
                        firebeams[i].flag = true;
                        firebeams[i].time = end;
                    }
                }
            }
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            score += float(1*float(1/60));
            tick_input(window);
            tick_elements();
            reset_screen();

        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
        // glfwWaitEventsTimeout(0.01);
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    bool x = a.x + a.width >= b.x && b.x + b.width >= a.x?true:false;
    bool y = a.y + a.height >= b.y && b.y + b.height >= a.y?true:false;
    return (x && y);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    if(player.position.x < screen_center_x - 2.0f) player.position.x = screen_center_x - 2.0f;
    if(player.position.x > screen_center_x + 1.0f ) player.position.x = screen_center_x + 1.0f;
    // if(player.yspeed==0){ 
    //     player.position.y = bottom+2;
    // }
    if(player.position.y > top-1.4f)
    { 
        player.position.y = top - 1.4f;
        player.yspeed = 0.0f;
    }
    player.miny = bottom+2.0f;
    platform.position.y = bottom;
    for(int i = 0  ; i < speeds.size() ; i++){
        speeds[i].miny = bottom;
    }
    for(int i = 0  ; i < pow_coins.size() ; i++){
        pow_coins[i].miny = bottom;
    }
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
