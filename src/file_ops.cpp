#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>

#include <string.h>
#include <errno.h>

#include <piengine/file_ops.hpp>

namespace file_ops {

std::filesystem::path relativePrepend = "";

std::map<std::filesystem::path, std::string> stringFileCache;

void setGlobalAssetPath(std::filesystem::path path) {
	relativePrepend = std::move(path);
}

std::filesystem::path getGlobalAssetPath() {
	return relativePrepend;
}

std::string loadFile(std::filesystem::path file, bool cache) {
	if(auto it = stringFileCache.find(file); it != stringFileCache.end() && cache) {
		return it->second;
	}

	std::ifstream stream(relativePrepend / file, std::ios::in);
	if(stream.fail()) {
		std::cerr << "PiEngine: loadFile(" << file << ") failed: " << strerror(errno) << std::endl;
		return std::string("");
	}
	std::stringstream sstr;
	sstr << stream.rdbuf();
	stream.close();

	if(cache) {
		stringFileCache[file] = sstr.str();
	}

	return sstr.str();
}

FILE* loadFile(std::filesystem::path file, const char mode[]) {
	// TODO: what happens when there are unicode chars here?
	return fopen((relativePrepend / file).string().c_str(), mode);
}

}
