#pragma once

#include <sol/sol.hpp>

struct Script;

struct ScriptManager {
	friend Script;
	
	static ScriptManager& the() {
		static ScriptManager instance;
		return instance;
	}

	void initialize();

protected:
	sol::state _createLuaState();

private:
	ScriptManager() = default;

	sol::state _luaState;
};
