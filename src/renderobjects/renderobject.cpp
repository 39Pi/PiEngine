#include <piengine/renderobjects/renderobject.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace {

uint64_t next_id = 1;

}

RenderObject::RenderObject()
: _modelMatrix{std::function<glm::mat4()>(std::bind(&RenderObject::_computeModelMatrix, this))}, 
  _rotMatrix{std::function<glm::mat4()>(std::bind(&RenderObject::_computeRotMatrix, this))}, _id{next_id++} {
}

glm::mat4 RenderObject::_computeModelMatrix() {
	return glm::translate(glm::mat4(1.0f), _pos);
}

glm::mat4 RenderObject::_computeRotMatrix() {
	return glm::toMat4(_rot);
}
