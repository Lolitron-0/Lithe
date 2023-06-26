#version 330 core
in vec3 Position;

out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4((Position + 1) * 0.5, 1.0);
}