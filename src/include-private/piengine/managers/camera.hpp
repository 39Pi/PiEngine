#pragma once

#include <piengine/cached_var.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct CameraManager {
	static inline CameraManager& the() {
		static CameraManager instance;
		return instance;
	}

	constexpr const glm::vec3& getPos() const {
		return _cameraPos;
	}

	constexpr const glm::vec3& getRot() const {
		return _cameraRot;
	}

	void setPos(const glm::vec3& pos) {
		_cameraPos = pos;
		_viewMatrix.clear();
	}

	void setRot(const glm::vec3& rot) {
		_cameraRot = rot;
		_viewMatrix.clear();
		_right.clear();
		_direction.clear();
	}

	void setWindowSize(int width, int height) {
		_windowWidth = width;
		_windowHeight = height;
		_projMatrix.clear();
	}

	constexpr int getWindowWidth() const {
		return _windowWidth;
	}

	constexpr int getWindowHeight() const {
		return _windowHeight;
	}

	const glm::mat4& getProjMatrix() {
		return _projMatrix.get();
	}

	const glm::mat4& getViewMatrix() {
		return _viewMatrix.get();
	}

	const glm::vec3& getDirectionVector() {
		return _direction.get();
	}

	const glm::vec3& getRightVector() {
		return _right.get();
	}

private:
	CameraManager();

	glm::mat4 _calculateProjMatrix();
	glm::mat4 _calculateViewMatrix();

	glm::vec3 _calculateDirection();
	glm::vec3 _calculateRight();

	int _windowWidth;
	int _windowHeight;

	glm::vec3 _cameraPos;
	glm::vec3 _cameraRot;

	CachedVar<glm::mat4> _projMatrix;
	CachedVar<glm::mat4> _viewMatrix;

	CachedVar<glm::vec3> _direction;
	CachedVar<glm::vec3> _right;
};
