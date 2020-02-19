#region Vertex

#version 440 core
			
layout(location = 0) in vec3 a_vertexPosition;
layout(location = 1) in vec3 a_texCoord;

out vec2 texCoord;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;  

void main()
{
	texCoord = a_texCoord;
	gl_Position = u_projection * u_view * u_model * vec4(a_vertexPosition, 0.f, 1.f);
}

#region Fragment

#version 440 core
			
layout(location = 0) out vec4 colour;

in vec2 texCoord;

uniform Sampler2D u_textData;

void main()
{
	colour = texture(u_textData, texCoord);
}