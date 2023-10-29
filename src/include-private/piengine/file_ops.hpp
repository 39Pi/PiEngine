#pragma once

#include <stdio.h>

#include <string>
#include <filesystem>

namespace file_ops {

void setGlobalAssetPath(std::filesystem::path path);
std::filesystem::path getGlobalAssetPath();
std::string loadFile(std::filesystem::path file, bool cache = true);
FILE* loadFile(std::filesystem::path file, const char mode[]);

}
