#pragma once
#include <filesystem>
#include <cassert>

#include <piengine/cached_var.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Shader {
	Shader(std::filesystem::path vertexShaderFile, std::filesystem::path fragmentShaderFile);

	constexpr GLuint programID() const {
		return _programID;
	}

	constexpr bool good() const {
		return _good;
	}

	void enable() const {
		assert(_good);
		glUseProgram(_programID);
	}

	inline GLuint getMvpId() {
		return _mvpID.get();
	}
private:
	GLuint _vertexShader;
	GLuint _fragmentShader;
	GLuint _programID;

	CachedVar<GLuint> _mvpID;

	GLuint _getMvpId() {
		assert(_good);
		return glGetUniformLocation(_programID, "MVP");
	}

	bool _good = false;
};