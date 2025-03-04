#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 UVs;

layout (location = 0) uniform mat4 projectionView;
layout (location = 1) uniform mat4 transform;

vec3 lightLocation = vec3(0.0,0.0,0.0);
vec3 ambient = vec3(0.2, 0.3, 0.4);

out vec2 uv_coords;
out vec3 shading;

void main(){
    vec4 transformedPosition = transform * vec4(position, 1.0);
    vec3 transformedNormal = mat3(transpose(inverse(transform))) * normal;
    uv_coords = UVs;

    vec3 ligthDirection = normalize(lightLocation - transformedPosition.xyz);

    float diffuse = max(dot(transformedNormal, ligthDirection), 0.0);
    
    shading =  (ambient + diffuse) * vec3(0.9, 0.9, 0.6);
    gl_Position = projectionView * transformedPosition;
}