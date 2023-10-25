#include <iostream>
#include <functional>
#include <piengine/managers/camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace {
	constexpr bool debugCameraManager = true;
}

CameraManager::CameraManager()
: _projMatrix{std::function<glm::mat4()>(std::bind(&CameraManager::_calculateProjMatrix, this))},
  _viewMatrix{std::function<glm::mat4()>(std::bind(&CameraManager::_calculateViewMatrix, this))} {
}

glm::mat4 CameraManager::_calculateProjMatrix() {
	if(debugCameraManager) {
		std::cerr << "PiEngine: CameraManager recalculating Projection Matrix" << std::endl;
	}
    
    return glm::perspective(
        glm::radians(45.0f),
        (float)_windowWidth / (float)_windowHeight,
        0.1f,
        100.0f
        );
}

glm::mat4 CameraManager::_calculateViewMatrix() {
    if(debugCameraManager) {
		std::cerr << "PiEngine: CameraManager recalculating View Matrix" << std::endl;
	}
    
    return glm::lookAt(
        _cameraPos, // camera pos
        glm::vec3(0, 0, 0), // look pos
        glm::vec3(0, 1, 0) // head is up
        );
}
