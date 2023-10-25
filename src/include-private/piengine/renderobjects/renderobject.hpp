#pragma once

#include <stdint.h>

#include <piengine/cached_var.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct RenderObject {
	virtual void draw() = 0;
	virtual ~RenderObject() = default;

	RenderObject();

	constexpr const glm::vec3& getPos() {
		return _pos;
	}

	constexpr const glm::quat& getRot() {
		return _rot;
	}

	void setPos(const glm::vec3& pos) {
		_pos = pos;
		_modelMatrix.clear();
	}

	void setRot(const glm::quat& rot) {
		_rot = rot;
		_rotMatrix.clear();
	}

	const glm::mat4& getModelMatrix() {
		return _modelMatrix.get();
	}

	const glm::mat4& getRotMatrix() {
		return _rotMatrix.get();
	}

	constexpr uint64_t getId() {
		return _id;
	}

private:
	glm::mat4 _computeModelMatrix();
	glm::mat4 _computeRotMatrix();

	glm::vec3 _pos{0.0f};
	glm::quat _rot;

	CachedVar<glm::mat4> _modelMatrix;
	CachedVar<glm::mat4> _rotMatrix;

	uint64_t _id;
};
