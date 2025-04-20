#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
uniform int useTex;
uniform sampler2D texture1;

void main()
{
	if(useTex == 1)
	{
		FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
	}
	else
	{
		FragColor = vec4(ourColor, 1.0);
	}
}