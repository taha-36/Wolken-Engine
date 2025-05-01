#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out uint objectID;

in vec3 ourColor;
in vec2 TexCoord;

uniform uint id;
uniform int isSelected;
uniform int useTex;
uniform sampler2D texture1;

void main()
{
	if(isSelected == 1)
	{
		if(useTex == 1)
		{
			FragColor = mix(texture(texture1, TexCoord) * vec4(ourColor, 1.0), vec4(0.302, 0.82, 0.929, 0.6), 0.5);
		}
		else
		{
			FragColor = mix(vec4(ourColor, 1.0), vec4(0.302, 0.82, 0.929, 0.6), 0.5);
		}
	}
	else
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
	objectID = id;
}