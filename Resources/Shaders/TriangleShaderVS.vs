uniform mat4 u_trans;
attribute vec3 a_posL;
attribute vec3 a_norm;
attribute vec3 a_binorm;
attribute vec3 a_tgt;
attribute vec2 a_uv;

varying vec2 v_uv;

void main()
{
vec4 posL = u_trans * vec4(a_posL, 1.0);
gl_Position = posL;
v_uv = a_uv;
}