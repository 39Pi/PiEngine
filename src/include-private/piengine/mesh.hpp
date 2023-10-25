#pragma once
#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Mesh {
	Mesh();

	void draw() const;

private:
	GLuint VertexArrayID, vertexbuffer, elementbuffer, vertex_size; 
};