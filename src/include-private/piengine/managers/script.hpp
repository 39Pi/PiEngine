#pragma once


struct ScriptManager {
	static ScriptManager& the() {
		static ScriptManager instance;
		return instance;
	}

private:
	ScriptManager() = default;
};
