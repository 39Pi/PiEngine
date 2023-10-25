#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <piengine/cached_var.hpp>

struct CameraManager {
	static CameraManager& the() {
		static CameraManager instance;
		return instance;
	}

	constexpr const glm::vec3& getPos() {
		return _cameraPos;
	}

	void setPos(const glm::vec3& pos) {
		_cameraPos = pos;
		_viewMatrix.clear();
	}

	void setWindowSize(int width, int height) {
		_windowWidth = width;
		_windowHeight = height;
		_projMatrix.clear();
	}

	const glm::mat4& getProjMatrix() {
		return _projMatrix.get();
	}

	const glm::mat4& getViewMatrix() {
		return _viewMatrix.get();
	}

private:
	CameraManager();

	glm::mat4 _calculateProjMatrix();
	glm::mat4 _calculateViewMatrix();

	int _windowWidth;
	int _windowHeight;

	glm::vec3 _cameraPos;

	CachedVar<glm::mat4> _projMatrix;
	CachedVar<glm::mat4> _viewMatrix;
};
