//	���_�V�F�[�_

#version 330 core			//	OpenGL 3.3���g�p

//	�C���v�b�g�f�[�^
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
//	�A�E�g�v�b�g�f�[�^
out vec3 fragmentColor;
uniform mat4 MVP;

void main(){
 
    // �N���b�v��Ԃł́A���_�̃A�E�g�v�b�g�ʒu�FMVP * �ʒu
    vec4 v = vec4(vertexPosition_modelspace,1); // ����4D�x�N�g���ɕϊ����܂��B�o���Ă��܂����H
    gl_Position = MVP * v;

	//	�t���O�����g�V�F�[�_�ɓ]��
	fragmentColor = vertexColor;
}