#version 460 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 worldPosition;

layout (location = 0) uniform mat4 projectionView;
layout (location = 1) uniform vec3 cameraRight;
layout (location = 2) uniform vec3 cameraUp;

const vec2 uv_coords[4] = vec2[4](
    vec2(0.0, 0.0), vec2(0.0, 1.0),
    vec2(1.0, 0.0), vec2(1.0, 1.0)
);

out vec2 uvCoord;

void main(){
    vec3 vertexPosition = worldPosition
    + -cameraRight * position.x * 1.0 +
    + cameraUp * position.y * 1.0;

    uvCoord = uv_coords[gl_VertexID % 4];
    gl_Position = projectionView * vec4(vertexPosition, 1.0);
}
