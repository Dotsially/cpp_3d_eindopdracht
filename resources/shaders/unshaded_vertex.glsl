#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 UVs;

layout (location = 0) uniform mat4 projectionView;
layout (location = 1) uniform mat4 transform;

out vec2 uv_coords;

void main(){
    uv_coords = UVs;
    gl_Position = projectionView * transform * vec4(position, 1.0);
}