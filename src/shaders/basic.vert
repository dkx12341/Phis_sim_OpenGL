#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec2 uPosition;
uniform float uRadius;

uniform mat4 uCamera;

void main()
{
    vec2 worldPosition =
        uPosition + aPos.xy * uRadius;

    gl_Position =
        uCamera *
        vec4(
            worldPosition,
            0.0,
            1.0
        );
}