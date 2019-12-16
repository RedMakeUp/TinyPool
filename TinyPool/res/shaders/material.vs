#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 PosInWorld;
out vec3 Normal;

uniform mat4 model;
uniform mat4 mvp;

void main()
{
    TexCoords = aTexCoords;
	PosInWorld = (model * vec4(aPos, 1.0)).xyz;
	Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = mvp * vec4(aPos, 1.0);
}