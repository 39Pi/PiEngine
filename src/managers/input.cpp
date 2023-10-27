#include <piengine/managers/input.hpp>
#include <piengine/managers/window.hpp>

InputManager::InputManager() {
}

void InputManager::init() {
    glfwSetInputMode(WindowManager::the().getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(WindowManager::the().getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(WindowManager::the().getWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    _deltaTime = 0;
    _lastTime = glfwGetTime();

    _currentMousePos = _getMousePos();
}

void InputManager::beginFrame() {
	double now = glfwGetTime();
	_deltaTime = now - _lastTime;
	_lastTime = now;

	// Calcuate cursor diff
	glm::vec2 newMousePos = _getMousePos();
	_deltaMousePos = -(newMousePos - _currentMousePos);
	_normalisedDeltaMousePos = _deltaMousePos / WindowManager::the().getWindowSize();
	_currentMousePos = newMousePos;
}

void InputManager::endFrame() {
	// Clear the pressed key map for next frame
	_pressedKeyMap.clear();
}

bool InputManager::keyPressed(GLenum key) {
	// If we have queried this key this frame, return the previous result.
	if(auto search = _pressedKeyMap.find(key); search != _pressedKeyMap.end()) {
		return search->second;
	}

	// If we have not, query it from glfw, store the result and return.
	bool pressed = glfwGetKey(WindowManager::the().getWindow(), key) == GLFW_PRESS;
	_pressedKeyMap[key] = pressed;
	return pressed;
}

glm::vec2 InputManager::_getMousePos() {
	double _x;
	double _y;
	glfwGetCursorPos(WindowManager::the().getWindow(), &_x, &_y);
	return glm::vec2{_x, _y};
}
