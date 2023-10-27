#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

std::ostream& operator<<(std::ostream& os, glm::vec3 const& vec);
std::ostream& operator<<(std::ostream& os, glm::vec2 const& vec);
