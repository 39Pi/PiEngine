#include <iostream>
#include <piengine/managers/render.hpp>

namespace {

constexpr bool debugRenderManager = true;

}

void RenderManager::addObject(std::shared_ptr<RenderObject> object) {
	if(debugRenderManager) {
		std::cerr << "PiEngine: RenderManager adding object with id " << object->getId() << std::endl;
	}

	objects.push_back(std::move(object));
}

void RenderManager::fireScripts() {
	for(auto object : objects) {
		object->fireScript(object);
	}
}

void RenderManager::draw() {
	for(auto object : objects) {
		object->draw();
	}
}
