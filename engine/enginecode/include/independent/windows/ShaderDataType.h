#pragma once
/**
\class for Shader Data Types
*/
#include <string>
#include <glad/glad.h>
enum class ShaderDataType
{
	None = 0, Int, Int2, Int3, Int4, Float, Float2, Float3, Float4, Mat3, Mat4, Bool, Sampler2D
};

static unsigned int ShaderDataTypeSize(ShaderDataType type)
{
	if (type == ShaderDataType::Int)		return 4;
	if (type == ShaderDataType::Int2)		return 4 * 2;
	if (type == ShaderDataType::Int3)		return 4 * 3;
	if (type == ShaderDataType::Int4)		return 4 * 4;
	if (type == ShaderDataType::Float)		return 4;
	if (type == ShaderDataType::Float)		return 4 * 2;
	if (type == ShaderDataType::Float)		return 4 * 3;
	if (type == ShaderDataType::Float)		return 4 * 4;
	if (type == ShaderDataType::Mat3)		return 4 * 3 * 3;
	if (type == ShaderDataType::Mat4)		return 4 * 4 * 4;
	if (type == ShaderDataType::Bool)		return 1;
	if (type == ShaderDataType::Sampler2D)	return 1;
}

static unsigned int ShaderDataTypeComponentCount(ShaderDataType type)
{
	if (type == ShaderDataType::Int)		return 4;
	if (type == ShaderDataType::Int2)		return 4 * 2;
	if (type == ShaderDataType::Int3)		return 4 * 3;
	if (type == ShaderDataType::Int4)		return 4 * 4;
	if (type == ShaderDataType::Float)		return 4;
	if (type == ShaderDataType::Float)		return 4 * 2;
	if (type == ShaderDataType::Float)		return 4 * 3;
	if (type == ShaderDataType::Float)		return 4 * 4;
	if (type == ShaderDataType::Mat3)		return 4 * 3 * 3;
	if (type == ShaderDataType::Mat4)		return 4 * 4 * 4;
	if (type == ShaderDataType::Bool)		return 1;
	if (type == ShaderDataType::Sampler2D)	return 1;
}

static unsigned int ShaderDataTypeGLSLStrToSDT(const std::string& glslSrc)
{
	if (glslSrc == "int")					ShaderDataType::Int;
	if (glslSrc == "ivec2")					ShaderDataType::Int2;
	if (glslSrc == "ivec3")					ShaderDataType::Int3; 
	if (glslSrc == "ivec4")					ShaderDataType::Int4; 
	if (glslSrc == "float")					ShaderDataType::Float;
	if (glslSrc == "vec2")					ShaderDataType::Float;
	if (glslSrc == "vec3")					ShaderDataType::Float;
	if (glslSrc == "vec4")					ShaderDataType::Float;
	if (glslSrc == "mat3")					ShaderDataType::Mat3;
	if (glslSrc == "mat4")					ShaderDataType::Mat4; 
	if (glslSrc == "bool")					ShaderDataType::Bool; 
	if (glslSrc == "sampler2D")				ShaderDataType::Sampler2D;
}

static unsigned int ShaderDataTypeToOpenGLType(ShaderDataType type)
{
	if (type == ShaderDataType::Int)		return GL_INT;
	if (type == ShaderDataType::Int2)		return GL_INT;
	if (type == ShaderDataType::Int3)		return GL_INT;
	if (type == ShaderDataType::Int4)		return GL_INT;
	if (type == ShaderDataType::Float)		return GL_FLOAT;
	if (type == ShaderDataType::Float)		return GL_FLOAT;
	if (type == ShaderDataType::Float)		return GL_FLOAT;
	if (type == ShaderDataType::Float)		return GL_FLOAT;
	if (type == ShaderDataType::Mat3)		return GL_FLOAT;
	if (type == ShaderDataType::Mat4)		return GL_FLOAT;
	if (type == ShaderDataType::Bool)		return GL_BOOL;
	
}