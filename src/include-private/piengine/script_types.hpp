#pragma once

#include <string>
#include <sstream>

namespace script_types {

struct vec3 {
	float x;
	float y;
	float z;

	vec3()
	: x{0}, y{0}, z{0} {}

	vec3(float a)
	: x{a}, y{a}, z{a} {}

	vec3(float x, float y, float z)
	: x{x}, y{y}, z{z} {}

	std::string to_string() {
		std::stringstream stream;
		stream << "vec3{" << x << ", " << y << ", " << z << "}";
		return stream.str();
	}

	vec3 operator+(const vec3& rhs) {
		return vec3{
			x + rhs.x,
			y + rhs.y,
			z + rhs.z
		};
	}
	vec3 operator-(const vec3& rhs) {
		return vec3{
			x - rhs.x,
			y - rhs.y,
			z - rhs.z
		};
	}
	vec3 operator*(const vec3& rhs) {
		return vec3{
			x * rhs.x,
			y * rhs.y,
			z * rhs.z
		};
	}
	vec3 operator/(const vec3& rhs) {
		return vec3{
			x / rhs.x,
			y / rhs.y,
			z / rhs.z
		};
	}
};

struct rot {
	float around_x;
	float around_y;
	float around_z;

	rot()
	: around_x{0}, around_y{0}, around_z{0} {}

	rot(float a)
	: around_x{a}, around_y{a}, around_z{a} {}

	rot(float around_x, float around_y, float around_z)
	: around_x{around_x}, around_y{around_y}, around_z{around_z} {}

	std::string to_string() {
		std::stringstream stream;
		stream << "rot{" << around_x << ", " << around_y << ", " << around_z << "}";
		return stream.str();
	}

	rot operator+(const rot& rhs) {
		return rot{
			around_x + rhs.around_x,
			around_y + rhs.around_y,
			around_z + rhs.around_z
		};
	}
	rot operator-(const rot& rhs) {
		return rot{
			around_x - rhs.around_x,
			around_y - rhs.around_y,
			around_z - rhs.around_z
		};
	}
	rot operator*(const rot& rhs) {
		return rot{
			around_x * rhs.around_x,
			around_y * rhs.around_y,
			around_z * rhs.around_z
		};
	}
	rot operator/(const rot& rhs) {
		return rot{
			around_x / rhs.around_x,
			around_y / rhs.around_y,
			around_z / rhs.around_z
		};
	}
};

}
