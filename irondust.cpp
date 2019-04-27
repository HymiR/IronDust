/**
 ** This file is part of the irondust project.
 ** Copyright 2019 CyberViking Softwareschmiede GbR <leghissa@cyber-viking.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/


#define LOG_LEVEL LOG_LEVEL_DEBUG

#include <cg/oogl/glfwIncludes.hpp>
#include <cg/oogl/Model.hpp>
#include <cg/oogl/GLSLShader.hpp>
#include <cg/oogl/GLSLProgram.hpp>
#include <cg/oogl/gl_error.hpp>

#include <cg/util/log.hpp>
#include <cg/util/math.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace cg::oogl;


static const float PI = static_cast<float>(M_PI);

static GLFWwindow* window;
static int gwidth = 840;
static int gheight = 480;

// Initial position vectors
static glm::vec3 position = glm::vec3( 0.0, 0.0, 10.0 );
static glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
static glm::vec3 right = glm::vec3(0.0f, 0.0f, 0.0f);
static glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
// Initial horizontal angle : toward -Z
static float horizontalAngle = glm::radians(-180.f); //glm::radians(356.5f);
// Initial vertical angle : none
static float verticalAngle = glm::radians(0.f); //glm::radians(222.5f);
// Initial z-Axis angle
static float depthAngle = 0.0f;
// Initial Field of View in degrees (typically between 90° and 30°)
static float FoV = 45.0f;
static bool ortho = false;

static float speed = 3.0f; // 3 units / second
static float mouseSpeed = 0.0005f;
static double xpos = 0.0;
static double ypos = 0.0;
static float deltaTime = 0.0f;


static std::unique_ptr<Model> model;
static std::unique_ptr<GLSLProgram> program;


int execute(int, char**);
void initialise();
void load();
void render();
void runPipeline();
void unload();
void Mortimer();

void look();
void move();


// callbacks
static void close_callback(GLFWwindow *);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void error_callback(int error, const char* description);


int main(int argc, char** argv)
{
    LOG_INFO << "==[ Welcome to IronDust ]==" << std::endl;

    return execute(argc, argv);
}


int execute(int argc, char** argv)
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    initialise();
    load();

    while (!glfwWindowShouldClose(window)) {
        render();
    }

    unload();
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}


void initialise()
{
    // early error callback
    glfwSetErrorCallback(error_callback);

    // Initialise GLFW
    if(!glfwInit()) {
        LOG_ERROR << "GLFW Init failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    // for older gpus, e.g. older intel
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( gwidth, gheight, "Iron Dust", nullptr, nullptr);
    if(window == nullptr) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    // init the extension library
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        LOG_ERROR << "GLEW Init failed: " << glewGetErrorString(err) << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    // set remaining callbacks
    glfwSetWindowCloseCallback(window, close_callback);
    glfwSetKeyCallback(window, key_callback); // instead of keyboard()

    /*
    printf("OpenGL Version %s initialised\n", glGetString(GL_VERSION));
    GLfloat m, p;
    glGetFloatv(GL_MAX_MODELVIEW_STACK_DEPTH, &m);
    glGetFloatv(GL_MAX_PROJECTION_STACK_DEPTH, &p);
    printf("The maximal depth of the Modelview Matrix stack is: %2f\n", m);
    printf("The maximal depth of the Projection Matrix stack is: %2f\n", p);
    */

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPos(window, gwidth/2, gheight/2);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // no cursor!
    glfwSwapInterval(1); // default is 0 -- on faster machines this could lead to tearing

    // Standard background color
    glClearColor(0.0f, 0.156f, 0.392f, 0.f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}


void load()
{
    LOG_INFO << "Loading scenes..." << std::endl;

    std::string models("../IronDust/models");
    std::string src("../IronDust");

    GLSLShader* vsh = GLSLShader::create(GLSLShader::VERTEX, src + "/default.vsh");
    GLSLShader* fsh = GLSLShader::create(GLSLShader::FRAGMENT, src + "/default.fsh");
    program.reset(new GLSLProgram({vsh, fsh}));

    // load a simple model:
    model.reset(loadModel(models + "/porsche/porsche.obj",
                          Model::LOAD_SET_SMOOTHING_GROUP |
                          Model::LOAD_NORMALIZE_TWO));
}


void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_BACK);
    glLoadIdentity();

    // activate ShaderProgram: use it:
    program->bind();

    // calculate movement transformations
    runPipeline();

    // draw simple model...
    model->render(Model::RENDER_NO_TEXTURES); // porsche has no texture...

    glfwSwapBuffers(window);
    glfwPollEvents();
    Mortimer();
}


void runPipeline()
{
    look();
    move();

    glm::mat4 p, v, m, mvp;
    int width, height;
    float ratio;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / height;

    if(ortho) {
        p = glm::ortho(-10.f,10.f,-10.f,10.f,0.f,100.f);
    } else {
        p = glm::perspective(glm::radians(FoV), ratio, .1f, 100.f);
    }

    // {cam position, cam look-at, cam-rotaiton}
    v = glm::lookAt(position, position+direction, up);
    m = glm::mat4(1.0f); // identity: model will be at the origin
    mvp = p * v * m; // model-view-projection: read multiplication in reverse-order

    // finally give that to shader uniform:
    (*program)["MVP"] = mvp;
}


void Mortimer()
{
    static double lastTick = glfwGetTime();
    double currentTick = glfwGetTime();
    float tick = float(currentTick - lastTick);
    deltaTime = tick;
    lastTick = glfwGetTime();

    if(tick > 33) {
        // put animation timer variable here
    }
}


void move()
{
    // Move forward
    if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
        position += direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
        position -= direction * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
        position -= right * deltaTime * speed;
    }
    // Jump
    if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS){
        position += up * deltaTime * speed;
    }
    // Duck
    if (glfwGetKey( window, GLFW_KEY_C ) == GLFW_PRESS){
        position -= up * deltaTime * speed;
    }
}


void look()
{
    int width, height = 0;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize (window, &width, &height);
    glfwSetCursorPos(window, width/2, height/2);

    // Compute new orientation
    horizontalAngle += mouseSpeed * static_cast<float>(width/2 - xpos);
    verticalAngle   += mouseSpeed * static_cast<float>(height/2 - ypos);
//    LOG_DEBUG << std::endl
//              << "\tHAngle: " << static_cast<int>(glm::degrees(horizontalAngle)) % 360 << std::endl
//              << "\tVAngle: " << static_cast<int>(glm::degrees(verticalAngle)) %360 << std::endl;

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    direction = glm::vec3(
        cosf(verticalAngle) * sinf(horizontalAngle),
        sinf(verticalAngle),
        cosf(verticalAngle) * cosf(horizontalAngle)
    );

    // Right vector
    right = glm::vec3(
        sinf(horizontalAngle - PI/2.0f),
        tanf(depthAngle),
        cosf(horizontalAngle - PI/2.0f)
    );

    // Up vector
    up = glm::cross( right, direction );
}



void unload()
{
    LOG_INFO << "Unloading scenes..." << std::endl;
}


static void close_callback(GLFWwindow* window)
{
    static_cast<void>(window);
    LOG_DEBUG << "IronDust is terminating due to caallback..." << std::endl;
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    static_cast<void>(scancode);
    static_cast<void>(mods);

    static bool wireframe = false;

    LOG_DEBUG << "KEY Action: key=" << key
              << ", action=" << action
              << ", scancode=" << scancode
              << ", mods=" << mods << std::endl;

    if(mods == 1) speed = 15.f;
    else speed = 3.f;

    switch (key) {
    case GLFW_KEY_E:
        FoV += 5.0f;
        if(FoV >= 360.0f) FoV = 45.0f;
        break;
    case GLFW_KEY_Q:
        FoV -= 5.0f;
        if(FoV <= 0.0f) FoV = 45.0f;
        break;
    case GLFW_KEY_ESCAPE:
        if(action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
        break;
        // GLFW_KEY_LEFT_SHIFT
    case GLFW_KEY_M:
        if(action == GLFW_PRESS) {
            wireframe = !wireframe;
            if(wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        break;
    case GLFW_KEY_P:
        if(action == GLFW_PRESS) ortho = !ortho;
        break;
    }
}


static void error_callback(int error, const char* description)
{
    LOG_ERROR << "PROBLEM: description: " << description << " (code: " << error << ")." << std::endl;
}
