#include <phyzle/gfx/PhyShader.h>

#include <fstream>
#include <sstream>
#include <iostream>

PhyShader::PhyShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	 std::string vertCode;
	 std::string fragCode;
	 std::ifstream vShaderFile;
	 std::ifstream fShaderFile;

	 // Ensure ifstream objects can throw exceptions
	 vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	 fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		// Read files into stringstreams
		std::stringstream vShaderSS, fShaderSS;
		vShaderSS << vShaderFile.rdbuf();
		fShaderSS << fShaderFile.rdbuf();

		// Close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// Get string stream contents
		vertCode = vShaderSS.str();
		fragCode = fShaderSS.str();	
	}
	catch(std::ifstream::failure e)
	{
		std::cerr << "Failed to read shader file!" << std::endl;
	}

	const GLchar* vShaderCode = vertCode.c_str();
	const GLchar* fShaderCode = fragCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cerr << "Vertex shader failed to compile!\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cerr << "Fragment shader failed to compile!\n" << infoLog << std::endl;
	}

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cerr << "Failed to link shader program\n" << infoLog << std::endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void PhyShader::use()
{
	glUseProgram(m_ID);
}




void PhyShader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), static_cast<GLint>(value));
}
void PhyShader::setBool(const std::string& name, GLboolean value)
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), static_cast<GLint>(value));
}
void PhyShader::setInt(const std::string& name, GLint value)
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}
void PhyShader::setFloat(const std::string& name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

