#include <iostream>
#include <vector>

#include <piengine/file_ops.hpp>
#include <piengine/shader.hpp>
#include <piengine/mesh.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// TODO: Engine() class
std::vector<Shader> shaders;
std::vector<Mesh> meshes;

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
    window = glfwCreateWindow( 1024, 768, "PiEngine", NULL, NULL);
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

    // Add shaders
    Shader defaultShader = Shader(
        std::filesystem::path("vertex.glsl"),
        std::filesystem::path("fragment.glsl")
        );


    // Add meshes
    meshes.push_back(Mesh());

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        defaultShader.enable();
        for(const Mesh& mesh : meshes) {
            mesh.draw();
        }

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    return 0;
}
