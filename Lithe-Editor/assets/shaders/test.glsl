#type vertex
#version 330 core
layout(location=0) in vec3 a_Position;
layout(location=1) in vec3 a_Normal;
layout(location=2) in vec2 a_TexCoord;
layout(location=3) in vec3 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 Position;
out vec3 Color;
out vec2 TexCoord;

void main()
{
	gl_Position = u_ViewProjection *u_Model* vec4(a_Position, 1.0);
	Position = a_Position;
	Color = a_Color;
	TexCoord = a_TexCoord;
}

#type fragment
#version 330 core

struct Material 
{
	sampler2D DiffuseMap;
	sampler2D SpecularMap;
}

in vec3 Position;
in vec3 Color;
in vec2 TexCoord;

out vec4 fragmentColor;

uniform Material u_Material;
uniform sampler2D textureObj;

void main()
{
	fragmentColor = texture(u_Material.DiffuseMap, TexCoord);
}