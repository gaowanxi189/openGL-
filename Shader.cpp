#include "Shader.h"

Shader::Shader()
{
	m_shaderProgram = 0;
}

void Shader::initShader(std::string& _vertexPath, std::string& _fragPath)
{
	std::ifstream _vShaderFile, _fShaderFile;
	std::string _vertexCode, _fragCode;
	_vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	_fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		_vShaderFile.open(_vertexPath);
		std::stringstream _vStream, _fStream;
		_vStream << _vShaderFile.rdbuf();

		_fShaderFile.open(_fragPath);
		_fStream << _fShaderFile.rdbuf();

		_vertexCode = _vStream.str();
		_fragCode = _fStream.str();

	}
	catch (const std::exception&)
	{
		return;
	}
	const char* _vertexStr = _vertexCode.c_str();
	const char* _fragStr = _fragCode.c_str();
	//shader错误检测
	char _infoLog[512];
	int	_sucessFlag = 0;

	//编译shader
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &_vertexStr, NULL);
	glCompileShader(vertexshader);
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &_sucessFlag);//错误检测真的很重要。
	if (!_sucessFlag) {
		glGetShaderInfoLog(vertexshader, 512, NULL, _infoLog);
		std::string err(_infoLog);
		std::cout << err << std::endl;
	}

	GLuint fragshader = glCreateShader(GL_FRAGMENT_SHADER);//这一处一定要注意参数要写对。
	glShaderSource(fragshader, 1, &_fragStr, NULL);
	glCompileShader(fragshader);
	glGetShaderiv(fragshader, GL_COMPILE_STATUS, &_sucessFlag);
	if (!_sucessFlag) {
		glGetShaderInfoLog(fragshader, 512, NULL, _infoLog);
		std::string err(_infoLog);
		std::cout << err << std::endl;
	}

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexshader);
	glAttachShader(m_shaderProgram, fragshader);
	glLinkProgram(m_shaderProgram);

	glDeleteShader(vertexshader);
	glDeleteShader(fragshader);

}

void Shader::setMatrix(const string& _name, glm::mat4 _matrix)
{

}
