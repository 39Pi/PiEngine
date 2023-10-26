#pragma once

#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Texture {
	Texture();
	Texture(std::filesystem::path file);
	~Texture();

	void bind(GLenum unit = 0);

private:
	GLuint _texture;
};
