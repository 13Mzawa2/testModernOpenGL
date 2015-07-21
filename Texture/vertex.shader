#version 330 core


layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

uniform mat4 mv_matrix;
uniform mat3 normal_matrix;
uniform mat4 mvp;

out vec3 color;

void main()
{
    vec3 n = normalize(normal_matrix * in_normal);

    vec4 camera = mv_matrix * vec4(in_position, 1.0);
    vec4 light = vec4(4.0, 4.0, 4.0, 1.0);
    vec3 s = normalize(vec3(light - camera));

    color = vec3(1.0, 1.0, 1.0) * max(dot(s, n), 0.0);
    gl_Position = mvp * vec4(in_position, 1.0);
}