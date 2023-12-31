#pragma once

#include <vector>
#include <memory>

#include <piengine/renderobjects/renderobject.hpp>

struct RenderManager {
	static inline RenderManager& the() {
		static RenderManager instance;
		return instance;
	}

	void addObject(std::shared_ptr<RenderObject> object);

	void fireScripts();

	void draw();

	std::shared_ptr<RenderObject> objectById(uint64_t id);
private:
	RenderManager() = default;

	std::vector<std::shared_ptr<RenderObject>> objects;
};
