#include <piengine/iostream_out_ops.hpp>

std::ostream& operator<<(std::ostream& os, glm::vec3 const& vec) {
    return os << "vec3{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
}

std::ostream& operator<<(std::ostream& os, glm::vec2 const& vec) {
    return os << "vec2{" << vec.x << ", " << vec.y << "}";
}
