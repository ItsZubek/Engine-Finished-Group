#region Vertex

#version 440 core
			
layout(location = 0) in vec3 a_vertexPosition;




uniform mat4 u_MVP;

void main()
{
	gl_Position =  u_MVP * vec4(a_vertexPosition,1.0);
}
				
#region Fragment

#version 440 core
			
layout(location = 0) out vec4 colour;

uniform vec4 u_Colour

void main()
{
	colour = u_Color
}