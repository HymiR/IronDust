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

#include <irondust/gl/glfwIncludes.hpp>
#include <irondust/gl/GLSLShader.hpp>
#include <irondust/gl/GLSLProgram.hpp>
#include <irondust/gl/gl_error.hpp>

#include <irondust/util/log.hpp>
#include <irondust/util/math.hpp>

// sgnode stuff
#include <irondust/sg/sgscene.hpp>
#include <irondust/sg/sgcontext.hpp>
#include <irondust/sg/sgshadernode.hpp>
#include <irondust/sg/sgmaterialnode.hpp>
#include <irondust/sg/sglightnode.hpp>
#include <irondust/sg/sgtransformnode.hpp>
#include <irondust/sg/sgtexturenode.hpp>
#include <irondust/sg/sgnode.hpp>
#include <irondust/sg/sgmodel.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <stdlib.h> // for getenv()


using namespace irondust::gl;
using namespace irondust::sg;
using namespace irondust::util;


static GLFWwindow* window;
static glm::ivec2 size(840, 480);

// Initial position vectors
static glm::vec3 position = glm::vec3( -3, 2.0, 8.0 );
static glm::vec3 direction = glm::vec3(.0f, 0.5f, .0f);
static glm::vec3 right = glm::vec3(0.0f, 0.0f, 0.0f);
static glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
// Initial horizontal angle : toward -Z
static float horizontalAngle = glm::radians(135.f);
// Initial vertical angle : none
static float verticalAngle = glm::radians(-15.f);
// Initial z-Axis angle
static float depthAngle = 0.0f;
// Initial Field of View in degrees (typically between 90° and 30°)
static float FoV = 45.0f;

static float speed = 3.0f; // 3 units / second
static float mouseSpeed = 0.0005f;
static double xpos = 0.0;
static double ypos = 0.0;
static float deltaTime = 0.0f;

static std::string resources("./");

/// scene graph
static SGScene* scene = nullptr;


int execute(int, char**);
void initialise();
void load();
void loop();
void reshape();
void unload();
void deltatime();

void look();
void move();


// callbacks
static void close_callback(GLFWwindow *);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void error_callback(int error, const char* description);



int main(int argc, char** argv)
{
    LOG_INFO << "==[ Welcome to IronDust ]==" << std::endl;
    if(argc > 1) {
        resources = std::string(argv[1]);
    } else {
        const char* path = getenv("PWD");
        if(path) resources = std::string(path);
    }

    if(resources.back() != '/') resources += '/';

    LOG_INFO << "workdir =" << resources << std::endl;
    return execute(argc, argv);
}


int execute(int argc, char** argv)
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    initialise();
    load();

    // exec main loop
    while (!glfwWindowShouldClose(window)) loop();

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
    window = glfwCreateWindow(size.x, size.y, "Iron Dust", nullptr, nullptr);
    if(window == nullptr) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    // init the extension library
    glewExperimental = GL_TRUE; // enable "modern" opengl stuff
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        LOG_ERROR << "GLEW Init failed: " << glewGetErrorString(err) << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    // set remaining callbacks
    glfwSetWindowCloseCallback(window, close_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPos(window, size.x/2, size.y/2);
#ifdef NDEBUG
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // no cursor!
#endif
    //glfwSwapInterval(1); // default is 0 -- on faster machines this could lead to tearing

    // Standard background color
    glClearColor(0.2f, 0.2f, 0.3f, 1.f);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Enable depth test (accept if it closer to the camera than the former one)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // enable alpha blend
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    LOG_INFO << "-----------------------------------------------------------------------" << std::endl;
    LOG_INFO << "OpenGL Version \t" << glGetString(GL_VERSION) << std::endl;
    LOG_INFO << "OpenGL Renderer\t " << glGetString(GL_RENDERER) << std::endl;
    //LOG_INFO << "OpenGL Extensions\t " << glGetString(GL_EXTENSIONS) << std::endl;
    LOG_INFO << "-----------------------------------------------------------------------" << std::endl;
}


void load()
{
    LOG_INFO << "Loading scenes..." << std::endl;
    std::string models(resources+"models");
    std::string textures(resources+"textures");
    std::string shaders(resources+"shaders");

    // construct scene graph
    GLSLShader* vsh1 = GLSLShader::create(GLSLShader::VERTEX, shaders + "/default.vsh");
    GLSLShader* fsh1 = GLSLShader::create(GLSLShader::FRAGMENT, shaders + "/default.fsh");
    GLSLShader* vsh2 = GLSLShader::create(GLSLShader::VERTEX, shaders + "/phong.vsh");
    GLSLShader* fsh2 = GLSLShader::create(GLSLShader::FRAGMENT, shaders + "/phong.fsh");

    // root node with phong shader
    scene = new SGScene(new SGShaderNode(new GLSLProgram({vsh2, fsh2})));
    ISGNode& root = scene->getRoot();

    // add light to root
    root.append(new SGTransformNode(glm::translate(glm::mat4(1.), {-0.5, 3., -4.})))
            .append(new SGLightNode())/*
            .append(new SGShaderNode(new GLSLProgram({vsh1, fsh1})))
            .append(SGModel::createCube(scene->getContext(), {.3, .3, .3}))*/;

    { // add floor to root
        auto& m = dynamic_cast<SGMaterialNode&>(root.append(new SGMaterialNode()));
        m.append(new SGTransformNode(
                      glm::translate(glm::mat4(1.), {0., -0.5, 0.}) *
                      glm::rotate(glm::mat4(1.), glm::radians(-90.f), {1., 0., 0.})))
                .append(new SGTextureNode(scene->getContext(), textures+"/lava2.jpg"))
                .append(SGModel::createQuad(scene->getContext(), {15.,15.}));
        m.diffuse = {.8f, .8f, .8f, 1.f};
        m.ambient = {.7f, .7f, .7f, 1.f};
        m.specular = {.01f, .01f, .01f, 1.f};
        m.shininess = 0.1f;
    }

    // add a sphere to root
    root.append(new SGMaterialNode())
            .append(SGModel::createSphere(scene->getContext(), 1));

    // add a cube to root
    root.append(new SGTransformNode(glm::translate(glm::mat4(1.), {-1.5, 0.5, 0.5})))
            .append(SGModel::createCube(scene->getContext(), {.5, .5, .5}));

    { // yet another cube
        auto* m = new SGMaterialNode();
        m->diffuse = {1.f, .2f, .2f, 1.f};
        m->ambient = {.8f, .1f, .2f, 1.f};
        m->specular = {.2f, .45f, .2f, 1.f};
        m->shininess = 5.0f;
        root.append(new SGTransformNode(glm::translate(glm::mat4(1.), {1.5, 1.0, 3})))
                .append(m)
                .append(SGModel::createCube(scene->getContext(), {.3, 3.0, .3}));
    }

    { // add a pyramid to root
        auto* m = new SGMaterialNode();
        m->diffuse = {.8f, .8f, .75f, 1.f};
        m->ambient = {.5f, .5f, .35f, 1.f};
        m->specular = {.1f, .1f, .1f, 1.f};
        m->shininess = 0.3f;
        root.append(new SGTransformNode(glm::translate(glm::mat4(1.), {3.5, 0.3, 1.5})))
                .append(new SGTextureNode(scene->getContext(), textures+"/wall1.jpg"))
                .append(m)
                .append(SGModel::createPyramid(scene->getContext(), 2.2f, 1.4f));
    }

    scene->init();
}


void loop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    deltatime();

    look();
    move();
    reshape();

    // render scenegraph
    scene->render();

    glfwSwapBuffers(window);
    glfwPollEvents();
}


void reshape()
{
    glm::i32 width, height;
    glfwGetFramebufferSize(window, &width, &height);
    SGContext& context = scene->getContext();

    static glm::f32 ratio = math::ratio(width, height);
    static glm::f32 near = .1f;
    static glm::f32 far = 100.f;
    context.projection_matrix = glm::perspective(glm::radians(FoV), ratio, near, far);

    // {cam position, cam look-at, cam-rotaiton}
    context.view_matrix = glm::lookAt(position, position+direction, up);
}


void deltatime()
{
    static double lastTick = glfwGetTime();
    double currentTick = glfwGetTime();
    deltaTime = float(currentTick - lastTick);
    lastTick = glfwGetTime();
}


void move()
{
    // Move forward
    if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS)
        position += direction * deltaTime * speed;
    // Move backward
    if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS)
        position -= direction * deltaTime * speed;
    // Strafe right
    if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS)
        position += right * deltaTime * speed;
    // Strafe left
    if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS)
        position -= right * deltaTime * speed;
    // Jump
    if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS)
        position += up * deltaTime * speed;
    // Duck
    if (glfwGetKey( window, GLFW_KEY_C ) == GLFW_PRESS)
        position -= up * deltaTime * speed;
}


void look()
{
    int width, height, hwith, hheight = 0;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize (window, &width, &height);
    hheight = height / 2;
    hwith = width / 2;
    glfwSetCursorPos(window, hwith, hheight);

    // Compute new orientation
    horizontalAngle += mouseSpeed * static_cast<float>(hwith - xpos);
    verticalAngle   += mouseSpeed * static_cast<float>(hheight - ypos);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    direction = glm::vec3(
        cosf(verticalAngle) * sinf(horizontalAngle),
        sinf(verticalAngle),
        cosf(verticalAngle) * cosf(horizontalAngle)
    );

    // Right vector
    right = glm::vec3(
        sinf(horizontalAngle - math::HPIl),
        tanf(depthAngle),
        cosf(horizontalAngle - math::HPIl)
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
    static bool wireframe = false;

    if(mods & GLFW_MOD_SHIFT) speed = 15.f;
    else speed = 3.f;

    switch (key) {
    case GLFW_KEY_E:
        if(action == GLFW_PRESS) {
            FoV += 5.0f;
            if(FoV >= 360.0f) FoV = 45.0f;
        }
        break;
    case GLFW_KEY_Q:
        if(action == GLFW_PRESS) {
            FoV -= 5.0f;
            if(FoV <= 0.0f) FoV = 45.0f;
        }
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
    default:
        LOG_DEBUG << "KEY Action: key=" << key
                  << ", action=" << action
                  << ", scancode=" << scancode
                  << ", mods=" << mods << std::endl;
    }
}


static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    static_cast<void>(window);
    //if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    LOG_DEBUG << "MOUSE Action: button=" << button
              << ", action=" << action
              << ", mods=" << mods << std::endl;
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    static_cast<void>(window);
    LOG_DEBUG << "MOUSE Scroll: xoff=" << xoffset
              << ", yoff=" << yoffset<< std::endl;
}


static void error_callback(int error, const char* description)
{
    LOG_ERROR << "PROBLEM: description: " << description << " (code: " << error << ")." << std::endl;
}
