#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec2 uPosition;
uniform float uRadius;

void main()
{
    vec2 position =
        uPosition + aPos.xy * uRadius;

    gl_Position = vec4(
        position,
        0.0,
        1.0
    );
}