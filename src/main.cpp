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
#include "tunnel.h"
#include <unistd.h>
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
Tunnel tunnel;
vector<Zero> zero;
vector<One> one;
vector<Two> two;
vector<Three> three;
vector<Four> four;
vector<Five> five;
vector<Six> six;
vector<Seven> seven;
vector<Eight> eight;
vector<Nine> nine;
vector<Fire> fire;
vector<Sword> sword;
std::vector<SpeedUp> speeds;
std::vector<Firelines> firelines;
std::vector<Firebeams> firebeams;
std::vector<CoinsUp> pow_coins;
std::vector<Balloon> balloons;
vector<Boomerang> boomerang;
vector<Magnet> mag;
int score = 0;
float screen_zoom = 0.35f, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int pos = 0;
double acc = 0.0;
float run_x = 0.2f;
float run_y = 0.3f;
clock_t bond;
clock_t firet;
clock_t safe;
clock_t magn;
int lives = 5;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void score_tick(float x, int score){
    float pos = screen_center_x + 4 / screen_zoom-1.0f;
    float top    = screen_center_y + 4 / screen_zoom - 1.0f;
    if(score == 0 ){ if(zero.size()>0) zero.pop_back(); zero.push_back(Zero(pos, top));}
    while(score>0){
        int temp = score % 10;
        if(temp==0){ zero.push_back(Zero(pos, top));}
        if(temp==1){ one.push_back(One(pos, top));}
        if(temp==2){ two.push_back(Two(pos, top));}
        if(temp==3){ three.push_back(Three(pos, top));}
        if(temp==4){ four.push_back(Four(pos, top));}
        if(temp==5){ five.push_back(Five(pos, top));}
        if(temp==6){ six.push_back(Six(pos, top));}
        if(temp==7){ seven.push_back(Seven(pos, top));}
        if(temp==8){ eight.push_back(Eight(pos, top));}
        if(temp==9){ nine.push_back(Nine(pos, top));}
        pos -= 1.1f;
        score = score / 10;
    }
}
void live_tick(int live){
    float pos = screen_center_x - 4 / screen_zoom-1.0f;
    float top    = screen_center_y + 4 / screen_zoom - 1.0f;
    if(live == 0 ){ if(zero.size()>0) zero.pop_back(); zero.push_back(Zero(pos+2.0f, top));}
    while(live>0){
        int temp = live % 10;
        if(temp==0){ zero.push_back(Zero(pos+2.0f, top));}
        if(temp==1){ one.push_back(One(pos+2.0f, top));}
        if(temp==2){ two.push_back(Two(pos+2.0f, top));}
        if(temp==3){ three.push_back(Three(pos+2.0f, top));}
        if(temp==4){ four.push_back(Four(pos+2.0f, top));}
        if(temp==5){ five.push_back(Five(pos+2.0f, top));}
        if(temp==6){ six.push_back(Six(pos+2.0f, top));}
        if(temp==7){ seven.push_back(Seven(pos+2.0f, top));}
        if(temp==8){ eight.push_back(Eight(pos+2.0f, top));}
        if(temp==9){ nine.push_back(Nine(pos+2.0f, top));}
        pos -= 1.1f;
        live = live / 10;
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
    for(int i = 0; i < zero.size();i++) zero[i].draw(VP);
    for(int i = 0; i < one.size();i++) one[i].draw(VP);
    for(int i = 0; i < two.size();i++) two[i].draw(VP);
    for(int i = 0; i < three.size();i++) three[i].draw(VP);
    for(int i = 0; i < four.size();i++) four[i].draw(VP);
    for(int i = 0; i < five.size();i++) five[i].draw(VP);
    for(int i = 0; i < six.size();i++) six[i].draw(VP);
    for(int i = 0; i < seven.size();i++) seven[i].draw(VP);
    for(int i = 0; i < eight.size();i++) eight[i].draw(VP);
    for(int i = 0; i < nine.size();i++) nine[i].draw(VP);
    if(zero.size()>0) zero.clear(); 
    if(one.size()>0) one.clear(); 
    if(two.size()>0)two.clear();
    if(three.size()>0)three.clear();
    if(four.size()>0)four.clear();
    if(five.size()>0)five.clear();
    if(six.size()>0)six.clear();
    if(seven.size()>0)seven.clear();
    if(eight.size()>0)eight.clear();
    if(nine.size()>0)nine.clear();
    for(int i = 0 ; i<firelines.size();i++) firelines[i].draw(VP);
    for(int i = 0 ; i<fire.size();i++) fire[i].draw(VP);
    for(int i = 0 ; i<mag.size();i++) mag[i].draw(VP);
    for(int i = 0 ; i<boomerang.size();i++) boomerang[i].draw(VP);
    for(int i = 0 ; i<firebeams.size();i++) if(firebeams[i].flag) firebeams[i].draw(VP);
    for(int i = 0 ; i<balloons.size();i++) balloons[i].draw(VP);
    for(int i = 0; i < speeds.size() ; i++) speeds[i].draw(VP);
    for(int i = 0; i < pow_coins.size() ; i++) pow_coins[i].draw(VP);
    for(int i = 0; i < coins.size(); i++) coins[i].draw(VP);
    for(int i = 0; i < sword.size(); i++) sword[i].draw(VP);
    tunnel.draw(VP);
    player.draw(VP);
    platform.draw(VP);

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
        clock_t sta = clock();
        double timer = (double)(sta-firet)/CLOCKS_PER_SEC;
        if(timer>0.1){
            for(int i = 0 ; i < 3; i++)
            {
                fire.push_back(Fire(player.position.x - 0.14f - float(i)/4.0f, player.position.y-(float)i/4,1));
            }
            firet = clock();
        }
    }
    // if(zoom_in) {   
    //     screen_zoom+=0.1f;
    //     if(screen_zoom>1.7f) screen_zoom = 1.7f;
    // }
    // if(zoom_out) {
    //     screen_zoom-=0.1f;
    //     if(screen_zoom<0.35f) screen_zoom = 0.35f;
    // }
    if(right) {
        if(player.safe){
            if(tunnel.rot > 0.0f) tunnel.rot -= 1.0f;
            else{
                tunnel.rot = 180.f;
                player.safe = false;
                tunnel.position.x += 240.0f;
            }
        }
        else{
            float factor = 1.0f;
            if(player.position.x >= screen_center_x + 1.0f ) screen_center_x += 0.24f,factor = 2.0f;
            else screen_center_x += 0.07f ;
            player.move(1,factor);
            platform.move();
        }
    }
    if(left){
        if(player.safe){
            if(tunnel.rot < 180.0f) tunnel.rot += 1.0f;
            else{
                tunnel.rot = 180.f;
                player.safe = false;
                tunnel.position.x += 240.0f;

            }
        }
        else{
            float factor = 1.0f;
            if(player.position.x <= screen_center_x - 2.0f ) screen_center_x -= 0.24f,factor = 2.0f;
            else screen_center_x -= 0.07f ;
            player.move(0,factor);
            platform.move();
        }
    } 
}
void tick_elements() {
    platform.tick(&player);
    clock_t temp = clock();
    int magtime = (int)(temp - magn)/CLOCKS_PER_SEC;
    if(magtime>10){
        player.magnet = false;
    }
    score_tick(player.position.x, score);
    live_tick(lives);
    player.tick();
    tunnel.tick(&player);
    dragon.tick(&player);
    if(player.sword){
        clock_t temp = clock();
        int timer = (int)(temp - safe)/CLOCKS_PER_SEC;
        //cout<<timer<<endl;
        if(timer > 6) player.sword = false;
    }
    bounding_box_t a;
    a.x = player.position.x;
    a.y = player.position.y-1.0f;
    a.width = 1.0f;
    a.height = 2.4f;
    bounding_box_t tun;
    tun.y = tunnel.position.y;
    tun.x = tunnel.position.x - 9.0f;
    tun.height = 1.0f;
    tun.width = 2.0f;
    if(detect_collision(a,tun)){
        player.safe = true;
        safe = clock();
    } 
    if(dragon.position.x - player.position.x < 13.0f){
        clock_t sta = clock();
        double timer = (double)(sta-firet)/CLOCKS_PER_SEC;
        if(timer>0.2){
            for(int i = 0 ; i < 5; i++)
            {
                fire.push_back(Fire(dragon.position.x - 7.0f, dragon.position.y+3.0f -(float)i/4,0));
            }
            firet = clock();
        }
    }
    bounding_box_t draco;
    draco.x = dragon.position.x - 7.0f;
    draco.y = dragon.position.y - 1.25f;
    draco.width = 9.0f;
    draco.height = 5.0f;
    if(detect_collision(draco,a)){
    //   delete &dragon;
        score = 0;
        dragon.position.x += 220.0f;
        player.position.x -= 10.0f;
        usleep(45000);
    }
    for(int i = 0 ; i< speeds.size();i++){
        if(speeds[i].tick(player.position.x)){
            speeds.erase(speeds.begin()+i);
            break;
        }
        bounding_box_t pow;
        pow.x = speeds[i].position.x - 0.6f*cos(M_PI/5.0f);
        pow.y = speeds[i].position.y - 0.6f*sin(M_PI/5.0f);
        pow.height = (0.6f + 0.6f*cos(M_PI/5.0f));
        pow.width = (0.6f + 0.6f*cos(M_PI/5.0f));
        if(detect_collision(a,pow)){
            speeds.erase(speeds.begin()+i);
            player.magnet = true;
            magn = clock();
            lives+=1;
            break;
        }
    }
    for(int i = 0 ; i< pow_coins.size();i++){
        if(pow_coins[i].tick(player.position.x)){
            pow_coins.erase(pow_coins.begin()+i);
            break;
        }        bounding_box_t pow;
        pow.x = pow_coins[i].position.x - 0.6f*cos(M_PI/5.0f);
        pow.y = pow_coins[i].position.y - 0.6f*sin(M_PI/5.0f);
        pow.height = (0.6f + 0.6f*cos(M_PI/5.0f));
        pow.width = (0.6f + 0.6f*cos(M_PI/5.0f));
        if(detect_collision(a,pow)){
            pow_coins.erase(pow_coins.begin()+i);
            score += 40;
            break;
        }
    }
    for(int i = 0; i<coins.size();i++){
        bounding_box_t b;
        b.x = coins[i].position.x-0.2f;
        b.y = coins[i].position.y-0.2f;
        b.width = 0.4;
        b.height = 0.4;
        if(coins[i].tick(&player)){
            coins.erase(coins.begin()+i);
            break;
        }
        if(detect_collision(a,b)){
            if(coins[i].r == 0.2f) score+=1;
            else score +=5;
            coins.erase(coins.begin()+i);
            break;
        }
    }
    for(int i = 0 ; i < sword.size() ; i++){
        if(sword[i].tick(player.position.x)){
            sword.erase(sword.begin()+i);
            break;
        }
        bounding_box_t tall,wid;
        tall.x = sword[i].position.x;
        tall.y = sword[i].position.y-0.80f;
        tall.width = 0.35f;
        tall.height = 3.0f;
        wid.x = sword[i].position.x - 0.75f;
        wid.y = sword[i].position.y - 0.15f;
        wid.height = 0.15f;
        wid.width = 1.85f;
        if(detect_collision(a,tall) || detect_collision(a,wid)){
            //cout<<"ab  ye krke dikhao"<<endl;
            sword.erase(sword.begin()+i);
            player.sword = true;
            safe = clock();
        }
        
    }
    if(!player.safe){
        for(int i = 0; i < fire.size(); i++){
            bounding_box_t b;
            b.x = fire[i].position.x;
            b.y = fire[i].position.y;
            b.width = 0.4f;
            b.height = 0.25f;
            if(fire[i].type==0 && detect_collision(a,b)) exit(0);
           float  timer =  fire[i].tick(player.position.y - dragon.position.y);
           float limit;
           if(fire[i].type) limit = 0.4f;
           else limit = 1.5f;
           if(timer>limit){
               fire.erase(fire.begin() + i);
               break;
           }
        }
        for(int i =0; i < firelines.size(); i++){
            if(firelines[i].tick(&player)){
                firelines.erase(firelines.begin()+i);
                break;
            }
            bounding_box_t field;
            field.x = firelines[i].position.x-2.0f;
            field.y = firelines[i].position.y+0.6f;
            field.width = 8.0f;
            field.height = 5.0f;
            if(detect_collision(a,field)){
                //cout<<field.y<<" aaj mai krke aaya "<<rand()<<endl;
                if(player.sword){
                    firelines[i].position.x += run_x;
                    firelines[i].position.y += run_y;
                }
                if(firelines[i].detect_collision(a,0.5f)){
                    firelines.erase(firelines.begin()+i);
                    if(!player.sword){
                        lives--;
                    }
                }
            }
            for(int j = 0; j < balloons.size(); j++)
            {
                cout<<"iske andar to aaya"<<endl;
                bounding_box_t ba;
                ba.x = balloons[j].position.x - 0.4f;
                ba.y = balloons[j].position.y - 0.4f;
                ba.height = 0.4f;
                ba.width = 0.4f;
                if(detect_collision(field,ba) && firelines[i].detect_collision(ba,0)){
                    cout<<"detect ho gaya"<<endl;
                    firelines.erase(firelines.begin()+i);
                    balloons.erase(balloons.begin()+j);                
                    break;
                }

            }
            
        } 
        for(int i = 0 ; i < mag.size() ; i++){
            if(mag[i].tick(&player)){
                mag.erase(mag.begin()+i);break;
            } 
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
        }
        for(int i =0; i < boomerang.size(); i++){
            if(boomerang[i].tick(player.position.x)){
                boomerang.erase(boomerang.begin()+i);
                break;
            }
            bounding_box_t boomer;
            boomer.x = -0.5f + boomerang[i].position.x;
            boomer.y = -0.5f + boomerang[i].position.y;
            boomer.width = 1.0f;
            boomer.height = 0.5f;
            if(detect_collision(boomer, a)){
                if(!player.sword)lives--;
                boomerang.erase(boomerang.begin()+i);
                usleep(90000);
                player.position.x += 5.0f;
            }
            if(player.sword){
                    boomerang[i].position.x += 3*run_x;
                    boomerang[i].position.y -= 3*run_y;
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
                
                if(firebeams[i].flag){
                    lives--;
                    firebeams[i].flag = false;
                    usleep(90000);
                    player.position.x += 5.0f;
                }
                if(player.sword){
                    firebeams[i].flag = false;
                }
            }         
         }
    }
    //end of if conditton
}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    float bottom = screen_center_y - 4.0f / screen_zoom;
    bond = clock();
    firet = clock();
    player = Player(-3.0f, bottom+2.0f, COLOR_BLACK,bottom);
    platform = Platform(-30.0f, bottom , 1);
    dragon = Dragon(240.0f,2.0f);
    tunnel = Tunnel(140.0f,-1.0f);
    firebeams.push_back(Firebeams(6, 6));
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor ((COLOR_BACKGROUND.r) / 256.0, (COLOR_BACKGROUND.g)/ 256.0, (COLOR_BACKGROUND.b)/ 256.0, 0.0f); // R, G, B, A
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
    int incr = -1;
    initGL (window, width, height);
    /* Draw in loop */
    clock_t start = clock();
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // std:://cout<<"tick"<<std::endl;
            // 60 fps
            // OpenGL Draw commands
            if(lives==0) exit(0);
            if(int(player.position.x)%300<2){
                incr++;
                incr = incr%3;
                player.position.x += 2.0f;
                screen_center_x += 2.0f;
                if(player.position.x < 30.0f) incr = 0;
            }
            glClearColor ((COLOR_BACKGROUND1[incr].r) / 256.0, (COLOR_BACKGROUND1[incr].g)/ 256.0, (COLOR_BACKGROUND1[incr].b)/ 256.0, 0.0f); // R, G, B, A
            clock_t end = clock();
            int timer = ((int) (end - start)) / CLOCKS_PER_SEC;
            int random1 = rand()%1232;
            int random2 = rand()%1232;
            int rand1 = rand()%632;
            int rand2 = rand()%632;
            // if(true){   
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            score += float(1*float(1/60));
            tick_input(window);
            tick_elements();
            reset_screen();
            if(abs(random1 - random2)==0){
                for(int i = 0 ; i < firebeams.size() ; i++){
                    if(!firebeams[i].flag){
                        firebeams[i].flag = true;
                        firebeams[i].time = end;
                    }
                }
                float pos = player.position.x + 52;
                mag.push_back(Magnet(pos,rand()%9-3.0f));
            }
            if(abs(random1 - random2)<5 &&  coins.size()<20){
                for(int i = 0;i<30;i++){
                    float x1 = player.position.x+ 20.f +(float)i/1.5f;
                    if(i<=24 && i > 22){
                        coins.push_back(Ball(x1+rand()%7, rand()%11-7.0f, COLOR_COIN2,0.3f));
                        coins.push_back(Ball(x1+rand()%7, rand()%11-7.0f, COLOR_COIN2,0.3f));
                    }
                    else if(i<25){
                        coins.push_back(Ball(x1+rand()%8, rand()%9-7.0f, COLOR_COIN,0.2f));
                        coins.push_back(Ball(x1+rand()%6, rand()%10-7.0f, COLOR_COIN,0.2f));
                    }
                    else{
                        coins.push_back(Ball(x1+rand()%9,rand()%10-6.0f,COLOR_COIN,0.2f));
                        coins.push_back(Ball(x1+rand()%7,rand()%9-6.0f,COLOR_COIN,0.2f));
                    }
                }
            }
            if(rand1==rand2){
                float pos = player.position.x + 25.0f;
                boomerang.push_back(Boomerang(2.0f,2.0f, pos, 0.0f));
            }
            if(random1%998<4 && pow_coins.size()<3){
                float bottom = screen_center_y - 4 / screen_zoom;
                float pos = player.position.x;
                speeds.push_back(SpeedUp(pos + 56.0f, 3.0f, bottom));
                pow_coins.push_back(CoinsUp(pos+25.0f, 0.0f, bottom));
                sword.push_back(Sword(pos+40.0f,2,bottom));  
            }
            if(abs(random1 - random2) < 2){
                float pos = player.position.x + 35.0f;
                firelines.push_back(Firelines(pos,1.0f+rand()%4));
                firelines.push_back(Firelines(pos+8,-2.0f+rand()%5));
            }
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
    if(player.position.x < screen_center_x - 2.0f && !player.safe) player.position.x = screen_center_x - 2.0f;
    if(player.position.x > screen_center_x + 1.0f && !player.safe) player.position.x = screen_center_x + 1.0f;
    if(player.position.x < screen_center_x - 2.0f && player.safe) screen_center_x = player.position.x + 2.0f;
    if(player.position.x > screen_center_x + 1.0f && player.safe) screen_center_x = player.position.x - 1.0f;
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
