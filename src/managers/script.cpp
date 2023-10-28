#include <iostream>

#include <sol/raii.hpp>
#include <sol/property.hpp>

#include <piengine/renderobjects/renderobject.hpp>
#include <piengine/renderobjects/meshobject.hpp>
#include <piengine/managers/script.hpp>
#include <piengine/script.hpp>
#include <sol/types.hpp>

void ScriptManager::initialize() {
	_luaState = _createLuaState();
}

sol::state ScriptManager::_createLuaState() {
	sol::state luaState;
	luaState.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::io);

	// Register generic script types
	auto luaPiengineNamespace = _luaState["piengine"].get_or_create<sol::table>();
	
	auto vec3 = luaState.new_usertype<script_types::vec3>("vec3", 
		sol::constructors<script_types::vec3(), script_types::vec3(float), script_types::vec3(float, float, float)>(),
		sol::meta_function::addition,
		&script_types::vec3::operator+,
		sol::meta_function::subtraction,
		&script_types::vec3::operator-,
		sol::meta_function::multiplication,
		&script_types::vec3::operator*,
		sol::meta_function::division,
		&script_types::vec3::operator/
		);
	vec3["x"] = &script_types::vec3::x;
	vec3["y"] = &script_types::vec3::y;
	vec3["z"] = &script_types::vec3::z;

	auto rot = luaState.new_usertype<script_types::rot>("rot", 
		sol::constructors<script_types::rot(), script_types::rot(float), script_types::rot(float, float, float)>(),
		sol::meta_function::addition,
		&script_types::rot::operator+,
		sol::meta_function::subtraction,
		&script_types::rot::operator-,
		sol::meta_function::multiplication,
		&script_types::rot::operator*,
		sol::meta_function::division,
		&script_types::rot::operator/
		);
	rot["around_x"] = &script_types::rot::around_x;
	rot["around_y"] = &script_types::rot::around_y;
	rot["around_z"] = &script_types::rot::around_z;

	// Register object types
	auto renderObject = luaState.new_usertype<RenderObject>("RenderObject");
	renderObject["pos"] = sol::property(&RenderObject::getScriptPos, &RenderObject::setScriptPos);
	renderObject["rot"] = sol::property(&RenderObject::getScriptRot, &RenderObject::setScriptRot);

	auto meshObject = luaState.new_usertype<MeshObject>("MeshObject");
	meshObject["pos"] = sol::property(&MeshObject::getScriptPos, &MeshObject::setScriptPos);
	meshObject["rot"] = sol::property(&MeshObject::getScriptRot, &MeshObject::setScriptRot);

	return luaState;
}
