#include <iostream>
#include <string>
#include <piengine/shader.hpp>
#include <piengine/file_ops.hpp>

namespace {

constexpr bool debugShaders = true;

}

Shader::Shader(std::filesystem::path vertexShaderFile, std::filesystem::path fragmentShaderFile) {
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Compile vertex shader
	{
		std::string vertexShaderCode = file_ops::loadFile(vertexShaderFile);
	
		if(vertexShaderCode.empty()) {
			std::cerr << "PiEngine: failed to construct Shader: vertex shader file load error" << std::endl;
			return;
		}

		const char* vertexShaderCodeCStr = vertexShaderCode.c_str();
		glShaderSource(_vertexShader, 1, &vertexShaderCodeCStr, NULL);
		glCompileShader(_vertexShader);

		// Check if the shader was compiled correctly
		GLint result;
		int infoLogLen;
		glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(_vertexShader, GL_INFO_LOG_LENGTH, &infoLogLen);

		if(infoLogLen > 0) {
			std::string infoLog(infoLogLen, ' ');
			char* infoLogCStr = (char*)infoLog.c_str();
			glGetShaderInfoLog(_vertexShader, infoLogLen, NULL, infoLogCStr);
			std::cerr << "PiEngine: compilation of shader \"" << vertexShaderFile << "\" caused logs:" << std::endl;
			std::cerr << infoLog << std::endl;
		}
		if(result != GL_TRUE) {
			std::cerr << "PiEngine: failed to compile shader \"" << vertexShaderFile << "\"" << std::endl;
			return;
		}
	}
	// Compile fragment shader
	{
		std::string fragmentShaderCode = file_ops::loadFile(fragmentShaderFile);
		
		if(fragmentShaderCode.empty()) {
			std::cerr << "PiEngine: failed to construct Shader: fragment shader file load error" << std::endl;
			return;
		}

		const char* fragmentShaderCodeCStr = fragmentShaderCode.c_str();
		glShaderSource(_fragmentShader, 1, &fragmentShaderCodeCStr, NULL);
		glCompileShader(_fragmentShader);

		// Check if the shader was compiled correctly
		GLint result;
		int infoLogLen;
		glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(_fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLen);

		if(infoLogLen > 0) {
			std::string infoLog(infoLogLen, ' ');
			char* infoLogCStr = (char*)infoLog.c_str();
			glGetShaderInfoLog(_fragmentShader, infoLogLen, NULL, infoLogCStr);
			std::cerr << "PiEngine: compilation of shader \"" << vertexShaderFile << "\" caused logs:" << std::endl;
			std::cerr << infoLog << std::endl;
		}
		if(result != GL_TRUE) {
			std::cerr << "PiEngine: failed to compile shader \"" << vertexShaderFile << "\"" << std::endl;
			return;
		}
	}

	// Link the program
	{
		_programID = glCreateProgram();
		glAttachShader(_programID, VertexShaderID);
		glAttachShader(_programID, FragmentShaderID);
		glLinkProgram(_programID);

		// Check the program
		GLint result;
		int infoLogLen;
		glGetProgramiv(_programID, GL_LINK_STATUS, &result);
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &infoLogLen);
		if(infoLogLen > 0){
			std::string infoLog(infoLogLen, ' ');
			char* infoLogCStr = (char*)infoLog.c_str();
			glGetProgramInfoLog(_programID, infoLogLen, NULL, infoLogCStr);
			std::cerr << "PiEngine: linking of shaders {" << vertexShaderFile << ", " << fragmentShaderFile << "}" << std::endl
		}
	}
	if(debugShaders)
		std::cerr << "PiEngine: built shaders {" << vertexShaderFile << ", " << fragmentShaderFile << "}" << std::endl;

	_good = true;
}