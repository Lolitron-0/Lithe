#type vertex
#version 330 core
layout(location=0) in vec3 a_Position;
layout(location=3) in vec3 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 Position;
out vec3 Color;

void main()
{
	gl_Position = u_ViewProjection *u_Model* vec4(a_Position, 1.0);
	Position = a_Position;
	Color = a_Color;
}

#type fragment
#version 330 core
in vec3 Position;
in vec3 Color;

out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4(Color, 1.0);
}