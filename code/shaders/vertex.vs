#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec2 texClipper;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(position, 1.0);
    //gl_Position = vec4(position, 1.0);
    TexCoord = aTexCoord;
}