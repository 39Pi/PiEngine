#include <iostream>
#include <piengine/managers/window.hpp>

WindowManager::WindowManager() {
}

bool WindowManager::createWindow(std::string title, int width, int height) {
    glewExperimental = true; // Needed for core profile
    if(!glfwInit()) {
        std::cerr << "failed to init GLFW!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if(_window == NULL){
        std::cerr << "failed to open GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(_window); // Initialize GLEW
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "failed to initialize GLEW" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

	return true;
}

glm::vec2 WindowManager::getWindowSize() {
    int width;
    int height;
    glfwGetWindowSize(_window, &width, &height);
    return glm::vec2{width, height};
}
