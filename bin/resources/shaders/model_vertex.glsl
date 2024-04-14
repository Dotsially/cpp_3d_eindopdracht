#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 UVs;

layout (location = 0) uniform mat4 projectionView;

out vec2 uv_coords;
out vec3 normals;

void main(){
    uv_coords = UVs;
    normals = normals;
    gl_Position = projectionView * vec4(position, 1.0);
}