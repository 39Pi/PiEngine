#include <cassert>

#include <piengine/renderobjects/meshobject.hpp>
#include <piengine/managers/camera.hpp>

namespace {
	constexpr bool debugMeshObject = true;
}

MeshObject::MeshObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader)
: _mesh{mesh}, _shader{shader} {
	if(debugMeshObject) {
		std::cerr << "PiEngine! constructed MeshObject with id " << getId() << std::endl;
	}
}

void MeshObject::draw() {
	assert(_mesh);

	// Calculate MVP Matrix, using the current global view and projection matrix
	glm::mat4 mvp = CameraManager::the().getProjMatrix() * CameraManager::the().getViewMatrix() * getModelMatrix();

	_mesh->draw(mvp, _shader);
}
