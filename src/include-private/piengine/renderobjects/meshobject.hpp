#include <iostream>
#include <memory>

#include <piengine/mesh.hpp>
#include <piengine/renderobjects/renderobject.hpp>

struct MeshObject : RenderObject {
	MeshObject() = default;
	MeshObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader);

	void draw() override;

	void setMesh(std::shared_ptr<Mesh> mesh) {
		_mesh = mesh;
	}

	void setShader(std::shared_ptr<Shader> shader) {
		_shader = shader;
	}

private:
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Shader> _shader;
};
