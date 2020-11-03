#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 atextureCoord;

out vec2 textureCoord;

void main(void)
{
    gl_Position = vec4(position, 1.0);
	textureCoord = atextureCoord;
}