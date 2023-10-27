#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct WindowManager {
	static inline WindowManager& the() {
		static WindowManager instance;
		return instance;
	}

	bool createWindow(std::string title, int width, int height);
	
	constexpr GLFWwindow* getWindow() const {
		return _window;
	}

	glm::vec2 getWindowSize();

private:
	WindowManager();

	GLFWwindow* _window;
};
