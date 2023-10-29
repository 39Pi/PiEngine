#include <iostream>
#include <memory>
#include <vector>

#include <piengine/file_ops.hpp>
#include <piengine/shader.hpp>
#include <piengine/mesh.hpp>
#include <piengine/texture.hpp>
#include <piengine/iostream_out_ops.hpp>
#include <piengine/managers/shader.hpp>
#include <piengine/managers/camera.hpp>
#include <piengine/managers/render.hpp>
#include <piengine/managers/window.hpp>
#include <piengine/managers/input.hpp>
#include <piengine/renderobjects/meshobject.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

std::vector<GLfloat> g_vertex_buffer_data = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

std::vector<GLfloat> g_color_buffer_data = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

std::vector<GLfloat> g_uv_buffer_data = { 
    0.000059f, 0.000004f, // 1.0f- 
    0.000103f, 0.336048f, // 1.0f- 
    0.335973f, 0.335903f, // 1.0f- 
    1.000023f, 0.000013f, // 1.0f- 
    0.667979f, 0.335851f, // 1.0f- 
    0.999958f, 0.336064f, // 1.0f- 
    0.667979f, 0.335851f, // 1.0f- 
    0.336024f, 0.671877f, // 1.0f- 
    0.667969f, 0.671889f, // 1.0f- 
    1.000023f, 0.000013f, // 1.0f- 
    0.668104f, 0.000013f, // 1.0f- 
    0.667979f, 0.335851f, // 1.0f- 
    0.000059f, 0.000004f, // 1.0f- 
    0.335973f, 0.335903f, // 1.0f- 
    0.336098f, 0.000071f, // 1.0f- 
    0.667979f, 0.335851f, // 1.0f- 
    0.335973f, 0.335903f, // 1.0f- 
    0.336024f, 0.671877f, // 1.0f- 
    1.000004f, 0.671847f, // 1.0f- 
    0.999958f, 0.336064f, // 1.0f- 
    0.667979f, 0.335851f, // 1.0f- 
    0.668104f, 0.000013f, // 1.0f- 
    0.335973f, 0.335903f, // 1.0f- 
    0.667979f, 0.335851f, // 1.0f- 
    0.335973f, 0.335903f, // 1.0f- 
    0.668104f, 0.000013f, // 1.0f- 
    0.336098f, 0.000071f, // 1.0f- 
    0.000103f, 0.336048f, // 1.0f- 
    0.000004f, 0.671870f, // 1.0f- 
    0.336024f, 0.671877f, // 1.0f- 
    0.000103f, 0.336048f, // 1.0f- 
    0.336024f, 0.671877f, // 1.0f- 
    0.335973f, 0.335903f, // 1.0f- 
    0.667969f, 0.671889f, // 1.0f- 
    1.000004f, 0.671847f, // 1.0f- 
    0.667979f, 0.335851f  // 1.0f-
};

int width = 1920;
int height = 1080;

constexpr float mouseSpeed = 80.0f;
constexpr float movSpeed = 10.0f;

int main(int argc, char** argv) {
    std::cout << "PiEngine!" << std::endl;

    if(argc > 1) {
        file_ops::setGlobalAssetPath(std::filesystem::path(argv[1]));
        std::cout << "PiEngine: set global asset path to " << file_ops::getGlobalAssetPath() << std::endl;
    }

    if(!WindowManager::the().createWindow("PiEngine", width, height)) {
        return -1;
    }

    InputManager::the().init();

    // Setup camera
    CameraManager::the().setWindowSize(width, height);
    CameraManager::the().setPos(glm::vec3(4.0f, 3.0f, 3.0f));
    CameraManager::the().setRot(glm::vec3(0.0f, -0.5f, 4.0f));

    // Load shaders
    ShaderManager::the().colorShader = std::make_shared<Shader>(
        std::filesystem::path("color/vertex.glsl"),
        std::filesystem::path("color/fragment.glsl")
        );

    ShaderManager::the().textureShader = std::make_shared<Shader>(
        std::filesystem::path("textured/vertex.glsl"),
        std::filesystem::path("textured/fragment.glsl")
        );

    // Load textures
    auto texture = std::make_shared<Texture>(std::filesystem::path("uvtemplate.DDS"));

    // Add meshes
    auto mesh = std::make_shared<Mesh>(Mesh::Type::Textured, g_vertex_buffer_data, g_uv_buffer_data, texture);
    auto script = std::make_shared<Script>(std::filesystem::path("scripts/rotate.lua"));
    
    auto object = std::make_shared<MeshObject>(mesh);
    object->setRot(glm::vec3{0, 0, 0});
    object->attachScript(script, object);

    RenderManager::the().addObject(object);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        InputManager::the().beginFrame();

        // std::cerr << "PiEngine: mouse pos = " << InputManager::the().normalisedMouseDeltaPos() << std::endl;

        double deltaTime = InputManager::the().deltaTime();

        glm::vec3 cameraRot = CameraManager::the().getRot();
        cameraRot.z += mouseSpeed * deltaTime * InputManager::the().normalisedMouseDeltaPos().x;
        cameraRot.y += mouseSpeed * deltaTime * InputManager::the().normalisedMouseDeltaPos().y;

        if(cameraRot != CameraManager::the().getRot()) {
            CameraManager::the().setRot(cameraRot);
        }

        glm::vec3 cameraPos = CameraManager::the().getPos();
        if(InputManager::the().keyPressed(GLFW_KEY_UP)) {
            cameraPos += CameraManager::the().getDirectionVector() * (float)deltaTime * movSpeed;
        }
        if(InputManager::the().keyPressed(GLFW_KEY_DOWN)) {
            cameraPos -= CameraManager::the().getDirectionVector() * (float)deltaTime * movSpeed;
        }

        if(InputManager::the().keyPressed(GLFW_KEY_RIGHT)) {
            cameraPos += CameraManager::the().getRightVector() * (float)deltaTime * movSpeed;
        }
        if(InputManager::the().keyPressed(GLFW_KEY_LEFT)) {
            cameraPos -= CameraManager::the().getRightVector() * (float)deltaTime * movSpeed;
        }

        if(cameraPos != CameraManager::the().getPos()) {
            CameraManager::the().setPos(cameraPos);
        }

        RenderManager::the().fireScripts();
        RenderManager::the().draw();

        // Swap buffers
        InputManager::the().endFrame();
        glfwSwapBuffers(WindowManager::the().getWindow());
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(WindowManager::the().getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(WindowManager::the().getWindow()) == 0 );

    return 0;
}
