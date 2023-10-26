#pragma once
#include <filesystem>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Shader;
struct Texture;

struct Mesh {
	enum class Type {
		Coloured,
		Textured
	};

	Mesh();
	Mesh(Type type);
	Mesh(Type type, std::vector<GLfloat> vertex, std::vector<GLfloat> uv);
	Mesh(Type type, std::vector<GLfloat> vertex, std::vector<GLfloat> uv, std::shared_ptr<Texture> texture);

	~Mesh();

	void draw(glm::mat4 mvp) const;

	void updateMesh(std::vector<GLfloat> vertex, std::vector<GLfloat> uv);

	void updateShader(Type type) {
		_type = type;
	}

	void updateTexture(std::shared_ptr<Texture> texture) {
		_texture = std::move(texture);
	}

private:
	Type _type;

	std::vector<GLfloat> _vertex;
	std::vector<GLfloat> _uv;

	std::shared_ptr<Texture> _texture;

	void _generateBuffers();
	void _bufferData();

	GLuint VertexArrayID;
	GLuint vertexbuffer;
	GLuint elementbuffer;
	GLuint colourbuffer;
	GLuint vertex_size; 
};
