#pragma once
#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Shader;

struct Mesh {
	Mesh();

	void draw(glm::mat4 mvp, std::shared_ptr<Shader> shader) const;

private:
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	GLuint elementbuffer;
	GLuint colourbuffer;
	GLuint vertex_size; 
};
