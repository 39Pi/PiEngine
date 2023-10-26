#include <iostream>
#include <piengine/managers/shader.hpp>
#include <piengine/shader.hpp>
#include <piengine/mesh.hpp>
#include <piengine/texture.hpp>

namespace {
    constexpr bool debugMeshes = true;
}

Mesh::Mesh() {
    _generateBuffers();
}

Mesh::Mesh(Type type) {
    _generateBuffers();
    updateShader(type);
}

Mesh::Mesh(Type type, std::vector<GLfloat> vertex, std::vector<GLfloat> uv) {
    _generateBuffers();
    updateShader(type);
    updateMesh(vertex, uv);
}

Mesh::Mesh(Type type, std::vector<GLfloat> vertex, std::vector<GLfloat> uv, std::shared_ptr<Texture> texture) {
    _generateBuffers();
    updateShader(type);
    updateMesh(vertex, uv);
    updateTexture(texture);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colourbuffer);
    // glDeleteBuffers(1, &elementbuffer);

    if(debugMeshes) {
        std::cerr << "PiEngine: deleted mesh object" << std::endl;
    }
}

void Mesh::draw(glm::mat4 mvp) const {
    std::shared_ptr<Shader> shader;
    switch(_type) {
    case Mesh::Type::Coloured: {
        shader = ShaderManager::the().colorShader;
        break;
    }
    case Mesh::Type::Textured: {
        shader = ShaderManager::the().textureShader;
        break;
    }
    }
    shader->enable();

	glUniformMatrix4fv(shader->getMvpId(), 1, GL_FALSE, &mvp[0][0]);

    if(_type == Mesh::Type::Textured) {
        assert(_texture);
        _texture->bind(GL_TEXTURE0);
    }

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0, 					// attr 0
		3, 					// vertex count
		GL_FLOAT, 			// data type
		GL_FALSE, 			// not normalized
		0, 					// stride
		(void*)0			// buffer offset
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	glVertexAttribPointer(
		1, 					// attr 0
		_type == Mesh::Type::Textured ? 2 : 3, 					// vertex count
		GL_FLOAT, 			// data type
		GL_FALSE, 			// not normalized
		0, 					// stride
		(void*)0			// buffer offset
	);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawArrays(GL_TRIANGLES, 0, vertex_size);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Mesh::updateMesh(std::vector<GLfloat> vertex, std::vector<GLfloat> uv) {
    _vertex = std::move(vertex);
    _uv = std::move(uv);

    _bufferData();
}

void Mesh::_generateBuffers() {
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexbuffer);
    glGenBuffers(1, &colourbuffer);
    // glGenBuffers(1, &elementbuffer);
}

void Mesh::_bufferData() {
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertex.size(), _vertex.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _uv.size(), _uv.data(), GL_STATIC_DRAW);
    
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);

    vertex_size = _vertex.size() / 3;

    if(debugMeshes)
        std::cerr << "PiEngine: buffered mesh object, vertex_size=" << vertex_size << std::endl;
}
