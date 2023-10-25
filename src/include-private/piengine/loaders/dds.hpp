#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace loaders {
namespace textures {

GLuint dds(std::filesystem::path file);

}
}