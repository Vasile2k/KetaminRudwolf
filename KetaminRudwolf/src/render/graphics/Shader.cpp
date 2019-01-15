#include "Shader.hpp"

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
	char *vertexShaderSource = loadFile(vertexShaderPath);
	char *fragmentShaderSource = loadFile(fragmentShaderPath);

	unsigned int vertexShaderID = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
	unsigned int fragmentShaderID = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	m_RendererID = createProgram(vertexShaderID, fragmentShaderID);
}

Shader::~Shader() {
	glDeleteProgram(m_RendererID);
}

void Shader::bind() const {
	glUseProgram(m_RendererID);
}

void Shader::unbind() const {
	glUseProgram(0);
}

unsigned int Shader::compileShader(const char *const shaderSource, unsigned int type) {
	unsigned int shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &shaderSource, nullptr);
	delete[] shaderSource;

	glCompileShader(shaderID);

	int compilationResult = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationResult);
	if (compilationResult != GL_TRUE) {
		std::cerr << "Failed to compile " << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment") << " shader." << std::endl;

		int infoLogLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char log[1024];
		glGetShaderInfoLog(shaderID, infoLogLength, nullptr, log);
		std::cerr << "Log: " << log << std::endl;

		glDeleteShader(shaderID);
	}

	return shaderID;
}

char *Shader::loadFile(std::string path) {
	FILE *stream = fopen(path.c_str(), "rt");
	if (stream == nullptr) {
		std::cerr << "Couldn't open file " << path.c_str() << "." << std::endl;
		return nullptr;
	}

	fseek(stream, 0, SEEK_END);
	unsigned long length = ftell(stream);

	char *shaderSource = new char[length + 1];
	shaderSource[length] = '\0';
	fseek(stream, 0, SEEK_SET);
	fread(shaderSource, 1, length, stream);
	fclose(stream);

	return shaderSource;
}

unsigned int Shader::createProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID) {
	unsigned int shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShaderID);
	glAttachShader(shaderID, fragmentShaderID);
	glLinkProgram(shaderID);

	int result;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		std::cerr << "Failed to link program" << std::endl;

		int infoLogLength;
		glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0) {
			char *log = new char[infoLogLength + 1];
			glGetProgramInfoLog(shaderID, infoLogLength, nullptr, log);
			std::cerr << "Log: " << log << std::endl;
			delete[] log;
		}
		return 0;
	}

	glDetachShader(shaderID, vertexShaderID);
	glDetachShader(shaderID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return shaderID;
}

int Shader::getUniformLocation(const std::string &name) {
	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1) {
		std::cout << "Uniform " << name.c_str() << " is not here." << std::endl;
	}
	return location;
}

void Shader::setUniform4f(const std::string &name, float f0, float f1, float f2, float f3) {
	glUniform4f(getUniformLocation(name), f0, f1, f2, f3);
}

void Shader::setUniform2f(const std::string &name, float f0, float f1) {
	glUniform2f(getUniformLocation(name), f0, f1);
}

void Shader::setUniform1f(const std::string &name, float f) {
	glUniform1f(getUniformLocation(name), f);
}

void Shader::setUniform1i(const std::string &name, int val) {
	glUniform1i(getUniformLocation(name), val);
}
