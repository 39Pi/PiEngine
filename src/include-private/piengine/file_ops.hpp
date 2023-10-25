#pragma once

#include <string>
#include <filesystem>

namespace file_ops {

void setGlobalAssetPath(std::filesystem::path path);
std::filesystem::path getGlobalAssetPath();
std::string loadFile(std::filesystem::path file);

}