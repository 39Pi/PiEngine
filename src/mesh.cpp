#include <iostream>
#include <piengine/mesh.hpp>

namespace {

constexpr bool debugMeshes = true;

}
// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
};

Mesh::Mesh() {
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);



	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// glGenBuffers(1, &elementbuffer);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);

	vertex_size = sizeof(g_vertex_buffer_data) / sizeof(GLfloat) / 3;

	if(debugMeshes)
		std::cerr << "PiEngine: constructed mesh object, vertex_size=" << vertex_size << std::endl;
}

void Mesh::draw() const {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0, 					// attr 0
		vertex_size, 		// vertex count
		GL_FLOAT, 			// data type
		GL_FALSE, 			// not normalized
		0, 					// stride
		(void*)0			// buffer offset
	);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawArrays(GL_TRIANGLES, 0, vertex_size);
	glDisableVertexAttribArray(0);
}