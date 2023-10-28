#include <iostream>

#include <piengine/managers/input.hpp>
#include <piengine/managers/script.hpp>
#include <piengine/renderobjects/renderobject.hpp>
#include <piengine/file_ops.hpp>
#include <piengine/script.hpp>
#include <piengine/script_types.hpp>
#include <sol/forward.hpp>
#include <sol/state_handling.hpp>


Script::Script(std::filesystem::path file) {
	_code = file_ops::loadFile(file);
	_luaState = ScriptManager::the()._createLuaState();

	_luaState.script(_code);
}

void Script::fireOnAttach(std::shared_ptr<RenderObject> object) {
	sol::protected_function onAttach(_luaState["onAttach"]);

	if(onAttach.valid()) {
		auto result = onAttach(object);
		if(!result.valid()) {
			sol::error error = result;
			std::cerr << "PiEngine: onAttach() call failed: " << error.what() << std::endl;
		}
	}
}

void Script::fire(std::shared_ptr<RenderObject> object) {
	sol::protected_function loop(_luaState["loop"]);

	if(loop.valid()) {
		auto result = loop(object, InputManager::the().deltaTime());	
		if(!result.valid()) {
			sol::error error = result;
			std::cerr << "PiEngine: loop() call failed: " << error.what() << std::endl;
		}
	}
}
