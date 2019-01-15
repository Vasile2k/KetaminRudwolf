#pragma once

class Texture {
private:
	std::string m_FilePath;
	unsigned int m_RendererID = 0;
	unsigned char *m_LocalBuffer = nullptr;
	int m_Width = 0;
	int m_Height = 0;
	int m_BPP = 0;

public:
	Texture(const std::string &path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	int getWidth() const;
	int getHeight() const;
};
