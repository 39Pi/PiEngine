#pragma once
#include <filesystem>
#include <cassert>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Shader {
	Shader(std::filesystem::path vertexShaderFile, std::filesystem::path fragmentShaderFile);

	constexpr GLuint programID() {
		return _programID;
	}

	constexpr bool good() {
		return _good;
	}

	void enable() {
		assert(_good);
		glUseProgram(_programID);
	}
private:
	GLuint _vertexShader;
	GLuint _fragmentShader;
	GLuint _programID;

	bool _good = false;
};