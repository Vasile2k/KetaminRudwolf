#pragma once

class Shader {
private:
	unsigned int m_RendererID;

public:
	Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform1i(const std::string &name, int val);
	void setUniform4f(const std::string &name, float f0, float f1, float f2, float f3);
	void setUniform2f(const std::string &name, float f0, float f1);
	void setUniform1f(const std::string &name, float f);

private:
	int getUniformLocation(const std::string &name);
	static unsigned int compileShader(const char *const shaderSource, unsigned int type);
	static char *loadFile(std::string path);
	static unsigned int createProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID);
};

