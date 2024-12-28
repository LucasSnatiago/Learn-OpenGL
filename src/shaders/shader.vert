#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;

uniform float movePos;

void main()
{
    gl_Position = vec4(aPos.x + movePos, aPos.y, aPos.z, 1.0f);
    // ourColor = aColor;
    ourColor = aPos;
}
