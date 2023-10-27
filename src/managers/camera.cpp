#include <iostream>
#include <functional>

#include <piengine/managers/camera.hpp>
#include <piengine/iostream_out_ops.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace {
	constexpr bool debugCameraManager = false;
}

CameraManager::CameraManager()
: _projMatrix{std::function<glm::mat4()>(std::bind(&CameraManager::_calculateProjMatrix, this))},
  _viewMatrix{std::function<glm::mat4()>(std::bind(&CameraManager::_calculateViewMatrix, this))},
  _direction{std::function<glm::vec3()>(std::bind(&CameraManager::_calculateDirection, this))},
  _right{std::function<glm::vec3()>(std::bind(&CameraManager::_calculateRight, this))} {
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

    glm::vec3 up = glm::cross(_right.get(), _direction.get());

    if(debugCameraManager) {
        std::cerr << "PiEngine: camera looking towards " << (_cameraPos + _direction.get()) << std::endl;
        std::cerr << "          _cameraPos = " << _cameraPos << std::endl;
        std::cerr << "          direction = " << _direction.get() << std::endl;
        std::cerr << "          up = " << up << std::endl;
    }

    return glm::lookAt(
        _cameraPos, // camera pos
        _cameraPos + _direction.get(), // look dir
        //direction,
        //glm::vec3{0, 0, 0},
        up // head dir
        );
}

glm::vec3 CameraManager::_calculateDirection() {
    return glm::vec3{
            cos(_cameraRot.y) * sin(_cameraRot.z),
            sin(_cameraRot.y),
            cos(_cameraRot.y) * cos(_cameraRot.z)
            };
}

glm::vec3 CameraManager::_calculateRight() {
    return glm::vec3{
        sin(_cameraRot.z - 3.14f / 2.0f),
        0,
        cos(_cameraRot.z - 3.14f / 2.0f)
        };
}
