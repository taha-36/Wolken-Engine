#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform int useTex;
uniform bool useVertsColors;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = proj * view * model * vec4(aPos, 1.0);
	if(useVertsColors)
	{
		ourColor = aColor;
	}
	else
	{
		ourColor = vec3(1.0,1.0,1.0);
	}
	TexCoord = aTexCoord;
}