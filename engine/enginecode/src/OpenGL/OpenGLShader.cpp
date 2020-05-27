
#include "engine_pch.h"
#include "..\..\include\independent\platform\OpenGL\OpenGLShader.h"

#include <fstream>
#include <sstream>
#include "systems/MyLogger.h"
#include <glm/gtc/type_ptr.hpp>



namespace Engine
{
	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::fstream handle(filepath, std::ios::in);
		enum { NONE = -1, VERTEX = 0, FRAGMENT } region;
		if (handle.is_open()) ENGINE_CORE_CRITICAL("Could not open shader file '{0]'. ", filepath);

		std::string line, src[2];
		while (getline(handle, line))
		{
			//Determine shader src type
			if (line.find("#region Vertex") != std::string::npos) { region = VERTEX; continue; }
			if (line.find("#region Fragment") != std::string::npos) { region = FRAGMENT; continue; }
			if (line.find("#region Geomentry") != std::string::npos) { region = NONE; continue; }
			if (line.find("#region Tessalation") != std::string::npos) { region = NONE; continue; }

			if (region != NONE) src[region] += (line + "\n");
		}

		handle.close();

		compileAndLink(src[VERTEX], src[FRAGMENT]);
	}
	OpenGLShader::OpenGLShader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
	{
		std::fstream handle;
		enum { VERTEX = 0, FRAGMENT } region;
		std::string line, src[2];

		handle.open(vertexFilePath, std::ios::in);
		if (!handle.is_open()) ENGINE_CORE_CRITICAL("Could not open shader file '{0}' .", vertexFilePath);

		while (getline(handle, line))
		{
			src[VERTEX] += line;
		}
		handle.close();

		handle.open(fragmentFilePath, std::ios::in);
		if (!handle.is_open()) ENGINE_CORE_CRITICAL("Could not open shader file '{0}' .", fragmentFilePath);

		while (getline(handle, line))
		{
			src[FRAGMENT] += line;
		}
		handle.close();

		compileAndLink(src[VERTEX], src[FRAGMENT]);
	}
	void OpenGLShader::Bind() const
	{
		glUseProgram(getRenderedID());
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::setUniformMat4(const std::string& name, glm::mat4 matrix)
	{
		//UploadUniformMat4(name, data);
	}

	void OpenGLShader::setUniformFloat3(const std::string& name, float a, float b, float c)
	{
		uploadFloat3(name, a, b, c);
	}

	void OpenGLShader::setUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadFloat4(name, value);
	}

	void OpenGLShader::UploadUniformMat4(const std::string & name, float* data)
	{
		GLuint loc = glGetUniformLocation(getRenderedID(), name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, data);
	}

	void OpenGLShader::UploadFloat4(const std::string& name, const glm::vec4& data)
	{
		GLint loc = glad_glGetUniformLocation(getRenderedID(), name.c_str());
		glUniform4f(loc, data.x, data.y, data.z, data.w);
	}

	void OpenGLShader::uploadFloat3(const std::string & name, float a, float b, float c)
	{
		GLuint loc = glGetUniformLocation(getRenderedID(), name.c_str());
		glUniform3f(loc, a, b, c);
	}

	void OpenGLShader::uploadInt(const std::string & name, int data)
	{
		GLuint loc = glGetUniformLocation(getRenderedID(), name.c_str());
		glUniform1i(loc, data);
	}
	void OpenGLShader::dispatchUniformUpload(ShaderDataType type, GLuint location, void* data)
	{
		const float* addrf;
		const int* addri;
		GLfloat valueFloat;
		GLint valueInt;

		if (type == ShaderDataType::Bool)
		{
			valueInt = *(bool*)data;
			glUniform1i(location, valueInt);
		}
		else if (type == ShaderDataType::Int)
		{
			valueInt = *(int*)data;
			glUniform1i(location, valueInt);
		}
		else if (type == ShaderDataType::Int2)
		{
			addri = (const int*)data;
			glUniform2iv(location, 1, addri);
		}
		else if (type == ShaderDataType::Int3)
		{
			addri = (const int*)data;
			glUniform3iv(location, 2, addri);
		}
		else if (type == ShaderDataType::Int4)
		{
			addri = (const int*)data;
			glUniform4iv(location, 3, addri);
		}
		else if (type == ShaderDataType::Float)
		{
			valueFloat = *(float*)data;
			glUniform1i(location, valueFloat);
		}
		else if (type == ShaderDataType::Float2)
		{
			addrf = (const float*)data;
			glUniform2fv(location, 1, addrf);
		}
		else if (type == ShaderDataType::Float3)
		{
			addrf = (const float*)data;
			glUniform3fv(location, 2, addrf);
		}
		else if (type == ShaderDataType::Float4)
		{
			addrf = (const float*)data;
			glUniform4fv(location, 3, addrf);
		}
		else if (type == ShaderDataType::Mat3)
		{
			addrf = (const float*)data;
			glUniformMatrix3fv(location, 1, GL_FALSE, addrf);
		}
		else if (type == ShaderDataType::Mat4)
		{
			addrf = (const float*)data;
			glUniformMatrix4fv(location, 1, GL_FALSE, addrf);
		}
	}
	void OpenGLShader::compileAndLink(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
	{
		// Compile Vertex Shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* src = vertexShaderSrc.c_str();
		glShaderSource(vertexShader, 1, &src, 0);
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog;
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			std::string errorString(infoLog.begin(), infoLog.end());
			 ENGINE_CORE_CRITICAL("Vertex shader compile failiure:\n {0]", errorString);

			glDeleteShader(vertexShader);
			return;
		}

		// Compile Fragment Shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		src = fragmentShaderSrc.c_str();
		glShaderSource(fragmentShader, 1, &src, 0);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			std::string errorString(infoLog.begin(), infoLog.end());
			 ENGINE_CORE_CRITICAL("Fragment shader compile failure:\n {0}", errorString);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			return;
		}

		// Link Shaders
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, fragmentShader);
		glAttachShader(m_RendererID, vertexShader);
		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			std::string errorString(infoLog.begin(), infoLog.end());
			 ENGINE_CORE_CRITICAL("Shader linker failure:\n {0}", errorString);

			glDeleteProgram(m_RendererID);
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			return;
		}
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}
}
