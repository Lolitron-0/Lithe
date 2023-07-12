#version 330 core
struct Material 
{
	sampler2D DiffuseMap;
	sampler2D SpecularMap;
	bool Textured;
	vec3 BaseColor;
	float Transparency;
	float Shininess;
};

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

out vec4 fragmentColor;

uniform Material u_Material;

void main()
{
	vec4 result;
	if (u_Material.Textured)
		result = texture(u_Material.DiffuseMap, TexCoord);
	else
		result = vec4(u_Material.BaseColor,1);
	result.a = u_Material.Transparency;
	fragmentColor = result;
}