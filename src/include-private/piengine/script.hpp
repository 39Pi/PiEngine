#pragma once

#include <filesystem>

#include <sol/sol.hpp>

struct RenderObject;

struct Script {
	Script(std::filesystem::path file);

	void fireOnAttach(std::shared_ptr<RenderObject> object);
	void fire(std::shared_ptr<RenderObject> object);

private:
	// TODO: better way than this
	std::string _code;

	sol::state _luaState;
};
