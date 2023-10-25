#include <iostream>
#include <memory>
#include <vector>

#include <piengine/file_ops.hpp>
#include <piengine/shader.hpp>
#include <piengine/mesh.hpp>
#include <piengine/managers/shader.hpp>
#include <piengine/managers/camera.hpp>
#include <piengine/managers/render.hpp>
#include <piengine/renderobjects/meshobject.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int width = 1024;
int height = 768;

int main(int argc, char** argv) {
    std::cout << "PiEngine!" << std::endl;

    if(argc > 1) {
        file_ops::setGlobalAssetPath(std::filesystem::path(argv[1]));
        std::cout << "PiEngine: set global asset path to " << file_ops::getGlobalAssetPath() << std::endl;
    }

    glewExperimental = true; // Needed for core profile
    if(!glfwInit()) {
        std::cerr << "failed to init GLFW!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow( width, height, "PiEngine", NULL, NULL);
    if( window == NULL ){
        std::cerr << "failed to open GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "failed to initialize GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Setup camera
    CameraManager::the().setWindowSize(width, height);
    CameraManager::the().setPos(glm::vec3(4, 3, 3));

    // Load shaders
    ShaderManager::the().colorShader = std::make_shared<Shader>(
        std::filesystem::path("color/vertex.glsl"),
        std::filesystem::path("color/fragment.glsl")
        );


    // Add meshes
    RenderManager::the().addObject(std::make_shared<MeshObject>(std::make_shared<Mesh>(), ShaderManager::the().colorShader));

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderManager::the().draw();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    return 0;
}
