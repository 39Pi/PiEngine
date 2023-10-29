#pragma once

#include <memory>
#include <stdint.h>

#include <piengine/cached_var.hpp>
#include <piengine/script.hpp>
#include <piengine/script_types.hpp>

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

	constexpr const glm::vec3& getRot() {
		return _rot;
	}

	void setPos(const glm::vec3& pos) {
		_pos = pos;
		_modelMatrix.clear();
	}

	void setRot(const glm::vec3& rot) {
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


	// Script stuff
	void attachScript(std::shared_ptr<Script> script, std::shared_ptr<RenderObject> self) {
		_script = script;
		_script->fireOnAttach(self);
	}

	void fireScript(std::shared_ptr<RenderObject> self);

	script_types::vec3 getScriptPos() {
		return script_types::vec3{_pos.x, _pos.y, _pos.z};
	}

	void setScriptPos(script_types::vec3 pos) {
		_pos = glm::vec3{pos.x, pos.y, pos.z};
		_modelMatrix.clear();
	}

	script_types::rot getScriptRot() {
		return script_types::rot{_rot.x, _rot.y, _rot.z};
	}

	void setScriptRot(script_types::rot rot) {
		_rot = glm::vec3{rot.around_x, rot.around_y, rot.around_z};
		_rotMatrix.clear();
	}

private:
	glm::mat4 _computeModelMatrix();
	glm::mat4 _computeRotMatrix();

	glm::vec3 _pos{0.0f};
	glm::vec3 _rot{0.0f};

	CachedVar<glm::mat4> _modelMatrix;
	CachedVar<glm::mat4> _rotMatrix;

	std::shared_ptr<Script> _script;

	uint64_t _id;
};
