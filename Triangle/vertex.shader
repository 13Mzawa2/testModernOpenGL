//	���_�V�F�[�_

#version 330 core			//	OpenGL 3.3���g�p

//	�C���v�b�g�f�[�^
layout(location = 0) in vec3 vertexPosition_modelspace;

void main(void)
{
	//	�����ϐ� gl_Position �ɃZ�b�g
	gl_Position.xyz = vertexPosition_modelspace;
	gl_Position.w = 1.0;
}