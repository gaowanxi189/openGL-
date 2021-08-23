#pragma once
#include "Base.h"
using std::string;
class Shader
{
private:
	GLuint m_shaderProgram;
	
public:
	Shader();
	~Shader(){}
	void start() { glUseProgram(m_shaderProgram); }
	void end() { glUseProgram(0); }
	GLuint getShadervalue() {
		return m_shaderProgram;
	}
	void initShader(std::string& _vertexPath, std::string& _fragPath);
	void setMatrix(const string& _name, glm::mat4 _matrix);
};

