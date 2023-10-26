#include <iostream>
#include <piengine/texture.hpp>
#include <piengine/loaders/dds.hpp>

namespace {

constexpr bool debugTextures = true;

}

Texture::Texture(std::filesystem::path file) {
	_texture = loaders::textures::dds(file);
}

Texture::~Texture() {
	glDeleteTextures(1, &_texture);
	if(debugTextures) {
		std::cerr << "PiEngine: deleted texture" << std::endl;
	}
}

void Texture::bind(GLenum unit) {
	glActiveTexture(unit);
	glBindTexture(GL_TEXTURE_2D, _texture);
}
