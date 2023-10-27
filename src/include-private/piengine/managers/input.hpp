#pragma once

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// TODO: allow 2d mouse input (aka enabling the cursor and disabling "normal" mouse input)
struct InputManager {
	static inline InputManager& the() {
		static InputManager instance;
		return instance;
	}

	void init();
	void beginFrame();
	void endFrame();

	constexpr double deltaTime() {
		return _deltaTime;
	}

	constexpr glm::vec2 mousePos() {
		return _currentMousePos;
	}

	constexpr glm::vec2 mouseDelta() {
		return _deltaMousePos;
	}

	constexpr glm::vec2 normalisedMouseDeltaPos() {
		return _normalisedDeltaMousePos;
	}

	bool keyPressed(GLenum key);

private:
	InputManager();

	glm::vec2 _currentMousePos;
	glm::vec2 _deltaMousePos;
	glm::vec2 _normalisedDeltaMousePos;

	glm::vec2 _getMousePos();

	// This stores a map of key to key pressed this frame.
	// This is stored like this, so that no matter what implementation, a repeated call to query a key in a frame will always return the same thing.
	std::map<GLenum, bool> _pressedKeyMap;

	double _lastTime;
	double _deltaTime;
};
