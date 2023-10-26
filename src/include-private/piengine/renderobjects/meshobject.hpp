#include <iostream>
#include <memory>

#include <piengine/mesh.hpp>
#include <piengine/renderobjects/renderobject.hpp>

struct MeshObject : RenderObject {
	MeshObject() = default;
	MeshObject(std::shared_ptr<Mesh> mesh);

	void draw() override;

	void setMesh(std::shared_ptr<Mesh> mesh) {
		_mesh = mesh;
	}

	constexpr std::shared_ptr<Mesh>& getMesh() {
		return _mesh;
	}

private:
	std::shared_ptr<Mesh> _mesh;
};
