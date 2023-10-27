#pragma once

#include <memory>
#include <piengine/shader.hpp>

struct ShaderManager {
	static inline ShaderManager& the() {
		static ShaderManager instance;
		return instance;
	}

	std::shared_ptr<Shader> colorShader;
	std::shared_ptr<Shader> textureShader;
private:
	ShaderManager() = default;
};
