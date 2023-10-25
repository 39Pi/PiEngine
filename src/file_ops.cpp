#include <iostream>
#include <fstream>

#include <string.h>
#include <errno.h>

#include <piengine/file_ops.hpp>

namespace file_ops {

std::filesystem::path relativePrepend = "";

void setGlobalAssetPath(std::filesystem::path path) {
	relativePrepend = std::move(path);
}

std::filesystem::path getGlobalAssetPath() {
	return relativePrepend;
}

std::string loadFile(std::filesystem::path file) {
	std::ifstream stream(relativePrepend / file, std::ios::in);
	if(stream.fail()) {
		std::cerr << "PiEngine: loadFile(" << file << ") failed: " << strerror(errno) << std::endl;
		return std::string("");
	}
	std::stringstream sstr;
	sstr << stream.rdbuf();
	stream.close();
	return sstr.str();
}

FILE* loadFile(std::filesystem::path file, const char mode[]) {
	return fopen((relativePrepend / file).u8string().c_str(), mode);
}

}