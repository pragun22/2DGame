#include "main.h"
#include "timer.h"
#include "ball.h"
#include "player.h"
#include "magnet.h"
#include "special.h"
#include "platform.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball coins[100];
set<int> del_coins;
Player player;
Platform platform;
SpeedUp pow_speed;
Magnet mag;
float score = 0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int pos = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
void renderBitmapString(float x, float y,const char *string){
    glColor3f(0.5,0,1);
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
    }
}
/* Edit this function according to your assignment */
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
    player.draw(VP);
    platform.draw(VP);
    mag.draw(VP);
    pow_speed.draw(VP);
    // for(int i = 0; i < 100; i++) {
    //     if(del_coins.find(i)==del_coins.end()) coins[i].draw(VP);
    // }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int zoom_in = glfwGetKey(window, GLFW_KEY_UP);
    int zoom_out = glfwGetKey(window, GLFW_KEY_DOWN);
    if (up) {
        player.jump();  
    }
    if(zoom_in) {
        screen_zoom+=0.1;
        if(screen_zoom>2) screen_zoom = 2;
    }
    if(zoom_out) {
        screen_zoom-=0.1;
        if(screen_zoom<0.5) screen_zoom = 0.5;
    }
    if(right) {
        player.move(1);
        platform.move();
        screen_center_x += 0.07f;
    }
    if(left){
        player.move(0); 
        screen_center_x -= 0.07f;

    } 
}
void tick_elements() {
    // screen_center_x += 0.07f;
    player.tick();
    mag.tick(&player);
    pow_speed.tick();
    // for(int i = 0; i<100;i++)
    // {
    //     bounding_box_t a,b;
    //     a.x = player.position.x;
    //     a.y = player.position.y-1;
    //     a.width = 1;
    //     a.height = 2.4;
    //     b.x = coins[i].position.x-0.2;
    //     b.y = coins[i].position.y-0.2;
    //     b.width = 0.4;
    //     b.height = 0.4;
    //     if(detect_collision(a,b))
    //     {
    //         // cout<<a.x<<"--"<<coins[i].position.x<<endl;
    //         del_coins.insert(i); 
    //     }
    // }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    float bottom = screen_center_y - 4 / screen_zoom;
    std::cout<<bottom<<std::endl;
    player = Player(-3, bottom + (float)2.0, COLOR_BLACK,bottom);
    platform = Platform(-30, bottom , 1);
    mag = Magnet(14,4);
    pow_speed = SpeedUp(5, 3, bottom);
    for(int i = 0;i<50;i++)
    {
        float x1 = 94.2 +(float)i/2.0;
        if(i<25)
        {
            coins[i] = Ball(x1, 2, COLOR_COIN,0.2);
            coins[99-i] = Ball(x1 , 2.5, COLOR_COIN,0.2);
        }
        else{
            coins[i] = Ball(x1,2.5,COLOR_COIN,0.2);
            coins[99-i] = Ball(x1 , 3, COLOR_COIN,0.2);
        }
    }
    // Create and compile our GLSL program from the shaders
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
// initText2D( "Holstein.DDS" );
    initGL (window, width, height);
    glutInit(&argc, argv);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            score += float(1*float(1/60));
            char buffer[256];
            sprintf(buffer,"SCORE :  %.2f",score);
            // std::cout<<score<<std::endl;
            // renderBitmapString(0,0,buffer);
            // printText2D(buffer,10,500,60);
            tick_elements();
            tick_input(window);
            reset_screen();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
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
    if(player.position.x < left + 1) player.position.x = left + 1;
    if(player.position.x > right - 1) player.position.x = right - 1;
    // if(player.yspeed==0){ 
    //     player.position.y = bottom+2;
    // }
    player.miny = bottom+2;
    platform.position.y = bottom;
    pow_speed.miny = bottom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
