#pragma once

class Shader {
private:
	unsigned int m_RendererID;

public:
	Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string &name, int val);
	void SetUniform4f(const std::string &name, float f0, float f1, float f2, float f3);
	void SetUniform2f(const std::string &name, float f0, float f1);
	void SetUniform1f(const std::string &name, float f);

private:
	int GetUniformLocation(const std::string &name);
	static unsigned int CompileShader(const char *const shaderSource, unsigned int type);
	static char *loadFile(std::string path);
	static unsigned int CreateProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID);
};

