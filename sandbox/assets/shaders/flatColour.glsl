#region Vertex

#version 440 core
			
layout(location = 0) in vec3 a_vertexPosition;
layout(location = 1) in vec3 a_vertexColour;
layout(location = 2) in vec2 a_textCoord;

out vec3 fragmentColour;

uniform mat4 u_MVP;

void main()
{
	fragmentColour = a_vertexColour;
	texCoord = vec2(a_texCoord.x, a_texCoord.y);
	gl_Position =  u_MVP * vec4(a_vertexPosition,1);
}

#region Fragment

#version 440 core
			
layout(location = 0) out vec4 colour;


in vec3 fragmentColour;
in vec2 texCoord;

uniform sampler2D u_texData;

void main()
{
	colour = vec4(fragmentColour, 1.0) * texture(u_texData, texCoord);
}