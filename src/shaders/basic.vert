#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec2 uPosition;
uniform float uRadius;
uniform float uRotation;

uniform mat4 uCamera;

void main()
{
    float c = cos(uRotation);
    float s = sin(uRotation);

    mat2 rotationMatrix = mat2(
         c, s,
        -s, c
    );

    vec2 rotatedPosition =
        rotationMatrix * aPos.xy;

    vec2 worldPosition =
        uPosition + rotatedPosition * uRadius;

    gl_Position =
        uCamera *
        vec4(
            worldPosition,
            0.0,
            1.0
        );
}