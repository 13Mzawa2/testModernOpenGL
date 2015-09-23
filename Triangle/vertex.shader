//	頂点シェーダ

#version 330 core			//	OpenGL 3.3を使用

//	インプットデータ
layout(location = 0) in vec3 vertexPosition_modelspace;

void main(void)
{
	//	内部変数 gl_Position にセット
	gl_Position.xyz = vertexPosition_modelspace;
	gl_Position.w = 1.0;
}