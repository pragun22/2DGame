#include "main.h"
#include "timer.h"
#include "ball.h"
#include "player.h"
#include "magnet.h"
#include "special.h"
#include "enemies.h"
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
std::vector<SpeedUp> speeds;
std::vector<Firelines> firelines;
std::vector<Firebeams> firebeams;
std::vector<CoinsUp> pow_coins;
Magnet mag;
float score = 0;
float screen_zoom = 0.5f, screen_center_x = 0, screen_center_y = 0;
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
    for(int i = 0 ; i<firelines.size();i++) firelines[i].draw(VP);
    for(int i = 0 ; i<firebeams.size();i++) firebeams[i].draw(VP);
    for(int i = 0; i < speeds.size() ; i++){
        speeds[i].draw(VP);
    }
    for(int i = 0; i < pow_coins.size() ; i++){
        pow_coins[i].draw(VP);
    }
    for(int i = 0; i < 100; i++) {
        if(del_coins.find(i)==del_coins.end()) coins[i].draw(VP);
    }
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
        screen_zoom+=0.1f;
        if(screen_zoom>2.0f) screen_zoom = 2.0f;
    }
    if(zoom_out) {
        screen_zoom-=0.1f;
        if(screen_zoom<0.5f) screen_zoom = 0.5f;
    }
    if(right) {
        float factor = 1.0f;
        float right  = screen_center_x + 4.0f / screen_zoom;
        if(player.position.x >= screen_center_x + 1 ) screen_center_x += 0.24f,factor = 2.0f;
        else screen_center_x += 0.07f;
        player.move(1,factor);
        platform.move();
    }
    if(left){
        player.move(0,1.0f); 
        screen_center_x -= 0.07f;

    } 
}
void tick_elements() {
    // screen_center_x += 0.07f;
    player.tick();
    mag.tick(&player);
    for(int i = 0 ; i < speeds.size(); i++) speeds[i].tick();
    for(int i = 0 ; i < pow_coins.size(); i++) pow_coins[i].tick();
    bounding_box_t a;
    a.x = player.position.x;
    a.y = player.position.y-1.0f;
    a.width = 1.0f;
    a.height = 2.4f;
    for(int i = 0; i<100;i++)
    {
        bounding_box_t b;
        b.x = coins[i].position.x-0.2f;
        b.y = coins[i].position.y-0.2f;
        b.width = 0.4;
        b.height = 0.4;
        if(detect_collision(a,b))
        {
            // cout<<a.x<<"--"<<coins[i].position.x<<endl;
            del_coins.insert(i); 
        }
    }
    for(int i = 0 ; i< speeds.size();i++){
        bounding_box_t pow;
        pow.x = speeds[i].position.x - 0.6f*cos(M_PI/5.0f);
        pow.y = speeds[i].position.y - 0.6f*sin(M_PI/5.0f);
        pow.height = (0.6f + 0.6f*cos(M_PI/5.0f));
        pow.width = (0.6f + 0.6f*cos(M_PI/5.0f));
        if(detect_collision(a,pow)){
            SpeedUp* S = &speeds[i];
            speeds.erase(speeds.begin()+i);
            delete S;
        }
    }
    for(int i = 0 ; i< pow_coins.size();i++){
        bounding_box_t pow;
        pow.x = pow_coins[i].position.x - 0.6f*cos(M_PI/5.0f);
        pow.y = pow_coins[i].position.y - 0.6f*sin(M_PI/5.0f);
        pow.height = (0.6f + 0.6f*cos(M_PI/5.0f));
        pow.width = (0.6f + 0.6f*cos(M_PI/5.0f));
        if(detect_collision(a,pow)){
            CoinsUp* S = &pow_coins[i];
            pow_coins.erase(pow_coins.begin()+i);
            delete S;
        }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    float bottom = screen_center_y - 4.0f / screen_zoom;
    std::cout<<bottom<<std::endl;
    player = Player(-3.0f, -2.0f, COLOR_BLACK,bottom);
    platform = Platform(-30.0f, bottom , 1);
    mag = Magnet(14.0f,4.0f);
    SpeedUp pow_speed = SpeedUp(5.0f, 3.0f, bottom);
    speeds.push_back(pow_speed);
    pow_coins.push_back(CoinsUp(10.0f, 0.0f, bottom));
    firelines.push_back(Firelines(3,2));
    firebeams.push_back(Firebeams(2,1));
    for(int i = 0;i<50;i++)
    {
        float x1 = 94.2 +(float)i/2.0f;
        if(i<25)
        {
            coins[i] = Ball(x1, 2.0f, COLOR_COIN,0.2f);
            coins[99-i] = Ball(x1 , 2.5f, COLOR_COIN,0.2f);
        }
        else{
            coins[i] = Ball(x1,2.5f,COLOR_COIN,0.2f);
            coins[99-i] = Ball(x1 , 3.0f, COLOR_COIN,0.2f);
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
            tick_input(window);
            tick_elements();
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
    if(player.position.x < left + 1.0f) player.position.x = left + 1.0f;
    if(player.position.x > screen_center_x + 1.0f ) player.position.x = screen_center_x + 1.0f;
    // if(player.yspeed==0){ 
    //     player.position.y = bottom+2;
    // }
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
